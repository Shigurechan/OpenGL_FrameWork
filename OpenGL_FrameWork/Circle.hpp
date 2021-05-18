#ifndef ___CIRCLE_HPP_
#define ___CIRCLE_HPP_

#include <iostream>
#include <vector>
#include "Shader.hpp"
#include "Transform_2D.hpp"

namespace FrameWork
{
	class Window;

	class Circle : protected FrameWork::Transform_2D, public FrameWork::Shader
	{
	public:
		Circle(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);		//コンストラクタ
		~Circle();								//デストラクタ

		void Draw(glm::vec2 pos, int num, float r, glm::vec4 color);	//描画


	private:
		std::shared_ptr<Window> windowContext;	//ウインドウコンテキスト
		bool isDefaultShader;

		std::vector<Transform_2D::VertexColor> vertex;
		int count = 0;

	};

}
#endif;


