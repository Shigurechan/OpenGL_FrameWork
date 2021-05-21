#include "Circle.hpp"
#include "Window.hpp"
#include "FrameWork.hpp"
//�R���X�g���N�^
FrameWork::Circle::Circle(std::shared_ptr<Window> w,const char* vert, const char* frag) : Transform_2D(),Shader()
{
	windowContext = w;	//�E�C���h�E�R���e�L�X�g

	vertex = std::vector<Transform_2D::VertexColor>();	//���_�����z��

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

	//���_���

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//�A���t�@�u�����h�L��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




//�`��
void FrameWork::Circle::Draw(glm::vec2 pos, int num, float r,glm::vec4 color)
{
	if (isDefaultShader == true) 
	{
		setEnable();
	}

	if (count != num) 
	{
		count = num;
		vertex.resize(num);
		float c = 1.0f / 255.0f;
		float n = (PI * 2.0f) / (float)num;
		float t = 0.0f;
		for (int i = 0; i < num; i++)
		{
			
			vertex.at(i).position[0] = cos(t) * r;
			vertex.at(i).position[1] = sin(t) * r;

			vertex.at(i).color[0] = c * color.x;
			vertex.at(i).color[1] = c * color.y;
			vertex.at(i).color[2] = c * color.z;
			vertex.at(i).color[3] = c * color.w;
			
			t += n;
		}
	}

	//���_	
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(VertexColor), vertex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");

	//���_�J���[
	attrib = getAttribLocation("vertexColor");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(VertexColor), vertex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribFragment("vertexColor");
	
	//Transform
	setTranslate(glm::vec3(pos.x + r, pos.y + r, 0.0f));	//���s�ړ�

	//Uniform		
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));

	glDrawArrays(GL_TRIANGLE_FAN, 0, num);
	glBindVertexArray(0);
	if (isDefaultShader == true) 
	{
		setDisable();
	}

}









//�f�X�g���N�^
FrameWork::Circle::~Circle()
{

}

