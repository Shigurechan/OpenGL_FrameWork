#include "Transform_2D.hpp"
#include "Shader.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Transform_2D::Transform_2D()
{
	shader = std::make_unique<FrameWork::Shader>();

	size = glm::vec2(0,0);
	vao = 0;
	vbo = 0;
	isDefaultShader = false;

	//行列を初期化
	scale = glm::scale(glm::mat4(1), glm::vec3(1.0f,1.0f,1.0f));
	rotate = glm::rotate(0.0f,glm::vec3(0.0, 0.0, 1.0));
	translate = glm::translate(glm::mat4(1), glm::vec3(0.0f,0.0f,0.0f));
}

// ##################################### スケールを設定 ##################################### 
void FrameWork::Transform_2D::setScale(glm::vec2 s)
{
	scale = glm::scale(glm::mat4(1), glm::vec3(s.x,s.y,0.0f) + glm::vec3(size.x,size.y,0.0f));
}

// ##################################### 回転を設定 ##################################### 
void FrameWork::Transform_2D::setRotate(float a)
{
	rotate = glm::rotate(glm::mat4(1), a, glm::vec3(0.0,0.0,1.0));	//回転	
}

// ##################################### 平行移動を設定 ##################################### 
void FrameWork::Transform_2D::setTranslate(glm::vec3 t)
{	
	translate = glm::translate(glm::mat4(1), t);
}

// ##################################### 画像と同じサイズに拡大 ##################################### 
void FrameWork::Transform_2D::setSizeScale(glm::vec2 s)
{
	size = s;
	scale = glm::scale(glm::mat4(1), glm::vec3(s.x, s.y, 0.0f));
}

// ##################################### 画像サイズを取得 ##################################### 
glm::vec2 FrameWork::Transform_2D::getSizeScale()
{
	return size;	
}

// ##################################### デストラクタ ##################################### 
FrameWork::Transform_2D::~Transform_2D()
{

}
