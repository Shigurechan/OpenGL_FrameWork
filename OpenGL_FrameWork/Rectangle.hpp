#ifndef ___RECTANGLE_HPP
#define ___RECTANGLE_HPP

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

	class Rectangle : protected FrameWork::Transform_2D, public Shader
	{

	public:

		//frag ���_�F�`������邩�ǂ����H
		Rectangle(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);										//�R���X�g���N�^
		~Rectangle();																									//�f�X�g���N�^

		void Draw(glm::vec2 start, glm::vec2 end, float r, glm::vec2 s, glm::vec4 color);	// �`��		
	private:

		//�h��Ԃ���`
		Transform_2D::VertexColor rectangleVertex[6] =
		{
			//���_�A���_�F
			{-0.5f,0.5f,    0.0f,1.0f,0.0f,1.0f},
			{-0.5f,-0.5f,	0.0f,1.0f,0.0f,1.0f},
			{0.5f,0.5f,		0.0f,1.0f,0.0f,1.0f},

			{0.5f,0.5f,		 0.0f,1.0f,0.0f,1.0f},
			{-0.5f,-0.5f,    0.0f,1.0f,0.0f,1.0f},
			{0.5f,-0.5f,     0.0f,1.0f,0.0f,1.0f},
		};


		void setVertexALLColor(glm::vec4 color);			//���_�J���[��S���ݒ�
		void setVertexColor(int vertNum, glm::vec4 color);	//���_�J���[����ݒ�

		bool vertexColorFrag;


		std::shared_ptr<Window> windowContext;	//�E�C���h�E�R���e�L�X�g

	};
}


#endif

