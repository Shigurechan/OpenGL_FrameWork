#ifndef ___LINE_HPP_
#define ___LINE_HPP_
#include "Transform_2D.hpp"
#include "Shader.hpp"
#include <iostream>
/*#########################################################################
# Line �N���X

����
	���@�`��
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Line : protected FrameWork::Transform_2D
	{

	public:

		Line();		//�R���X�g���N�^
		~Line();	//�f�X�g���N�^

		void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color);	//�`��

	private:

		//���_�����@���_�J���[
		Transform_2D::Vertex vertex[2] =
		{
			{-0.5f,-0.5f},
			{0.5f,0.5f}
		};

	};
}
#endif
