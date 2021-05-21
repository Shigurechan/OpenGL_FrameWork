#ifndef ___FRAMEWORK_HPP_
#define ___FRAMEWORK_HPP_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

#include "Window.hpp"
#include "Sprite.hpp"
#include "Rectangle.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Text.hpp"
#include "RandomNumber.hpp"
#include "Animation.hpp"


#define PI ((float)3.14159265359f) //PI

namespace FrameWork
{


	bool Init();
	void setVersion(int a,int b);
}
#endif

