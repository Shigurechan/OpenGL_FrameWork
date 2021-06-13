#include "Line.hpp"
#include "Window.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Line::Line(std::shared_ptr<Window> w, const char* vert, const char* frag) : Transform_2D(),Shader()
{
	windowContext = w;	//�E�C���h�E�R���e�L�X�g

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

	//���_	
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");

	//���_�J���[
	attrib = getAttribLocation("vertexColor");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribFragment("vertexColor");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//�A���t�@�u�����h�L��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// ##################################### �`�� ##################################### 
void FrameWork::Line::Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color)
{
	if (isDefaultShader == true) { setEnable(); }

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//���_�����́@�F�ƒ��_���W��ݒ�
	float c = 1.0f / 255.0f;
	vertex[0].position[0] = start.x;
	vertex[0].position[1] = start.y;
	vertex[0].color[0] = color.x * c;
	vertex[0].color[1] = color.y * c;
	vertex[0].color[2] = color.z * c;
	vertex[0].color[3] = color.w * c;
	
	vertex[1].position[0] = end.x;
	vertex[1].position[1] = end.y;
	vertex[1].color[0] = color.x * c;
	vertex[1].color[1] = color.y * c;
	vertex[1].color[2] = color.z * c;
	vertex[1].color[3] = color.w * c;

	glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(VertexColor), &vertex);

	//Transform
	setTranslate(glm::vec3(0.0f, 0.0f, 0.0f));	//���s�ړ�

	//Uniform		
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));

	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (isDefaultShader == true) { setDisable(); }
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Line::~Line()
{

}



