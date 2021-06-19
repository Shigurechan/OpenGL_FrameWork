#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.hpp"
#include "FrameWork.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Camera::Camera()
{
	//�r���[
	vecPosition = glm::vec3(0, 0, 1);	//���W
	vecLook = glm::vec3(0, 0, -1);		//����
	
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0,1,0));
	projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);	//�����ˌ`
}

// ##################################### ���W��ݒ�@##################################### 
void FrameWork::Camera::setPosition(glm::vec3 p)
{
	vecPosition = p;	//���W
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));
}

// ##################################### ������ݒ� ##################################### 
void FrameWork::Camera::setLook(glm::vec3 l)
{
	vecLook = l;		//����
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));
}

// ##################################### ���W���擾 ##################################### 
glm::vec3 FrameWork::Camera::getPosition()
{
	return vecPosition;
}

// #####################################�@�������擾 ##################################### 
glm::vec3 FrameWork::Camera::getLook()
{
	return vecLook;
}

// ##################################### 3D �r���[�s����擾�@�����ˌ`�s�� ##################################### 
glm::mat4 FrameWork::Camera::getViewProjection()
{
	return projection * view;
}

// ##################################### �QD �r���[�s����擾 ���ˌ`�@##################################### 
glm::mat4 FrameWork::Camera::getProjection_2D()
{
	return glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f);
}

// ###################### �f�X�g���N�^ ###################### 
FrameWork::Camera::~Camera()
{

}
