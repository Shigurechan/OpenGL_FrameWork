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

    class Text : protected FrameWork::Transform_2D, public Shader
    {

    public:
        Text(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);  //�R���X�g���N�^
        ~Text();	                                                                        //�f�X�g���N�^

        void Draw(glm::vec2 pos,float scale, glm::vec3 color, const char* str, ...);    //�`��
    private:

        struct Character 
        {
            unsigned int textureID;  // �O���t�̃e�N�X�`��ID
            glm::ivec2   Size;       // �O���t�T�C�Y
            glm::ivec2   Bearing;    // �O���t�̃x�[�X���C��
            unsigned int Advance;    // ���̃O���t�܂ł̃I�t�Z�b�g
        };

        std::map<char, Character> Characters;   //�����f�[�^
        std::shared_ptr<Window> windowContext;  //�E�C���h�E�R���e�L�X�g
        int charSize;                           //�����̑傫��(�s�N�Z��)

        //FreeType
        FT_Library ft;  //freetype
        FT_Face face;   //�t�F�C�X
    };
}
#endif