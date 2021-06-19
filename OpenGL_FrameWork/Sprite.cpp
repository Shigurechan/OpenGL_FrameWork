#include "Sprite.hpp"

#include <iostream>
#include <fstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_Transform.hpp"
#include "glm/gtx/Transform.hpp"
#include "Texture.hpp"
#include "FrameWork.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "stb/stb_image.h"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Sprite::Sprite() : Transform_2D()
{
	//�V�F�[�_�[�ǂݍ���
	shader->Load("Shader/2D/BasicTexture_2D.vert", "Shader/2D/BasicTexture_2D.frag");	//�V�F�[�_�[���[�h

	//�e�N�X�`���֌W	
	textureID = std::vector<TextureData>(0);	//�e�N�X�`���[�f�[�^
	textureUnitCount = 0;						//�e�N�X�`�����j�b�g�����J�E���g
	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//���_	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

	//UV
	attrib = shader->getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	shader->setBindAttribLocation("vertexUV");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

// ##################################### �e�N�X�`����ݒ� ##################################### 
void FrameWork::Sprite::setTexture(TextureData tex)
{	
	textureID.push_back(tex);				//�e�N�X�`���[ID�ɒǉ�	
	glGenTextures(1, &textureID.back().ID);	//�e�N�X�`��ID�̐���

	//�o�C���h
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureID.back().ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureID.back().size.x, textureID.back().size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureID.back().fileData);

	// �e�N�X�`���̕�Ԑݒ�
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	textureID.back().textureUnitNumber = GL_TEXTURE0 + (int)textureUnitCount;

	//�e�N�X�`�����j�b�g��ݒ�ł��Ȃ��ꍇ�̓G���[
	assert(textureID.back().textureUnitNumber < GL_TEXTURE31);

	textureUnitCount++;	//�e�N�X�`���[���j�b�g�J�E���g�ɉ��Z
}

// ##################################### �e�N�X�`���T�C�Y���擾 ##################################### 
glm::vec2 FrameWork::Sprite::getTextureSize(unsigned char id)
{
	return textureID.at(id).size;
}

// ##################################### �`�悷��A�N�e�B�u�ȃe�N�X�`���Ɏw�� ##################################### 
void FrameWork::Sprite::setDrawTextureID(unsigned char id)
{
	if (id < textureID.size())
	{
		glActiveTexture(textureID.at(id).textureUnitNumber);
	}
	else 
	{
		std::cerr << "�e�N�X�`�����j�b�g�ԍ��𒴂��Ă��܂��B" << std::endl;
		//assert(0);
	}
}

// ##################################### �`�� ##################################### 
void FrameWork::Sprite::DrawGraph(glm::vec2 pos, unsigned char texNum,float r,glm::vec2 s,glm::vec2 startSize,glm::vec2 endSize)
{
	shader->setEnable();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// ####################### ���_������UV�f�[�^���X�V  #######################	
	//UV�T�C�Y����s�N�Z���T�C�Y���Z�o
	const float sizeX = 1.0f / (float)textureID.at(texNum).size.x;
	const float sizeY = 1.0f / (float)textureID.at(texNum).size.y;

	//����
	rectangleVertex[0].uv[0] = sizeX * startSize.x;
	rectangleVertex[0].uv[1] = sizeY * endSize.y;

	//����
	rectangleVertex[1].uv[0] = sizeX * startSize.x;
	rectangleVertex[1].uv[1] = sizeY * startSize.y;
	rectangleVertex[4].uv[0] = sizeX * startSize.x;
	rectangleVertex[4].uv[1] = sizeY * startSize.y;

	//�E��
	rectangleVertex[2].uv[0] = sizeX * endSize.x;
	rectangleVertex[2].uv[1] = sizeY * endSize.y;
	rectangleVertex[3].uv[0] = sizeX * endSize.x;
	rectangleVertex[3].uv[1] = sizeY * endSize.y;

	//�E��
	rectangleVertex[5].uv[0] = sizeX * endSize.x;
	rectangleVertex[5].uv[1] = sizeY * startSize.y;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexUV) * 6, rectangleVertex);
	//  ################################################### 

	//Transform
	setSizeScale(glm::vec2(std::abs((endSize.x - startSize.x)), (std::abs(endSize.y - startSize.y))));			//�T�C�Y	
	setScale(s);																								//�X�P�[��
	setRotate(r);																								//��]
	setTranslate(glm::vec3(pos.x + (getSizeScale().x / 2.0f), pos.y + (getSizeScale().y / 2.0f), 0.0f));		//���s�ړ�
	
	//uniform
	shader->setUniformMatrix4fv("uTranslate", translate);
	shader->setUniformMatrix4fv("uRotate", rotate);
	shader->setUniformMatrix4fv("uScale", scale);
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f));

	//�o�C���h���`��	
	glBindTexture(GL_TEXTURE_2D, textureID.at(texNum).ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//�o�C���h������
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->setDisable();
}


// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Sprite::~Sprite()
{
	for (int i = 0; i < textureID.size(); i++)
	{
		glDeleteTextures(1,&textureID.at(i).ID);		//�e�N�X�`��ID�����
		stbi_image_free(textureID.at(i).fileData);		//�e�N�X�`�����J��
		textureID.at(i).fileData = NULL;				//�e�N�X�`���|�C���^��NULL
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}

