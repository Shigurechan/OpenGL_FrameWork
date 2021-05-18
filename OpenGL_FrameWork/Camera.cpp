#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Window.hpp"



// ###################### �R���X�g���N�^ ###################### 
FrameWork::Camera::Camera(std::shared_ptr<Window> w)
{
	windowContext = w;	//�E�C���h�E�R���e�L�X�g

	//�r���[
	vecPosition = glm::vec3(0, 0, 1);	//���W
	vecLook = glm::vec3(0, 0, -1);		//����
	
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0,1,0));


	projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);	//�����ˌ`
	

}

// ###################### �ݒ�@�֌W ###################### 

//���W
void FrameWork::Camera::setPosition(glm::vec3 p)
{
	vecPosition = p;	//���W
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));

}

//����
void FrameWork::Camera::setLook(glm::vec3 l)
{
	vecLook = l;		//����
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));

}
// ###################### �擾�@�֌W ###################### 

//���W
glm::vec3 FrameWork::Camera::getPosition()
{
	return vecPosition;
}

//����
glm::vec3 FrameWork::Camera::getLook()
{
	return vecLook;
}

//�J�����s����擾

//3D�J����
glm::mat4 FrameWork::Camera::getViewProjection()
{
	return projection * view;
}

//2D�J����
glm::mat4 FrameWork::Camera::getProjection_2D()
{
	return glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f);
}



// ###################### �f�X�g���N�^ ###################### 
FrameWork::Camera::~Camera()
{

}