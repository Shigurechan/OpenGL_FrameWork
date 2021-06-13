#ifndef ___Transform_2D_HPP_
#define ___Transform_2D_HPP_
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_Transform.hpp>
#include <glm/gtx/Transform.hpp>
#include <glew/include/GL/glew.h>
/*#########################################################################
# �g�����X�t�H�[���N���X: Actor�N���X���p��

����
	�S�Ă�2D�`�敨�͂�����p������
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Transform_2D
	{

	public:

		Transform_2D();		//�R���X�g���N�^
		~Transform_2D();	//�f�X�g���N�^

	protected:

		// ###################### Transform_2D�@�ݒ� ###################### 
		void setScale(glm::vec2 s);				//�X�P�[��
		void setRotate(float a);				//��]
		void setTranslate(glm::vec3 t);			//���s�ړ�
		glm::vec2 getSizeScale();				//�T�C�Y���擾
		void setSizeScale(glm::vec2 s);			//�T�C�Y��ݒ�

		//���_���W��UV
		struct VertexUV
		{
			GLfloat position[2];
			GLfloat uv[2];

		};

		//���_���W
		struct Vertex
		{
			GLfloat position[2];
		};

		//���_���W�ƒ��_�J���[
		struct VertexColor
		{
			GLfloat position[2];
			GLfloat color[4];
		};

		GLuint vao;							//VertexArrayObject
		GLuint vbo;							//VertexBufferObject	

		bool isDefaultShader;	//����̃V�F�[�_�[�t�@�C�����I�΂ꂽ���ǂ����H

		//�`��s��
		glm::mat4 scale;		//�g��k��
		glm::mat4 rotate;		//��]
		glm::mat4 translate;	//���s�ړ�

	private:

		glm::vec2 size;			//�摜�T�C�Y
	};
}
#endif
