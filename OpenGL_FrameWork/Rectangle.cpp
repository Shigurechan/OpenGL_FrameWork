#include "Rectangle.hpp"

#include "FrameWork.hpp"
#include "Window.hpp"
#include "Shader.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Rectangle::Rectangle() : Transform_2D()
{	
	shader->Load("Shader/2D/BasicMono_2D.vert","Shader/2D/BasicMono_2D.frag");
	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//���_	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// ##################################### �`�� ##################################### 
void FrameWork::Rectangle::Draw(glm::vec2 start,glm::vec2 end,float r,glm::vec4 color)
{
	shader->setEnable();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	//Transform
	setSizeScale(glm::vec2((end.x - start.x), (end.y - start.y)));			//�T�C�Y	
	setScale(glm::vec2(0,0));												//�X�P�[��
	setRotate(r);															//��]
	setTranslate(glm::vec3(start.x + (getSizeScale().x / 2.0f), start.y + (getSizeScale().y / 2.0f)  , 0.0f));	//���s�ړ�

	//Uniform
	shader->setUniform4f("uFragment", color);
	shader->setUniformMatrix4fv("uTranslate", translate);
	shader->setUniformMatrix4fv("uRotate", rotate);
	shader->setUniformMatrix4fv("uScale", scale);
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f));
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->setDisable();
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Rectangle::~Rectangle()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}