#include "Sprite.hpp"

#include <iostream>
#include <fstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_Transform.hpp"
#include "glm/gtx/Transform.hpp"
#include "Texture.hpp"
#include "FrameWork.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "stb/stb_image.h"

// ##################################### コンストラクタ ##################################### 
FrameWork::Sprite::Sprite() : Transform_2D()
{
	//シェーダー読み込み
	shader->Load("Shader/2D/BasicTexture_2D.vert", "Shader/2D/BasicTexture_2D.frag");	//シェーダーロード

	//テクスチャ関係	
	textureID = std::vector<TextureData>(0);	//テクスチャーデータ
	textureUnitCount = 0;						//テクスチャユニット数をカウント
	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//頂点	
	GLint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	shader->setBindAttribLocation("vertexPosition");

	//UV
	attrib = shader->getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	shader->setBindAttribLocation("vertexUV");

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

// ##################################### テクスチャを設定 ##################################### 
void FrameWork::Sprite::setTexture(TextureData tex)
{	
	textureID.push_back(tex);				//テクスチャーIDに追加	
	glGenTextures(1, &textureID.back().ID);	//テクスチャIDの生成

	//バインド
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureID.back().ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureID.back().size.x, textureID.back().size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureID.back().fileData);

	// テクスチャの補間設定
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	textureID.back().textureUnitNumber = GL_TEXTURE0 + (int)textureUnitCount;

	//テクスチャユニットを設定できない場合はエラー
	assert(textureID.back().textureUnitNumber < GL_TEXTURE31);

	textureUnitCount++;	//テクスチャーユニットカウントに加算
}

// ##################################### テクスチャサイズを取得 ##################################### 
glm::vec2 FrameWork::Sprite::getTextureSize(unsigned char id)
{
	return textureID.at(id).size;
}

// ##################################### 描画するアクティブなテクスチャに指定 ##################################### 
void FrameWork::Sprite::setDrawTextureID(unsigned char id)
{
	if (id < textureID.size())
	{
		glActiveTexture(textureID.at(id).textureUnitNumber);
	}
	else 
	{
		std::cerr << "テクスチャユニット番号を超えています。" << std::endl;
		//assert(0);
	}
}

// ##################################### 描画 ##################################### 
void FrameWork::Sprite::DrawGraph(glm::vec2 pos, unsigned char texNum,float r,glm::vec2 s,glm::vec2 startSize,glm::vec2 endSize)
{
	shader->setEnable();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// ####################### 頂点属性のUVデータを更新  #######################	
	//UVサイズからピクセルサイズを算出
	const float sizeX = 1.0f / (float)textureID.at(texNum).size.x;
	const float sizeY = 1.0f / (float)textureID.at(texNum).size.y;

	//左上
	rectangleVertex[0].uv[0] = sizeX * startSize.x;
	rectangleVertex[0].uv[1] = sizeY * endSize.y;

	//左下
	rectangleVertex[1].uv[0] = sizeX * startSize.x;
	rectangleVertex[1].uv[1] = sizeY * startSize.y;
	rectangleVertex[4].uv[0] = sizeX * startSize.x;
	rectangleVertex[4].uv[1] = sizeY * startSize.y;

	//右上
	rectangleVertex[2].uv[0] = sizeX * endSize.x;
	rectangleVertex[2].uv[1] = sizeY * endSize.y;
	rectangleVertex[3].uv[0] = sizeX * endSize.x;
	rectangleVertex[3].uv[1] = sizeY * endSize.y;

	//右下
	rectangleVertex[5].uv[0] = sizeX * endSize.x;
	rectangleVertex[5].uv[1] = sizeY * startSize.y;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexUV) * 6, rectangleVertex);
	//  ################################################### 

	//Transform
	setSizeScale(glm::vec2(std::abs((endSize.x - startSize.x)), (std::abs(endSize.y - startSize.y))));			//サイズ	
	setScale(s);																								//スケール
	setRotate(r);																								//回転
	setTranslate(glm::vec3(pos.x + (getSizeScale().x / 2.0f), pos.y + (getSizeScale().y / 2.0f), 0.0f));		//平行移動
	
	//uniform
	shader->setUniformMatrix4fv("uTranslate", translate);
	shader->setUniformMatrix4fv("uRotate", rotate);
	shader->setUniformMatrix4fv("uScale", scale);
	shader->setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, FrameWork::getWindowContext()->getSize().x, FrameWork::getWindowContext()->getSize().y, 0.0f, -1.0f, 1.0f));

	//バインド＆描画	
	glBindTexture(GL_TEXTURE_2D, textureID.at(texNum).ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//バインドを解除
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->setDisable();
}


// ##################################### デストラクタ ##################################### 
FrameWork::Sprite::~Sprite()
{
	for (int i = 0; i < textureID.size(); i++)
	{
		glDeleteTextures(1,&textureID.at(i).ID);		//テクスチャIDを解放
		stbi_image_free(textureID.at(i).fileData);		//テクスチャを開放
		textureID.at(i).fileData = NULL;				//テクスチャポインタをNULL
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}

