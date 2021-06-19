/*#########################################################################
# 単色の二次元テキストレンダリング フラグメントシェーダー
###########################################################################*/
#version 330
#extension GL_ARB_explicit_attrib_location: enable 

// ###################### 入力 ###################### 
layout(location = 2 ) in vec2 texCoord;

// ###################### 出力 ###################### 
out vec4 color;

// ###################### Unifrom ###################### 
uniform sampler2D text;     //文字テクスチャ
uniform vec4 uTextColor;    //色

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoord).r);
    color = uTextColor * sampled;
}  