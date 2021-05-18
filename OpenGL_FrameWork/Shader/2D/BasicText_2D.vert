/*#########################################################################
# �P�F�̓񎟌��e�L�X�g�����_�����O ���_�V�F�[�_�[
###########################################################################*/
#version 330
#extension GL_ARB_explicit_attrib_location: enable 

// ###################### ���_���� ###################### 
layout(location = 0) in vec4 vertexPosition;	//���_���W


// ######################�@�o�� ###################### 
layout(location = 2) out vec2 texCoord;	//�e�L�X�g

// ###################### Uniform ###################### 
uniform mat4 uViewProjection;	//�r���[�v���W�F�N�V�����s��

void main()
{

	vec4 vertex = vec4(vertexPosition.x,vertexPosition.y,0.0,1.0);		//���_���W
	gl_Position =  (uViewProjection * vertex);
	
	


	texCoord = vertexPosition.zw;
}