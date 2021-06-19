#ifndef ___TEXT_HPP_
#define ___TEXT_HPP_
#include "Transform_2D.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H

/*#########################################################################
# 文字描画クラス

説明
    文字を描画する
###########################################################################*/
namespace FrameWork
{
    class Window;

    class Text : protected FrameWork::Transform_2D
    {

    public:

        Text(const char* fontName, int fontSize, const char* str, ...);   //コンストラクタ
        ~Text();                                    //デストラクタ

        void Draw(glm::vec2 pos,glm::vec4 color);    //描画

    private:

         //文字構造体
        struct Character
        {
            unsigned int textureID;  // グリフのテクスチャID
            glm::ivec2   Size;       // グリフサイズ
            glm::ivec2   Bearing;    // グリフのベースライン
            unsigned int Advance;    // 次のグリフまでのオフセット
        };

        std::vector<Character> character;   //文字データ
        int charSize;                       //文字の大きさ(ピクセル)

        //FreeType
        FT_Face face;   //フェイス
        FT_Library ft;  //freetype

    };
}
#endif