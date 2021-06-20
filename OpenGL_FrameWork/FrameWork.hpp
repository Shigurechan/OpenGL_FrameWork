#ifndef ___FRAMEWORK_HPP_
#define ___FRAMEWORK_HPP_
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

#include "Window.hpp"
#include "Simple_Draw.hpp"
#include "Sprite.hpp"
#include "Rectangle.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Circle.hpp"
#include "Text.hpp"
#include "Help.hpp"
#include "Animation.hpp"

#define PI ((float)3.14159265359f) //PI

namespace FrameWork
{
	bool Init(glm::ivec2 size,const char* title);	//初期化
	void setVersion(int a,int b);	//バージョンを設定
	std::shared_ptr<FrameWork::Window> getWindowContext();	//ウインドウコンテキストを取得
}
#endif

