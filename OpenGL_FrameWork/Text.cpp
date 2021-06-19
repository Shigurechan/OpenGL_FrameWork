#include "Text.hpp"

#include "glew/include/GL/glew.h"
#include "glm/glm.hpp"
#include "uchar.h"
#include "Window.hpp"
#include "FrameWork.hpp"
#include <iostream>

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Text::Text(const char *fontName ,int fontSize,const char *str,...) : FrameWork::Transform_2D()
{
    charSize = fontSize;        //�����t�H���T�C�Y
    face = nullptr;             //�t�F�C�X��������
    ft = nullptr;               //FreeType��������

    //�V�F�[�_�[�ǂݍ���
    shader = std::make_unique<FrameWork::Shader>();
    shader->Load("Shader/2D/BasicText_2D.vert", "Shader/2D/BasicText_2D.frag");

    //vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //���_����
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(shader->getAttribLocation("vertexPosition"));
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    shader->setBindAttribLocation("vertexPosition");

    //������ 
    if (FT_Init_FreeType(&ft) != 0)
    {
        std::cerr << "FreeType ���C�u�������������o���܂���B"<<std::endl;
    }

    //�t�F�C�X�쐬�@�t�H���g�̓��C���I
    if (FT_New_Face(ft,fontName, 0, &face) != 0)
    {
        std::cerr << "FreeType �t�H���g��ǂݍ��߂܂���B"<< std::endl;
    }

    FT_Set_Pixel_Sizes(face,0,charSize);  //�s�N�Z���T�C�Y���w��
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    
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
    
    //���������[�h
    for (int i = 0; txt[i] != L'\0'; i++)
    {
        //�O���t�����[�h
        FT_Load_Glyph(face, FT_Get_Char_Index(face, txt[i]), FT_LOAD_RENDER);
        
        Character ch =
        {
            0,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };

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


        //�e�N�X�`���𐶐�      
        character.push_back(ch);

    }

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// ##################################### �`�� ##################################### 
void FrameWork::Text::Draw(glm::vec2 pos,glm::vec4 color)
{
    shader->setEnable();    //�V�F�[�_�[��L���ɂ���
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //�F��RGB�ɂ��Ĉʒu�𔽓]
    pos.y = FrameWork::getWindowContext()->getSize().y - pos.y - charSize;
    float c = 1.0f / 255.0f;

    //Unform
    shader->setUniform4f("uTextColor", color * c);    
    shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, 0.0f, FrameWork::getWindowContext()->getSize().y));

    for (std::vector<Character>::iterator itr = character.begin(); itr != character.end(); itr++) 
    {
#define SCALE 1.0f  //�����̑傫��

        float xpos = pos.x + itr->Bearing.x * SCALE;
        float ypos = pos.y - (itr->Size.y - itr->Bearing.y) * SCALE;

        float w = itr->Size.x * SCALE;
        float h = itr->Size.y * SCALE;

        float vertices[6][4] =
        {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, itr->textureID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindTexture(GL_TEXTURE_2D, 0);

        pos.x += ((itr->Advance >> 6) * SCALE); //���̃O���t�ɐi�߂�
#undef SCALE
    }
    

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    shader->setDisable();   //�V�F�[�_�[�𖳌��ɂ���
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Text::~Text()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    //�O���t���
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

}