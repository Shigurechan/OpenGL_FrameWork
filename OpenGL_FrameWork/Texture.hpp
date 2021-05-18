#ifndef ___TEXTURE_HPP_
#define ___TEXTURE_HPP_

#include <iostream>
#include "glm/glm.hpp"
#include "glew/include/GL/glew.h"


namespace FrameWork
{

	//�e�N�X�`���f�[�^�\����
	typedef struct
	{
		glm::ivec2 size;				//�摜�T�C�Y
		unsigned char* fileData;		//�摜�f�[�^
		int channel;					//�摜�̃`�����l����
		GLuint ID;						//�e�N�X�`��ID
		GLuint textureUnitNumber;		//�e�N�X�`�����j�b�g�ԍ�
	}TextureData;

	TextureData LoadTexture(const char* fileName);	//�e�N�X�`���[���[�h
}

#endif