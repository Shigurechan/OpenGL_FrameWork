#ifndef ___RECTANGLE_HPP_
#define ___RECTANGLE_HPP_
#include <iostream>
#include "glm/glm.hpp"
#include "Transform_2D.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
/*#########################################################################
# ��`�`��N���X
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Rectangle : protected FrameWork::Transform_2D
	{

	public:

		Rectangle();	//�R���X�g���N�^
		~Rectangle();	//�f�X�g���N�^

		void Draw(glm::vec2 start, glm::vec2 end, float r,glm::vec4 color);	// �`��		

	private:

		//�h��Ԃ���`
		Transform_2D::Vertex rectangleVertex[6] =
		{
			 //���_					���_�F
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

