#include "Transform_2D.hpp"
#include "Shader.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Transform_2D::Transform_2D()
{
	shader = std::make_unique<FrameWork::Shader>();

	size = glm::vec2(0,0);
	vao = 0;
	vbo = 0;
	isDefaultShader = false;

	//�s���������
	scale = glm::scale(glm::mat4(1), glm::vec3(1.0f,1.0f,1.0f));
	rotate = glm::rotate(0.0f,glm::vec3(0.0, 0.0, 1.0));
	translate = glm::translate(glm::mat4(1), glm::vec3(0.0f,0.0f,0.0f));
}

// ##################################### �X�P�[����ݒ� ##################################### 
void FrameWork::Transform_2D::setScale(glm::vec2 s)
{
	scale = glm::scale(glm::mat4(1), glm::vec3(s.x,s.y,0.0f) + glm::vec3(size.x,size.y,0.0f));
}

// ##################################### ��]��ݒ� ##################################### 
void FrameWork::Transform_2D::setRotate(float a)
{
	rotate = glm::rotate(glm::mat4(1), a, glm::vec3(0.0,0.0,1.0));	//��]	
}

// ##################################### ���s�ړ���ݒ� ##################################### 
void FrameWork::Transform_2D::setTranslate(glm::vec3 t)
{	
	translate = glm::translate(glm::mat4(1), t);
}

// ##################################### �摜�Ɠ����T�C�Y�Ɋg�� ##################################### 
void FrameWork::Transform_2D::setSizeScale(glm::vec2 s)
{
	size = s;
	scale = glm::scale(glm::mat4(1), glm::vec3(s.x, s.y, 0.0f));
}

// ##################################### �摜�T�C�Y���擾 ##################################### 
glm::vec2 FrameWork::Transform_2D::getSizeScale()
{
	return size;	
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Transform_2D::~Transform_2D()
{

}
