#ifndef ___Transform_2D_HPP_
#define ___Transform_2D_HPP_

#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_Transform.hpp>
#include <glm/gtx/Transform.hpp>


#include <glew/include/GL/glew.h>


/*#########################################################################
# トランスフォームクラス: Actorクラスを継承

説明
	全ての2D描画物はこれを継承する
###########################################################################*/

namespace FrameWork
{
	class Window;

	class Transform_2D
	{
	public:

		Transform_2D();		//コンストラクタ
		~Transform_2D();	//デストラクタ




	protected:

		// ###################### Transform_2D　設定 ###################### 
		void setScale(glm::vec2 s);				//スケール
		void setRotate(float a);				//回転
		void setTranslate(glm::vec3 t);			//平行移動
		glm::vec2 getSizeScale();				//サイズを取得
		void setSizeScale(glm::vec2 s);			//サイズを設定

		//頂点座標とUV
		struct VertexUV
		{
			GLfloat position[2];
			GLfloat uv[2];
		};

		//頂点座標
		struct Vertex
		{
			GLfloat position[2];
		};

		//頂点座標と頂点カラー
		struct VertexColor
		{
			GLfloat position[2];
			GLfloat color[4];
		};





		GLuint vao;							//VertexArrayObject
		GLuint vbo;							//VertexBufferObject	

		bool isDefaultShader;	//既定のシェーダーファイルが選ばれたかどうか？

		//描画行列
		glm::mat4 scale;		//拡大縮小
		glm::mat4 rotate;		//回転
		glm::mat4 translate;	//平行移動

	private:
		glm::vec2 size;			//画像サイズ

	};
}

#endif
