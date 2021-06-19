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
    // ##################################### ��` �`�� ##################################### 
    void DrawRectangle(glm::vec2 start, glm::vec2 end, glm::vec4 color)
    {
        float x = 1.0f / (FrameWork::getWindowContext()->getSize().x / 2);
        float y = 1.0f / (FrameWork::getWindowContext()->getSize().y / 2);
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);

        glm::vec2 posA;
        glm::vec2 posB;
        posA.x = ((start.x * x) - 1.0f);
        posA.y = (1.0f - (start.y * y));
        posB.x = ((end.x * x) - 1.0f);
        posB.y = (1.0f - (end.y * y));

        glRectf(posA.x, posA.y, posB.x, posB.y);
        glFinish();
    }

    // ##################################### �~ �`�� ##################################### 
    void DrawCircle(glm::vec2 start,int num,int r, glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::getWindowContext()->getSize().x / 2);
        float dy = 1.0f / (FrameWork::getWindowContext()->getSize().y / 2);
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);

        glBegin(GL_TRIANGLE_FAN);

        glm::vec2 pos = glm::vec2(0,0);
       
        pos.x = (start.x * dx) - 1.0f;
        pos.x = 1.0f - (start.y * dy);

        float f =  (PI * 2) / num;
        float ff = 0;
        for (int i = 0; i < num; i++)
        {
            float x = cos(ff) * (r * dx);
            float y = sin(ff) * (r * dy);

            glVertex2f( pos.x + x, pos.y + y);

            ff += f;
        }

        glEnd();
        glFinish();
    }

    // ##################################### �_ �`�� ##################################### 
    void DrawPoint(glm::vec2 pos,GLfloat size,glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::getWindowContext()->getSize().x / 2);
        float dy = 1.0f / (FrameWork::getWindowContext()->getSize().y / 2);
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);

        glPointSize(size);  //�T�C�Y
        glBegin(GL_POINTS);
        pos.y = 1.0f - (pos.y * dy);

        glVertex2f(pos.x, pos.y);

        glEnd();
        glFinish();
        
    }


    // ##################################### �� �`�� ##################################### 
    void DrawLine(glm::vec2 start,glm::vec2 end, GLfloat size, glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::getWindowContext()->getSize().x / 2);
        float dy = 1.0f / (FrameWork::getWindowContext()->getSize().y / 2);
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);  //�J���[

        glLineWidth(size);  //�T�C�Y
        glBegin(GL_LINE_LOOP);

        //�n�_
        glm::vec2 posA;
        posA.x = (start.x * dx) - 1.0f;
        posA.y = 1.0f - (start.y * dy);

        //�I�_
        glm::vec2 posB;
        posB.x = (end.x * dx) - 1.0f;
        posB.y = 1.0f - (end.y * dy);

        glVertex2f(posA.x, posA.y); //�n�_
        glVertex2f(posB.x, posB.y); //�I�_

        glEnd();
        glFinish();

    }

    // ##################################### �O�p�` �`�� ##################################### 
    void DrawTriangle(glm::vec2 pos, GLfloat size, glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::getWindowContext()->getSize().x / 2);
        float dy = 1.0f / (FrameWork::getWindowContext()->getSize().y / 2);
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);  //�J���[

        glBegin(GL_TRIANGLES);

        pos.x = (pos.x * dx) - 1.0f;
        pos.y = 1.0f - (pos.y * dy);

        glVertex2f(pos.x + 0.0f, pos.y + ((size / 2) * dy));
        glVertex2f(pos.x + ((size / 2) * dx), pos.y - ((size / 2) * dy));
        glVertex2f(pos.x - ((size / 2) * dx), pos.y - ((size / 2) * dy));
        
        glEnd();
        glFinish();

    }

    // ##################################### �ȉ~ �`�� ##################################### 
    void DrawOval(glm::vec2 pos,int num, glm::vec2 r, glm::vec4 color)
    {
        float dx = 1.0f / (FrameWork::getWindowContext()->getSize().x / 2);
        float dy = 1.0f / (FrameWork::getWindowContext()->getSize().y / 2);
        float c = 1.0f / 255.0f;
        glColor4f(color.x * c, color.y * c, color.z * c, color.w * c);  //�J���[

        pos.x = (pos.x * dx) - 1.0f;
        pos.y = 1.0f - (pos.y * dy);

        glBegin(GL_TRIANGLE_FAN);
                
        float f = (PI * 2) / num;
        float ff = 0;
        for (int i = 0; i < num; i++)
        {
            float x = cos(ff) * (r.x * dx);
            float y = sin(ff) * (r.y * dy);

            glVertex2f(pos.x + x, pos.y + y);

            ff += f;
        }
        
        glEnd();
        glFinish();
    }

    // ##################################### �ȈՕ����`�� ##################################### 
    void DrawFormatString(glm::vec2 pos, glm::vec4 color, FT_UInt charSize, const char* str, ...)
    {

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
        if (FT_New_Face(ft, "Font\\SourceHanCodeJP.ttc", 0, &face) != 0)
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