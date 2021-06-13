#include "Rectangle.hpp"
#include "Window.hpp"
#include "Shader.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Rectangle::Rectangle(std::shared_ptr<Window> w, const char* vert, const char* frag) : Transform_2D(), Shader()
{	
	windowContext = w;	//�E�C���h�E�R���e�L�X�g

	if (vert == NULL && frag == NULL)
	{
		vert = "Shader/2D/BasicMono_VertColor_2D.vert";
		frag = "Shader/2D/BasicMono_VertColor_2D.frag";
		LoadShader(vert,frag);
		isDefaultShader = true;
	}
	else
	{
		LoadShader(vert, frag);
		isDefaultShader = false;
	}
	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//���_	
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexColor), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");
	
	//���_�J���[
	attrib = getAttribLocation("vertexColor");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexColor), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribVertex("vertexColor");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//�A���t�@�u�����h�L��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// ##################################### �`�� ##################################### 
void FrameWork::Rectangle::Draw(glm::vec2 start,glm::vec2 end,float r,glm::vec2 s,glm::vec4 color)
{
	if (isDefaultShader == true) { setEnable(); }
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (isDefaultShader == true)
	{
		setVertexALLColor(color);	//���_�F��ݒ�
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexUV) * 6, rectangleVertex);

	}

	//Transform
	setSizeScale(glm::vec2((end.x - start.x), (end.y - start.y)));			//�T�C�Y	
	setScale(s);															//�X�P�[��
	setRotate(r);															//��]
	setTranslate(glm::vec3(start.x + (getSizeScale().x / 2.0f), start.y + (getSizeScale().y / 2.0f)  , 0.0f));	//���s�ړ�

	//Uniform		
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (isDefaultShader == true) { setDisable(); }
}

// ##################################### ���_�J���[���Đݒ� ##################################### 
void FrameWork::Rectangle::setVertexALLColor(glm::vec4 color)
{
	float c = 1.0f / 255.0f;

	rectangleVertex[0].color[0] = c * color.x;
	rectangleVertex[0].color[1] = c * color.y;
	rectangleVertex[0].color[2] = c * color.z;
	rectangleVertex[0].color[3] = c * color.w;

	rectangleVertex[1].color[0] = c * color.x;
	rectangleVertex[1].color[1] = c * color.y;
	rectangleVertex[1].color[2] = c * color.z;
	rectangleVertex[1].color[3] = c * color.w;

	rectangleVertex[2].color[0] = c * color.x;
	rectangleVertex[2].color[1] = c * color.y;
	rectangleVertex[2].color[2] = c * color.z;
	rectangleVertex[2].color[3] = c * color.w;

	rectangleVertex[3].color[0] = c * color.x;
	rectangleVertex[3].color[1] = c * color.y;
	rectangleVertex[3].color[2] = c * color.z;
	rectangleVertex[3].color[3] = c * color.w;

	rectangleVertex[4].color[0] = c * color.x;
	rectangleVertex[4].color[1] = c * color.y;
	rectangleVertex[4].color[2] = c * color.z;
	rectangleVertex[4].color[3] = c * color.w;

	rectangleVertex[5].color[0] = c * color.x;
	rectangleVertex[5].color[1] = c * color.y;
	rectangleVertex[5].color[2] = c * color.z;
	rectangleVertex[5].color[3] = c * color.w;
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Rectangle::~Rectangle()
{

}