#include "Sprite.hpp"

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_Transform.hpp>
#include <glm/gtx/Transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include <stb/stb_image.h>


//コンストラクタ
FrameWork::Sprite::Sprite(std::shared_ptr<Window> w,const char* vert,const char* frag) : Transform_2D(),Shader()
{
	windowContext = w;	//ウインドウコンテキスト


	//シェーダー読み込み

	if (vert == NULL && frag == NULL)
	{
		vert = "Shader/2D/BasicTexture_2D.vert";
		frag = "Shader/2D/BasicTexture_2D.frag";
		LoadShader(vert, frag);	//シェーダーロード

		isDefaultShader = true;
	}
	else 
	{
		LoadShader(vert, frag);

		isDefaultShader = false;

	}

	

	//テクスチャ関係	
	textureID = std::vector<TextureData>(0);		//テクスチャーデータ
	textureUnitCount = 0;						//テクスチャユニット数をカウント

	
	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//頂点	
	GLint attrib = getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	setBindAttribVertex("vertexPosition");

	attrib = getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexUV), rectangleVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
	setBindAttribVertex("vertexUV");


	//アルファブレンド有効
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


// ######################################## メンバ関数 ######################################## 

//テクスチャ設定
void FrameWork::Sprite::setTexture(TextureData tex)
{
	
	textureID.push_back(tex);	//テクスチャーIDに追加

	
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

	//setSizeScale(glm::vec3(textureID.back().size.x, textureID.back().size.y, 1.0f));	//スプライトサイズを設定


	textureID.back().textureUnitNumber = GL_TEXTURE0 + (unsigned short int)textureUnitCount;
	assert(textureID.back().textureUnitNumber < GL_TEXTURE31);//エラー表示

	textureUnitCount++;	//テクスチャーユニットカウントに加算
}

//描画するアクティブなテクスチャに指定
void FrameWork::Sprite::setDrawTextureID(unsigned char id)
{
	//assert(id < textureID.size());
	glActiveTexture(textureID.at(id).textureUnitNumber);	
}

//描画
void FrameWork::Sprite::DrawGraph(glm::vec2 pos, unsigned char texNum,float r,glm::vec2 s,glm::vec2 startSize,glm::vec2 endSize)
{
	if (isDefaultShader == true)
	{
		setEnable();
	}

	glBindVertexArray(vao);


	setDrawTextureID((unsigned char)texNum);	//テクチャーユニットを設定

	// ####################### 頂点属性のUVデータを更新  #######################
	
	//UVサイズからピクセルサイズを算出
	const float sizeX = 1.0f / (float)textureID.at(texNum).size.x;
	const float sizeY = 1.0f / (float)textureID.at(texNum).size.y;
	//std::cout<< sizeX << std::endl;
	//左上
	rectangleVertex[0].uv[0] = sizeX * startSize.x;
	rectangleVertex[0].uv[1] = 1.0f - (sizeY * startSize.y);

	//左下
	rectangleVertex[1].uv[0] = sizeX * startSize.x;
	rectangleVertex[1].uv[1] = 1.0f - (sizeY * ((endSize.y - startSize.y) + startSize.y));
	rectangleVertex[4].uv[0] = sizeX * startSize.x;
	rectangleVertex[4].uv[1] = 1.0f - (sizeY * ((endSize.y - startSize.y) + startSize.y));

	//右上
	rectangleVertex[2].uv[0] = (sizeX * endSize.x);
	rectangleVertex[2].uv[1] = 1.0f - (sizeY * startSize.y);
	rectangleVertex[3].uv[0] = (sizeX * endSize.x);
	rectangleVertex[3].uv[1] = 1.0f - (sizeY * startSize.y);

	//右下
	rectangleVertex[5].uv[0] = sizeX * endSize.x;
	rectangleVertex[5].uv[1] = 1.0f - (sizeY * ((endSize.y - startSize.y) + startSize.y));
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Transform_2D::VertexUV) * 6, rectangleVertex);	//頂点データを再変更	

	
	//  ################################################### 


	//std::cout << windowContext->getSize().x << std::endl;

	//Transform
	setSizeScale(glm::vec2((endSize.x - startSize.x), (endSize.y - startSize.y)));			//サイズ	
	setScale(s);																			//スケール
	setRotate(r);																			//回転
	setTranslate(glm::vec3(pos.x + (getSizeScale().x / 2.0f), pos.y + (getSizeScale().y / 2.0f), 0.0f));	//平行移動



	//uniform
	setUniformMatrix4fv("uTranslate", translate);
	setUniformMatrix4fv("uRotate", rotate);
	setUniformMatrix4fv("uScale", scale);
	setUniformMatrix4fv("uViewProjection", glm::ortho(0.0f, windowContext->getSize().x, windowContext->getSize().y, 0.0f, -1.0f, 1.0f));
	


	//バインド＆描画
	glBindTexture(GL_TEXTURE_2D, textureID.at(texNum).ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	

	//バインドを解除
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (isDefaultShader == true)
	{
		setDisable();
	}


}


//デストラクタ
FrameWork::Sprite::~Sprite()
{

	//std::cout << "デストラクタ" << std::endl;

	//テクスチャーIDを開放
	for (int i = 0; i < textureID.size(); i++)
	{
		glDeleteTextures(1,&textureID.at(i).ID);
	
		stbi_image_free(textureID.at(i).fileData);
		textureID.at(i).fileData = NULL;



	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	
}

