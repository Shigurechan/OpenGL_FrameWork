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

    class Text : protected FrameWork::Transform_2D, public Shader
    {

    public:
        Text(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);  //コンストラクタ
        ~Text();	                                                                        //デストラクタ

        void Draw(glm::vec2 pos,float scale, glm::vec3 color, const char* str, ...);    //描画
    private:

        struct Character 
        {
            unsigned int textureID;  // グリフのテクスチャID
            glm::ivec2   Size;       // グリフサイズ
            glm::ivec2   Bearing;    // グリフのベースライン
            unsigned int Advance;    // 次のグリフまでのオフセット
        };

        std::map<char, Character> Characters;   //文字データ
        std::shared_ptr<Window> windowContext;  //ウインドウコンテキスト
        int charSize;                           //文字の大きさ(ピクセル)

        //FreeType
        FT_Library ft;  //freetype
        FT_Face face;   //フェイス
    };
}
#endif