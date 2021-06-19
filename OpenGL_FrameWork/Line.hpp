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

	class Line : protected FrameWork::Transform_2D
	{

	public:

		Line();		//コンストラクタ
		~Line();	//デストラクタ

		void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color);	//描画

	private:

		//頂点属性　頂点カラー
		Transform_2D::Vertex vertex[2] =
		{
			{-0.5f,-0.5f},
			{0.5f,0.5f}
		};

	};
}
#endif
