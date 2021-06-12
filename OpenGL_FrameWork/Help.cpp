#include "Help.hpp"
#include <locale.h>
#include <Random>
#include <iostream>
#include "Shader.hpp"
#include "Window.hpp"
#include "glew/include/GL/glew.h"
#include "glfw/include/GLFW/glfw3.h"
#include <glm/gtc/matrix_Transform.hpp>
#include <glm/gtx/Transform.hpp>
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H

namespace FrameWork
{

    // ##################################### 乱数 ##################################### 
	int GetRandom(int start, int end)
	{
		std::random_device rnd;                             // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());                             //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> Rand(start, end);   // [start, end] 範囲の一様乱数	

		return Rand(mt);
	}

    // ##################################### 簡易文字描画 ##################################### 
	void DrawFormatString(std::shared_ptr<FrameWork::Window> w,glm::vec2 pos,glm::vec3 color,float scale,const char* str, ...)
	{
        FrameWork::Shader shader;
        
        shader.LoadShader("Shader/2D/BasicText_2D.vert", "Shader/2D/BasicText_2D.frag");    //シェーダー読み込み

        GLuint vao; //vao
        GLuint vbo; //vbo

        //文字構造体
        struct Character
        {
            unsigned int textureID;  // グリフのテクスチャID
            glm::ivec2   Size;       // グリフサイズ
            glm::ivec2   Bearing;    // グリフのベースライン
            unsigned int Advance;    // 次のグリフまでのオフセット
        };

        std::map<char, Character> Characters;   //文字データ
        int charSize = 24;                      //文字の大きさ(ピクセル)

        //FreeType
        FT_Library ft;  //freetype
        FT_Face face;   //フェイス

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
            std::cout << "ERROR: FREETYPE: Could not init FreeType Library" << std::endl;
        }

        //フェイス作成　フォントはメイリオ
        if (FT_New_Face(ft, "C:\\Windows\\Fonts\\meiryo.ttc", 0, &face) != 0)
        {
            std::cout << "ERROR: FREETYPE: Failed to load font" << std::endl;
        }

        
        FT_Set_Pixel_Sizes(face, 0, charSize);  //ピクセルサイズを指定

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction


        //アルファブレンドを有効
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //色をRGBにして位置を反転
        pos.y = w->getSize().y - pos.y - charSize;
        const float c = 1.0f / 255;
        color = color * c;

        //テクスチャをアクティブ
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);

        shader.setEnable(); //シェーダーを有効にする

        //Unform
        shader.setUniform3f("textColor", color);
        shader.setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, w->getSize().x, 0.0f, w->getSize().y));

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


        //文字描画
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
            glDeleteTextures(1, &ch.textureID);

            pos.x += ((ch.Advance >> 6) * scale); //次のグリフに進める

        }

        //解放
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        shader.setDisable();   //シェーダーを無効にする
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        //グリフ解放
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

	}




}