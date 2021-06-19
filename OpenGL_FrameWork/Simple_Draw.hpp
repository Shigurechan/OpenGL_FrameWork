#ifndef ___SIMPLE_DRAW_HPP_
#define ___SIMPLE_DRAW_HPP_
#include "glm/glm.hpp"
#include <iostream>
#include "ft2build.h"
#include FT_FREETYPE_H

/*#########################################################################
# 簡易描画関数

説明

###########################################################################*/

namespace FrameWork
{
	class Window;
	void DrawFormatString(glm::vec2 pos, glm::vec4 color, FT_UInt charSize, const char* str, ...);	//文字
	void DrawRectangle(glm::vec2 pos,glm::vec2 size,glm::vec4 color);


}
#endif


