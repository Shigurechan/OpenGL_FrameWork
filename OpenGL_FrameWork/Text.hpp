#ifndef ___TEXT_HPP_
#define ___TEXT_HPP_
#include "Transform_2D.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H

/*#########################################################################
# �����`��N���X

����
    ������`�悷��
###########################################################################*/
namespace FrameWork
{
    class Window;

    class Text : protected FrameWork::Transform_2D
    {

    public:

        Text(const char* fontName, int fontSize, const char* str, ...);   //�R���X�g���N�^
        ~Text();                                    //�f�X�g���N�^

        void Draw(glm::vec2 pos,glm::vec4 color);    //�`��

    private:

         //�����\����
        struct Character
        {
            unsigned int textureID;  // �O���t�̃e�N�X�`��ID
            glm::ivec2   Size;       // �O���t�T�C�Y
            glm::ivec2   Bearing;    // �O���t�̃x�[�X���C��
            unsigned int Advance;    // ���̃O���t�܂ł̃I�t�Z�b�g
        };

        std::vector<Character> character;   //�����f�[�^
        int charSize;                       //�����̑傫��(�s�N�Z��)

        //FreeType
        FT_Face face;   //�t�F�C�X
        FT_Library ft;  //freetype

    };
}
#endif