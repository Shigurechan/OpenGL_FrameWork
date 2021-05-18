#ifndef ___LINE_HPP_
#define ___LINE_HPP_

#include "Transform_2D.hpp"
#include "Shader.hpp"

#include <iostream>
/*#########################################################################
# Line クラス

説明
	線　描画
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Line : protected FrameWork::Transform_2D, public Shader
	{
	public:
		Line(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);		//コンストラクタ
		~Line();																										//デストラクタ

		void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color);													//描画
		void DrawColor(glm::vec2 start, glm::vec2 end, glm::vec4 startColor, glm::vec4 endColor);					//描画


	private:

		Transform_2D::VertexColor vertex[2] =
		{
			{-0.5f,-0.5f,	0.0f,1.0f,0.0f,1.0f},
			{0.5f,0.5f,		0.0f,1.0f,0.0f,1.0f}
		};


		std::shared_ptr<Window> windowContext;	//ウインドウコンテキスト
	};
}
#endif
