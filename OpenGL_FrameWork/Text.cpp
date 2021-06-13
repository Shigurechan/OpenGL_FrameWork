#include "Text.hpp"

#include "glew/include/GL/glew.h"
#include "glm/glm.hpp"
#include "uchar.h"
#include "Window.hpp"
#include <iostream>

// ##################################### コンストラクタ ##################################### 
FrameWork::Text::Text(std::shared_ptr<Window> w, const char* vert, const char* frag) : FrameWork::Transform_2D(),Shader()
{
    setlocale(LC_CTYPE, "");    //ローカルを設定
    windowContext = w;          //ウインドウコンテキスト

    //シェーダー
    if (vert == NULL && frag == NULL)
    {
        vert = "Shader/2D/BasicText_2D.vert";
        frag = "Shader/2D/BasicText_2D.frag";
        if (LoadShader(vert, frag) == false)
        {
            std::cerr << "シェーダープログラムを作成できません。" << std::endl;
        }
    }
    else 
    {
        LoadShader(vert, frag);
    }

    //vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //頂点属性
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    //FreeTypeを初期化
      
    //初期化 
    if (FT_Init_FreeType(&ft) != 0)
    {
        std::cerr << "ERROR: FREETYPE: Could not init FreeType Library"<<std::endl;
    }

    //フェイス作成　フォントはメイリオ
    if (FT_New_Face(ft, "C:\\Windows\\Fonts\\meiryo.ttc", 0, &face) != 0)
    {
        std::cerr << "ERROR: FREETYPE: Failed to load font" << std::endl;
    }
    
    charSize = 24;  //文字サイズを指定
    FT_Set_Pixel_Sizes(face,0,charSize);  //ピクセルサイズを指定

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //アルファブレンドを有効
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// ##################################### 描画 ##################################### 
void FrameWork::Text::Draw(glm::vec2 pos, float scale, glm::vec3 color, const char* str, ...)
{
    setEnable();    //シェーダーを有効にする

    //色をRGBにして位置を反転
    pos.y = windowContext->getSize().y - pos.y - charSize;
    const float c = 1.0f / 255;
    color = color * c;

    //テクスチャをアクティブ
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    //Unform
    setUniform3f("textColor", color);
    setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, 0.0f, windowContext->getSize().y));

    //マルチバイト文字をワイド文字変換
    wchar_t txt[1000] = { L'\0' };
    char text[1000];
    va_list args;
    va_start(args, str); 
    vsprintf_s(text, sizeof(text), str, args);
    va_end(args);

    int i, j, f;
    for (i = 0, j = 0; text[j]; i++, j += f)
    {
        f = (int)mbrtowc(txt + i, &text[j], (size_t)MB_CUR_MAX, nullptr);
    }

    for (int i = 0; txt[i] != L'\0'; i++)
    {
        unsigned int texture = 0;

        //グリフをロード
        FT_Load_Glyph(face, FT_Get_Char_Index(face, txt[i]), FT_LOAD_RENDER);

        //文字データを設定
        Character ch = 
        {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x

        };

        //テクスチャを生成
        glGenTextures(1, &ch.textureID);
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        //テクスチャタイプを設定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       
        float xpos = pos.x + ch.Bearing.x * scale;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
       
        float vertices[6][4] = 
        {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDeleteTextures(1,&ch.textureID);

        pos.x += ((ch.Advance >> 6) * scale); //次のグリフに進める

    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    setDisable();   //シェーダーを無効にする
}


// ##################################### デストラクタ ##################################### 
FrameWork::Text::~Text()
{
    //グリフ解放
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
