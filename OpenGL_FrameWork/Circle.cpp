#include "Circle.hpp"

#include "Window.hpp"
#include "FrameWork.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Circle::Circle() : Transform_2D()
{
	vertex.resize(100);		//頂点配列

	shader->Load("Shader/2D/BasicMono_2D.vert","Shader/2D/BasicMono_2D.frag");
	
	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), vertex.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

// ##################################### 描画 ##################################### 
void FrameWork::Circle::Draw(glm::vec2 pos, int num, float r,glm::vec4 color)
{
	shader->setEnable();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	if (vertex.size() != num)
	{
		//vertex.clear();
		vertex.resize(num);
		float n = (PI * 2.0f) / (float)vertex.size();
		float t = 0.0f;
		for (int i = 0; i < vertex.size(); i++)
		{
			vertex.at(i).position[0] = cos(t) * r;
			vertex.at(i).position[1] = sin(t) * r;
			t += n;
		}
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex.size() * sizeof(Vertex), vertex.data());


	//Transform
	setTranslate(glm::vec3(pos.x + r, pos.y + r, 0.0f));					//平行移動

	//Uniform		
	float c = 1.0f / 255.0f;
	shader->setUniform4f("uFragment", color * c);			//カラー
	shader->setUniformMatrix4fv("uTranslate", translate);	//平行移動
	shader->setUniformMatrix4fv("uRotate", rotate);			//回転
	shader->setUniformMatrix4fv("uScale", scale);			//スケール
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f));	//ビュープロジェクション


	
	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)vertex.size());

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->setDisable();
}

// ##################################### デストラクタ ##################################### 
FrameWork::Circle::~Circle()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}

