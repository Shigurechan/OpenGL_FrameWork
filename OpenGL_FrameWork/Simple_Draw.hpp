#ifndef ___SIMPLE_DRAW_HPP_
#define ___SIMPLE_DRAW_HPP_
#include "glm/glm.hpp"
#include "glew/include/GL/glew.h"
#include <iostream>
#include "ft2build.h"
#include FT_FREETYPE_H

/*#########################################################################
# �ȈՕ`��֐�

����

###########################################################################*/

namespace FrameWork
{
	void DrawFormatString(glm::vec2 pos, glm::vec4 color, FT_UInt charSize, const char* str, ...);	//����
	void DrawRectangle(glm::vec2 start,glm::vec2 end,glm::vec4 color);								//��`
	void DrawCircle(glm::vec2 start, int num, int r, glm::vec4 color);								//�~
	void DrawPoint(glm::vec2 pos, GLfloat size, glm::vec4 color);									//�_
	void DrawLine(glm::vec2 start, glm::vec2 end, GLfloat size, glm::vec4 color);					//��
	void DrawTriangle(glm::vec2 pos, GLfloat size, glm::vec4 color);								//�O�p�`
	void DrawOval(glm::vec2 pos,int num,glm::vec2 r, glm::vec4 color);								//�ȉ~
}
#endif


