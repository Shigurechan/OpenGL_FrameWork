/*#########################################################################
# 単色の二次元テキストレンダリング 頂点シェーダー
###########################################################################*/
#version 330
#extension GL_ARB_explicit_attrib_location: enable 

// ###################### 頂点属性 ###################### 
layout(location = 0) in vec4 vertexPosition;	//頂点座標


// ######################　出力 ###################### 
layout(location = 2) out vec2 texCoord;	//テキスト

// ###################### Uniform ###################### 
uniform mat4 uViewProjection;	//ビュープロジェクション行列

void main()
{

	vec4 vertex = vec4(vertexPosition.x,vertexPosition.y,0.0,1.0);		//頂点座標
	gl_Position =  (uViewProjection * vertex);
	
	


	texCoord = vertexPosition.zw;
}