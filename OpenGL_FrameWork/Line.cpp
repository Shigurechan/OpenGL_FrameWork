#include "Line.hpp"
#include "Window.hpp"


//コンストラクタ
FrameWork::Line::Line(std::shared_ptr<Window> w, const char* vert, const char* frag) : Transform_2D(),Shader()
{

	windowContext = w;	//ウインドウコンテキスト


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

	//頂点情報

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//頂点	
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");

	//頂点カラー
	attrib = getAttribLocation("vertexColor");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribFragment("vertexColor");



	//アルファブレンド有効
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


//描画
void FrameWork::Line::Draw(glm::vec2 start, glm::vec2 end, glm::vec4 color)
{
	if (isDefaultShader == true)
	{
		setEnable();
	}

	//頂点属性の　色と頂点座標を設定
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



	
	glBindVertexArray(vao);


	if (isDefaultShader == true)
	{
		//頂点	
		GLint attrib = getAttribLocation("vertexPosition");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		setBindAttribVertex("vertexPosition");

		
		//頂点カラー
		attrib = getAttribLocation("vertexColor");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
		setBindAttribFragment("vertexColor");
	}


	//Transform
	setTranslate(glm::vec3(0.0f, 0.0f, 0.0f));	//平行移動

	//Uniform		
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));

	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);


	if (isDefaultShader == true)
	{
		setDisable();
	}
}



//頂点カラー描画
void FrameWork::Line::DrawColor(glm::vec2 start, glm::vec2 end,glm::vec4 startColor, glm::vec4 endColor)
{
	if (isDefaultShader == true)
	{
		setEnable();
	}

	//頂点属性の　色と頂点座標を設定
	float c = 1.0f / 255.0f;
	vertex[0].position[0] = start.x;
	vertex[0].position[1] = start.y;
	vertex[0].color[0] = startColor.x * c;
	vertex[0].color[1] = startColor.y * c;
	vertex[0].color[2] = startColor.z * c;
	vertex[0].color[3] = startColor.w * c;

	vertex[1].position[0] = end.x;
	vertex[1].position[1] = end.y;
	vertex[1].color[0] = endColor.x * c;
	vertex[1].color[1] = endColor.y * c;
	vertex[1].color[2] = endColor.z * c;
	vertex[1].color[3] = endColor.w * c;




	glBindVertexArray(vao);


	if (isDefaultShader == true)
	{
		//頂点	
		GLint attrib = getAttribLocation("vertexPosition");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		setBindAttribVertex("vertexPosition");


		//頂点カラー
		attrib = getAttribLocation("vertexColor");
		glEnableVertexAttribArray(attrib);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(VertexColor), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
		setBindAttribFragment("vertexColor");
	}


	//Transform
	setTranslate(glm::vec3(0.0f, 0.0f, 0.0f));	//平行移動

	//Uniform		
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));

	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);


	if (isDefaultShader == true)
	{
		setDisable();
	}
}










//デストラクタ
FrameWork::Line::~Line()
{

}



