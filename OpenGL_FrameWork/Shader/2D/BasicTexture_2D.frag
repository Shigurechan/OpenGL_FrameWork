/*#########################################################################
# �P�F�̓񎟌��`��@�t���O�����g�V�F�[�_�[
###########################################################################*/
#version 330

#extension GL_ARB_explicit_attrib_location: enable 

// ###################### ���� ###################### 
layout(location = 2) in vec2 vUV;	//UV���W	

// ###################### Unifrom ###################### 
uniform sampler2D uImage;			//�C���[�W

//�o��
out vec4 fragment;

void main()
{

	fragment = texture(uImage,vUV);
}