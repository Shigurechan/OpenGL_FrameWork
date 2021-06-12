#include "Circle.hpp"

#include "Window.hpp"
#include "FrameWork.hpp"


// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Circle::Circle(std::shared_ptr<Window> w,const char* vert, const char* frag) : Transform_2D(),Shader()
{
	windowContext = w;	//�E�C���h�E�R���e�L�X�g
	vertex.resize(100);		//���_�z��

	if (vert == NULL && frag == NULL)
	{
		vert = "Shader/2D/BasicMono_VertColor_2D.vert";
		frag = "Shader/2D/BasicMono_VertColor_2D.frag";
		LoadShader(vert, frag);
		isDefaultShader = true;
	}
	else
	{
		LoadShader(vert, frag);
		isDefaultShader = false;
	}

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//���_	
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexColor), vertex.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");

	//���_�J���[
	attrib = getAttribLocation("vertexColor");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexColor), vertex.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribVertex("vertexColor");

	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);	//�A���t�@�u�����h�L��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//�u�����h�^�C�v
}

// ##################################### �`�� ##################################### 
void FrameWork::Circle::Draw(glm::vec2 pos, int num, float r,glm::vec4 color)
{
	if (isDefaultShader == true) { setEnable(); }
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	if (vertex.size() != num)
	{
		vertex.resize(num);
		float c = 1.0f / 255.0f;
		float n = (PI * 2.0f) / (float)vertex.size();
		float t = 0.0f;
		for (int i = 0; i < vertex.size(); i++)
		{
			vertex.at(i).position[0] = cos(t) * r;
			vertex.at(i).position[1] = sin(t) * r;

			vertex.at(i).color[0] = c * color.x;
			vertex.at(i).color[1] = c * color.y;
			vertex.at(i).color[2] = c * color.z;
			vertex.at(i).color[3] = c * color.w;

			t += n;
		}

		glBufferSubData(GL_ARRAY_BUFFER, 0, vertex.size() * sizeof(VertexColor), vertex.data());
	}


	//Transform
	setTranslate(glm::vec3(pos.x + r, pos.y + r, 0.0f));	//���s�ړ�

	//Uniform		
	setUniformMatrix4fv("uTranslate", translate);		//���s�ړ�
	setUniformMatrix4fv("uRotate", rotate);				//��]
	setUniformMatrix4fv("uScale", scale);				//�X�P�[��
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));	//�r���[�v���W�F�N�V����

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)vertex.size());

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (isDefaultShader == true) { setDisable(); }
}



// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Circle::~Circle()
{

}

