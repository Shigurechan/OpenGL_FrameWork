#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Window.hpp"



// ###################### コンストラクタ ###################### 
FrameWork::Camera::Camera(std::shared_ptr<Window> w)
{
	windowContext = w;	//ウインドウコンテキスト

	//ビュー
	vecPosition = glm::vec3(0, 0, 1);	//座標
	vecLook = glm::vec3(0, 0, -1);		//向き
	
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0,1,0));


	projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);	//透視射形
	

}

// ###################### 設定　関係 ###################### 

//座標
void FrameWork::Camera::setPosition(glm::vec3 p)
{
	vecPosition = p;	//座標
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));

}

//視線
void FrameWork::Camera::setLook(glm::vec3 l)
{
	vecLook = l;		//向き
	view = glm::lookAt(vecPosition, vecLook, glm::vec3(0, 1, 0));

}
// ###################### 取得　関係 ###################### 

//座標
glm::vec3 FrameWork::Camera::getPosition()
{
	return vecPosition;
}

//視線
glm::vec3 FrameWork::Camera::getLook()
{
	return vecLook;
}

//カメラ行列を取得

//3Dカメラ
glm::mat4 FrameWork::Camera::getViewProjection()
{
	return projection * view;
}

//2Dカメラ
glm::mat4 FrameWork::Camera::getProjection_2D()
{
	return glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f);
}



// ###################### デストラクタ ###################### 
FrameWork::Camera::~Camera()
{

}
