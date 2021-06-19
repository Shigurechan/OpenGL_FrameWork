#ifndef ___SIMPLE_DRAW_HPP_
#define ___SIMPLE_DRAW_HPP_
#include "glm/glm.hpp"
#include "glew/include/GL/glew.h"
#include <iostream>
#include "ft2build.h"
#include FT_FREETYPE_H

/*#########################################################################
# ä»à’ï`âÊä÷êî

ê‡ñæ

###########################################################################*/

namespace FrameWork
{
	void DrawFormatString(glm::vec2 pos, glm::vec4 color, FT_UInt charSize, const char* str, ...);	//ï∂éö
	void DrawRectangle(glm::vec2 start,glm::vec2 end,glm::vec4 color);								//ãÈå`
	void DrawCircle(glm::vec2 start, int num, int r, glm::vec4 color);								//â~
	void DrawPoint(glm::vec2 pos, GLfloat size, glm::vec4 color);									//ì_
	void DrawLine(glm::vec2 start, glm::vec2 end, GLfloat size, glm::vec4 color);					//ê¸
	void DrawTriangle(glm::vec2 pos, GLfloat size, glm::vec4 color);								//éOäpå`
	void DrawOval(glm::vec2 pos,int num,glm::vec2 r, glm::vec4 color);								//ë»â~
}
#endif


