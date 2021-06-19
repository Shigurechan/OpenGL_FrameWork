#include "Line.hpp"
#include "Window.hpp"
#include "FrameWork.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Line::Line() : Transform_2D()
{
	shader->Load("Shader/2D/BasicMono_2D.vert","Shader/2D/BasicMono_2D.frag");

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//頂点
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ##################################### 描画 ##################################### 
void FrameWork::Line::Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color)
{
	shader->setEnable();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vertex[0].position[0] = start.x;
	vertex[0].position[1] = start.y;
	
	vertex[1].position[0] = end.x;
	vertex[1].position[1] = end.y;
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(Vertex), &vertex);

	//Transform
	setTranslate(glm::vec3(0.0f, 0.0f, 0.0f));	//平行移動

	//Uniform		
	float c = 1.0f / 255.0f;
	shader->setUniform4f("uFragment", color * c);
	shader->setUniformMatrix4fv("uTranslate", translate);
	shader->setUniformMatrix4fv("uRotate", rotate);
	shader->setUniformMatrix4fv("uScale", scale);
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f));

	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->setDisable();
}

// ##################################### デストラクタ ##################################### 
FrameWork::Line::~Line()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}



