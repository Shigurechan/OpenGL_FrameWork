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

	class Line : protected FrameWork::Transform_2D, public Shader
	{
	public:
		Line(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);		//�R���X�g���N�^
		~Line();																										//�f�X�g���N�^

		void Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color);													//�`��
		void DrawColor(glm::vec2 start, glm::vec2 end, glm::vec4 startColor, glm::vec4 endColor);					//�`��


	private:

		Transform_2D::VertexColor vertex[2] =
		{
			{-0.5f,-0.5f,	0.0f,1.0f,0.0f,1.0f},
			{0.5f,0.5f,		0.0f,1.0f,0.0f,1.0f}
		};


		std::shared_ptr<Window> windowContext;	//�E�C���h�E�R���e�L�X�g
	};
}
#endif
