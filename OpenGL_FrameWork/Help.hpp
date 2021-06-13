#ifndef ___HELP_HPP_
#define ___HELP_HPP_
#include "glm/glm.hpp"
#include <iostream>
/*#########################################################################
# •â•Œn‚ÌŠÖ”

à–¾

###########################################################################*/

namespace FrameWork
{
	class Window;

	int GetRandom(int start, int end);	//—”‚ğæ“¾
	void DrawFormatString(std::shared_ptr<FrameWork::Window> w, glm::vec2 pos, glm::vec3 color,float scale,const char* str, ...);	//•¶š‚ğ•`‰æ
}
#endif