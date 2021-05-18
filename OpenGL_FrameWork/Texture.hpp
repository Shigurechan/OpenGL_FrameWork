#ifndef ___TEXTURE_HPP_
#define ___TEXTURE_HPP_

#include <iostream>
#include "glm/glm.hpp"
#include "glew/include/GL/glew.h"


namespace FrameWork
{

	//テクスチャデータ構造体
	typedef struct
	{
		glm::ivec2 size;				//画像サイズ
		unsigned char* fileData;		//画像データ
		int channel;					//画像のチャンネル数
		GLuint ID;						//テクスチャID
		GLuint textureUnitNumber;		//テクスチャユニット番号
	}TextureData;

	TextureData LoadTexture(const char* fileName);	//テクスチャーロード
}

#endif