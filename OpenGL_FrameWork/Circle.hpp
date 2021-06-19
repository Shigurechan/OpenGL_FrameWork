#ifndef ___CIRCLE_HPP_
#define ___CIRCLE_HPP_
#include <iostream>
#include <vector>
#include "Shader.hpp"
#include "Transform_2D.hpp"

/*#########################################################################
# �@�~�`��N���X

����
	
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Circle : protected FrameWork::Transform_2D
	{

	public:

		Circle();	//�R���X�g���N�^
		~Circle();	//�f�X�g���N�^

		void Draw(glm::vec2 pos, int num, float r, glm::vec4 color);	//�`��

	private:

		std::vector<Transform_2D::Vertex> vertex;	//���_�z��
		int count = 0;								//���_��
	};

}
#endif;


