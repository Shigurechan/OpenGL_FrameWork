#ifndef ___CIRCLE_HPP_
#define ___CIRCLE_HPP_
#include <iostream>
#include <vector>
#include "Shader.hpp"
#include "Transform_2D.hpp"

/*#########################################################################
# 　円描画クラス

説明
	
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Circle : protected FrameWork::Transform_2D
	{

	public:

		Circle();	//コンストラクタ
		~Circle();	//デストラクタ

		void Draw(glm::vec2 pos, int num, float r, glm::vec4 color);	//描画

	private:

		std::vector<Transform_2D::Vertex> vertex;	//頂点配列
		int count = 0;								//頂点数
	};

}
#endif;


