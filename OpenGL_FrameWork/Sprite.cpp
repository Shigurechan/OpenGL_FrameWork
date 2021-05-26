#include "Sprite.hpp"

#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_Transform.hpp"
#include "glm/gtx/Transform.hpp"

#include "Texture.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "stb/stb_image.h"


//�R���X�g���N�^
FrameWork::Sprite::Sprite(std::shared_ptr<Window> w,const char* vert,const char* frag) : Transform_2D(),Shader()
{
	windowContext = w;	//�E�C���h�E�R���e�L�X�g


	//�V�F�[�_�[�ǂݍ���
	if (vert == NULL && frag == NULL)
	{
		vert = "Shader/2D/BasicTexture_2D.vert";
		frag = "Shader/2D/BasicTexture_2D.frag";
		LoadShader(vert, frag);	//�V�F�[�_�[���[�h

		isDefaultShader = true;
	}
	else 
	{
		LoadShader(vert, frag);

		isDefaultShader = false;

	}

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
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");

	//UV
	attrib = getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribVertex("vertexUV");


	//�A���t�@�u�����h�L��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


// ######################################## �����o�֐� ######################################## 

//�e�N�X�`���ݒ�
void FrameWork::Sprite::setTexture(TextureData tex)
{
	
	textureID.push_back(tex);	//�e�N�X�`���[ID�ɒǉ�

	
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

	textureID.back().textureUnitNumber = GL_TEXTURE0 + (unsigned short int)textureUnitCount;
	assert(textureID.back().textureUnitNumber < GL_TEXTURE31);//�G���[�\��

	textureUnitCount++;	//�e�N�X�`���[���j�b�g�J�E���g�ɉ��Z
}

//�`�悷��A�N�e�B�u�ȃe�N�X�`���Ɏw��
void FrameWork::Sprite::setDrawTextureID(unsigned char id)
{
	//assert(id < textureID.size());
	glActiveTexture(textureID.at(id).textureUnitNumber);	
}

//�`��
void FrameWork::Sprite::DrawGraph(glm::vec2 pos, unsigned char texNum,float r,glm::vec2 s,glm::vec2 startSize,glm::vec2 endSize)
{
	if (isDefaultShader == true)
	{
		setEnable();
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	setDrawTextureID((unsigned char)texNum);	//�e�N�`���[���j�b�g��ݒ�

	// ####################### ���_������UV�f�[�^���X�V  #######################
	// 	
	//UV�T�C�Y����s�N�Z���T�C�Y���Z�o
	const float sizeX = 1.0f / (float)textureID.at(texNum).size.x;
	const float sizeY = 1.0f / (float)textureID.at(texNum).size.y;
//	std::cout << sizeX << std::endl;
	//std::cout << textureID.at(texNum).size.x << std::endl;
	//std::cout << textureID.at(texNum).size.y << std::endl;

	//std::cout << GL_BUFFER_SIZE << std::endl;
	//std::cout<< sizeX << std::endl;
	//����
	rectangleVertex[0].uv[0] = sizeX * startSize.x;
	rectangleVertex[0].uv[1] = 1.0f - (sizeY * startSize.y) * -1;

	//����
	rectangleVertex[1].uv[0] = sizeX * startSize.x;
	rectangleVertex[1].uv[1] = 1.0f - (sizeY * ((endSize.y - startSize.y) + startSize.y)) * -1;
	rectangleVertex[4].uv[0] = sizeX * startSize.x;
	rectangleVertex[4].uv[1] = 1.0f - (sizeY * ((endSize.y - startSize.y) + startSize.y)) * -1;

	//�E��
	rectangleVertex[2].uv[0] = (sizeX * endSize.x);
	rectangleVertex[2].uv[1] = 1.0f - (sizeY * startSize.y) * -1;
	rectangleVertex[3].uv[0] = (sizeX * endSize.x);
	rectangleVertex[3].uv[1] = 1.0f - (sizeY * startSize.y) * -1;

	//�E��
	rectangleVertex[5].uv[0] = sizeX * endSize.x;
	rectangleVertex[5].uv[1] = 1.0f - (sizeY * ((endSize.y - startSize.y) + startSize.y)) * -1;


	//std::cout << rectangleVertex[2].uv[0] << std::endl;
	//std::cout<< rectangleVertex[1].uv[0] <<std::endl;
	//printf("%f\n", rectangleVertex[2].uv[0]);
	//printf("%f\n", rectangleVertex[1].uv[0]);


	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexUV) * 6, rectangleVertex);
	//  ################################################### 


	
	//std::cout << windowContext->getSize().x << std::endl;

	//Transform
	//printf("%f\n", rectangleVertex[2].uv[0]);
	setSizeScale(glm::vec2(std::abs((endSize.x - startSize.x)), (std::abs(endSize.y - startSize.y))));			//�T�C�Y	
	setScale(s);																								//�X�P�[��
	setRotate(r);																								//��]
	setTranslate(glm::vec3(pos.x + (getSizeScale().x / 2.0f), pos.y + (getSizeScale().y / 2.0f), 0.0f));		//���s�ړ�
	
	//uniform
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	


	//�o�C���h���`��
	glBindTexture(GL_TEXTURE_2D, textureID.at(texNum).ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	


	if (isDefaultShader == true)
	{
		setDisable();
	}

	//�o�C���h������
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}


//�f�X�g���N�^
FrameWork::Sprite::~Sprite()
{

	//std::cout << "�f�X�g���N�^" << std::endl;

	//�e�N�X�`���[ID���J��
	for (int i = 0; i < textureID.size(); i++)
	{
		glDeleteTextures(1,&textureID.at(i).ID);
	
		stbi_image_free(textureID.at(i).fileData);
		textureID.at(i).fileData = NULL;



	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	
}

