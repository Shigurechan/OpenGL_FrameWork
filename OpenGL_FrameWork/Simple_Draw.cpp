#include "Simple_Draw.hpp"

#include "glew/include/GL/glew.h"
#include "glfw/include/GLFW/glfw3.h"
#include <glm/gtc/matrix_Transform.hpp>
#include <glm/gtx/Transform.hpp>
#include "Window.hpp"
#include "FrameWork.hpp"
#include "Shader.hpp"
#include <map>

namespace FrameWork
{
    //��`�`��
    void DrawRectangle(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
    {      
        float x = 1.0f / FrameWork::getWindowContext()->getSize().x;
        float y = 1.0f / FrameWork::getWindowContext()->getSize().y;
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);

        
        glm::vec2 posA;
        glm::vec2 posB;
        posA.x = ((pos.x * x) - 0.5f) - 0.5f;
        posA.y = ((pos.y * y) - 0.5f);

        posB.x = ((pos.x + size.x) * x - 0.5f) - 0.5f;
        posB.y = ((pos.y + size.y)* y - 0.5f);



        glRectf(posA.x, posA.y, posB.x, posB.y);

        glFlush();
    }








    // ##################################### �ȈՕ����`�� ##################################### 
    void DrawFormatString(glm::vec2 pos, glm::vec4 color, FT_UInt charSize, const char* str, ...)
    {
        setlocale(LC_CTYPE, "");    //���[�J����ݒ�

        FrameWork::Shader shader;

        shader.Load("Shader/2D/BasicText_2D.vert", "Shader/2D/BasicText_2D.frag");    //�V�F�[�_�[�ǂݍ���

        GLuint vao; //vao
        GLuint vbo; //vbo

        struct Character
        {
            unsigned int textureID;  // �O���t�̃e�N�X�`��ID
            glm::ivec2   Size;       // �O���t�T�C�Y
            glm::ivec2   Bearing;    // �O���t�̃x�[�X���C��
            unsigned int Advance;    // ���̃O���t�܂ł̃I�t�Z�b�g
        };

        //vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        //���_����
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

        //FreeType��������

        //FreeType
        FT_Library ft;  //freetype
        FT_Face face;   //�t�F�C�X

        //������ 
        if (FT_Init_FreeType(&ft) != 0)
        {
            std::cerr << "ERROR: FREETYPE: Could not init FreeType Library" << std::endl;
        }

        //�t�F�C�X�쐬�@�t�H���g�̓��C���I
        if (FT_New_Face(ft, "C:\\Windows\\Fonts\\meiryo.ttc", 0, &face) != 0)
        {
            std::cerr << "ERROR: FREETYPE: Failed to load font" << std::endl;
        }

        FT_Set_Pixel_Sizes(face, 0, charSize);  //�s�N�Z���T�C�Y���w��
        float scale = 1.0f;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        //�A���t�@�u�����h��L��
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //�F��RGB�ɂ��Ĉʒu�𔽓]
        pos.y = FrameWork::getWindowContext()->getSize().y - pos.y - charSize;
        const float c = 1.0f / 255;
        color = color * c;

        //�}���`�o�C�g���������C�h�����ϊ�
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

        //�����`��
        for (int i = 0; txt[i] != L'\0'; i++)
        {
            unsigned int texture = 0;

            //�O���t�����[�h
            FT_Load_Glyph(face, FT_Get_Char_Index(face, txt[i]), FT_LOAD_RENDER);

            //�����f�[�^��ݒ�
            Character ch =
            {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (unsigned int)face->glyph->advance.x

            };

            //�e�N�X�`���𐶐�
            glGenTextures(1, &ch.textureID);
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            glActiveTexture(GL_TEXTURE0);

            glTexImage2D
            (
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

            //�e�N�X�`���^�C�v��ݒ�
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

            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            shader.setEnable(); //�V�F�[�_�[��L���ɂ���

            //Unform
            shader.setUniform4f("uTextColor", color);
            shader.setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, 0.0f, FrameWork::getWindowContext()->getSize().y));

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteTextures(1, &ch.textureID);
            shader.setDisable();            //�V�F�[�_�[�𖳌��ɂ���

            pos.x += ((ch.Advance >> 6) * scale); //���̃O���t�ɐi�߂�

        }

        //���

        // vao vbo
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

        //�O���t���
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
}