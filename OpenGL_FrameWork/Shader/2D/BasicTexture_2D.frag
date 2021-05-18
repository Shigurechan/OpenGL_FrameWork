/*#########################################################################
# 単色の二次元描画　フラグメントシェーダー
###########################################################################*/
#version 330

#extension GL_ARB_explicit_attrib_location: enable 

// ###################### 入力 ###################### 
layout(location = 2) in vec2 vUV;	//UV座標	

// ###################### Unifrom ###################### 
uniform sampler2D uImage;			//イメージ

//出力
out vec4 fragment;

void main()
{

	fragment = texture(uImage,vUV);
}