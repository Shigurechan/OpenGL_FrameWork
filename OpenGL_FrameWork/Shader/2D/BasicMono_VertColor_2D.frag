/*#########################################################################
# 単色の二次元頂点カラー描画　フラグメントシェーダー
###########################################################################*/
#extension GL_ARB_explicit_attrib_location: enable 

// ###################### 入力 ###################### 
layout(location = 2) in vec4 vfragment;	


//出力
out vec4 fragment;

void main()
{
	fragment = vfragment;
}