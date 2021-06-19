#ifndef ___RECTANGLE_HPP_
#define ___RECTANGLE_HPP_
#include <iostream>
#include "glm/glm.hpp"
#include "Transform_2D.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
/*#########################################################################
# 矩形描画クラス
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Rectangle : protected FrameWork::Transform_2D
	{

	public:

		Rectangle();	//コンストラクタ
		~Rectangle();	//デストラクタ

		void Draw(glm::vec2 start, glm::vec2 end, float r,glm::vec4 color);	// 描画		

	private:

		//塗りつぶし矩形
		Transform_2D::Vertex rectangleVertex[6] =
		{
			 //頂点					頂点色
			{-0.5f,0.5f,	},
			{-0.5f,-0.5f,	},
			{0.5f,0.5f,		},

			{0.5f,0.5f,		},
			{-0.5f,-0.5f,	},
			{0.5f,-0.5f,	},
		};

		
	};
}
#endif

