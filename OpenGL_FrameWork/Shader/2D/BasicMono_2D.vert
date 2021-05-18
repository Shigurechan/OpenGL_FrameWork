/*#########################################################################
# 単色の二次元描画　頂点シェーダー
###########################################################################*/
#version 330											//バージョン
#extension GL_ARB_explicit_attrib_location: enable		//


// ###################### 頂点属性 ###################### 
layout(location = 0) in vec2 vertexPosition;	//頂点座標

// ###################### 出力 ###################### 
layout(location = 2) out vec4 vFragment;	//頂点カラー

// ###################### Uniform ###################### 
uniform mat4 uScale;			//スケール
uniform mat4 uRotate;			//回転
uniform mat4 uTranslate;		//平行移動
uniform mat4 uViewProjection;	//ビュープロジェクション行列
uniform vec4 uFragment;			//色


void main()
{
	vec4 vertex = vec4(vertexPosition,0.0,1.0);		//頂点座標
	mat4 model = uTranslate * uRotate * uScale;		//モデル行列

	gl_Position =  (uViewProjection * model) * vertex;
	
	vFragment = uFragment;				//カラー
}