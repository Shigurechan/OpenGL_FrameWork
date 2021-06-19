#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.hpp"
#include "FrameWork.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Camera::Camera()
{
	//ビュー
	vecPosition = glm::vec3(0, 0, 1);	//座標
	vecLook = glm::vec3(0, 0, -1);		//向き
	
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0,1,0));
	projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);	//透視射形
}

// ##################################### 座標を設定　##################################### 
void FrameWork::Camera::setPosition(glm::vec3 p)
{
	vecPosition = p;	//座標
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));
}

// ##################################### 視線を設定 ##################################### 
void FrameWork::Camera::setLook(glm::vec3 l)
{
	vecLook = l;		//向き
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));
}

// ##################################### 座標を取得 ##################################### 
glm::vec3 FrameWork::Camera::getPosition()
{
	return vecPosition;
}

// #####################################　視線を取得 ##################################### 
glm::vec3 FrameWork::Camera::getLook()
{
	return vecLook;
}

// ##################################### 3D ビュー行列を取得　透視射形行列 ##################################### 
glm::mat4 FrameWork::Camera::getViewProjection()
{
	return projection * view;
}

// ##################################### ２D ビュー行列を取得 正射形　##################################### 
glm::mat4 FrameWork::Camera::getProjection_2D()
{
	return glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f);
}

// ###################### デストラクタ ###################### 
FrameWork::Camera::~Camera()
{

}
