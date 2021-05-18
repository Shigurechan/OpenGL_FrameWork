#ifndef ___Sprite_2D_HPP
#define ___Sprite_2D_HPP


#include <iostream>
#include <glew/include/GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Transform_2D.hpp"
#include "Shader.hpp"


namespace FrameWork
{
	class Window;


	class Sprite : protected FrameWork::Transform_2D, public Shader
	{
	public:

		Sprite(std::shared_ptr<Window> w, const char* vert = NULL, const char* frag = NULL);		//コンストラクタ
		~Sprite();										//デストラクタ

		// ###################### メンバ関数 ###################### 	
		void DrawGraph(glm::vec2 pos, unsigned char texNum,float r, glm::vec2 s,glm::vec2 startSize, glm::vec2 endSize);	//描画

		void setTexture(TextureData tex);			//テクスチャ設定

	private:

		//頂点情報
		Transform_2D::VertexUV rectangleVertex[6] =
		{
			//頂点、頂点色
			{-0.5f,0.5f,    0.0f,1.0f},
			{-0.5f,-0.5f,	0.0f,0.0f},
			{0.5f,0.5f,		1.0f,1.0f},

			{0.5f,0.5f,		 1.0f,1.0f},
			{-0.5f,-0.5f,    0.0f,0.0f},
			{0.5f,-0.5f,     1.0f,0.0f},
		};


		void setDrawTextureID(unsigned char id);	//描画するテクスチャ番号を指定

		std::vector<TextureData> textureID;	//テクスチャーID
		unsigned char textureUnitCount;		//テクスチャー番号をカウント

		std::shared_ptr<Window> windowContext;	//Windowコンテキスト

		//bool isDefaultShader; //デフォルトシェーダーかどうか？
	};
}
#endif
