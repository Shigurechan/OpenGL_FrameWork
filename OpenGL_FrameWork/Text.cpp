#include "Text.hpp"
#include "glew/include/GL/glew.h"
#include "glm/glm.hpp"

#include "uchar.h"
#include "Window.hpp"
#include <iostream>

FrameWork::Text::Text(std::shared_ptr<Window> w, const char* vert, const char* frag) : FrameWork::Transform_2D(),Shader()
{
    setlocale(LC_CTYPE, "");


    windowContext = w;  //ウインドウコンテキスト

    //シェーダー
    if (vert == NULL && frag == NULL)
    {
        vert = "Shader/2D/BasicText_2D.vert";
        frag = "Shader/2D/BasicText_2D.frag";
        LoadShader(vert,frag);
    }
    else {
        LoadShader(vert, frag);
    }

    //vao vbo 
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //FreeTypeを初期化
    // 
    //初期化
    
    if (FT_Init_FreeType(&ft) != 0)
    {
        std::cout << "ERROR: FREETYPE: Could not init FreeType Library"<<std::endl;
        assert(0);
    }

    //フェイス作成

    if (FT_New_Face(ft, "C:\\Windows\\Fonts\\meiryo.ttc", 0, &face) != 0)
    {
        std::cout << "ERROR: FREETYPE: Failed to load font" << std::endl;
        assert(0);

    }
    
    charSize = 24;  //文字サイズを指定
    FT_Set_Pixel_Sizes(face,0,charSize);  //ピクセルサイズを指定

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    //アルファブレンドを有効
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FrameWork::Text::Draw(glm::vec2 pos, float scale, glm::vec3 color, const char* str, ...)
//void FrameWork::Text::Draw(glm::vec2 pos, std::string text,float scale, glm::vec3 color)
{
    setEnable();    //シェーダーを有効にする

    pos.y = windowContext->getSize().y - pos.y - charSize;
    const float c = 1.0f / 255;
    color = color * c;
    //テクスチャをアクティブ
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);


    //Unform
    setUniform3f("textColor", color);
    setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, 0.0f, windowContext->getSize().y));

    //char text[] = "テスト";
    //wchar_t txt[strlen(text)] = { L'\0' };
    wchar_t txt[1000] = { L'\0' };// = (wchar_t*)malloc(strlen(text));

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
        //std::cout << txt[i] <<std::endl;
        unsigned int texture = 0;

        // load character glyph 
        FT_Load_Glyph(face, FT_Get_Char_Index(face, txt[i]), FT_LOAD_RENDER);


        // now store character for later use
        Character ch = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x

        };


        // generate texture
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
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
       


        float xpos = pos.x + ch.Bearing.x * scale;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glDeleteTextures(1,&ch.textureID);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.x += ((ch.Advance >> 6) * scale); // bitshift by 6 to get value in pixels (2^6 = 64)

    }
    


    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    setDisable();   //シェーダーを無効にする
}



FrameWork::Text::~Text()
{
    //グリフ解放
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
