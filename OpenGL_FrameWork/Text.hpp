#ifndef ___TEXT_HPP
#define ___TEXT_HPP

#include "Transform_2D.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include <map>

#include "ft2build.h"
#include FT_FREETYPE_H

namespace FrameWork
{
    class Window;

    class Text : protected FrameWork::Transform_2D, public Shader
    {
    public:
        Text(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);		//�R���X�g���N�^
        ~Text();	                                                                            //�f�X�g���N�^

        void Draw(glm::vec2 pos,float scale, glm::vec3 color, const char* str, ...);    //�`��


    private:

        struct Character {
            unsigned int textureID;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        std::map<char, Character> Characters;   //�����f�[�^
        std::shared_ptr<Window> windowContext;  //�E�C���h�E�R���e�L�X�g
        int charSize;   //�����̑傫��(�s�N�Z��)
        FT_Library ft;
        FT_Face face;

    };

}

#endif