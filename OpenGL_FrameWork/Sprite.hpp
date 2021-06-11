#ifndef ___Sprite_2D_HPP
#define ___Sprite_2D_HPP


#include <iostream>
#include <glew/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Transform_2D.hpp"
#include "Shader.hpp"


/*#########################################################################
# �X�v���C�g�N���X

����
	2D�̃e�N�X�`���`��@���ˌ`
###########################################################################*/



namespace FrameWork
{
	class Window;


	class Sprite : protected FrameWork::Transform_2D, public Shader
	{
	public:

		Sprite(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);		//�R���X�g���N�^
		~Sprite();										//�f�X�g���N�^

		// ###################### �����o�֐� ###################### 	
		void DrawGraph(glm::vec2 pos, unsigned char texNum,float r, glm::vec2 s,glm::vec2 startSize, glm::vec2 endSize);	//�`��
		glm::vec2 getTextureSize(unsigned char id);	//�e�N�X�`���T�C�Y���擾
		void setTexture(TextureData tex);			//�e�N�X�`���ݒ�

	private:

		//���_���
		Transform_2D::VertexUV rectangleVertex[6] =
		{
			//���_�A���_�F
			{-0.5f,0.5f,    0.0f,1.0f},
			{-0.5f,-0.5f,	0.0f,0.0f},
			{0.5f,0.5f,		1.0f,1.0f},

			{0.5f,0.5f,		 1.0f,1.0f},
			{-0.5f,-0.5f,    0.0f,0.0f},
			{0.5f,-0.5f,     1.0f,0.0f},
		};




		void setDrawTextureID(unsigned char id);	//�`�悷��e�N�X�`���ԍ����w��

		std::vector<TextureData> textureID;	//�e�N�X�`���[ID
		unsigned char textureUnitCount;		//�e�N�X�`���[�ԍ����J�E���g

		std::shared_ptr<Window> windowContext;	//Window�R���e�L�X�g

		//bool isDefaultShader; //�f�t�H���g�V�F�[�_�[���ǂ����H
	};
}
#endif
