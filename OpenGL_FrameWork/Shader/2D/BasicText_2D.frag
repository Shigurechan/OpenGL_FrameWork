/*#########################################################################
# �P�F�̓񎟌��e�L�X�g�����_�����O �t���O�����g�V�F�[�_�[
###########################################################################*/
#version 330
#extension GL_ARB_explicit_attrib_location: enable 

// ###################### ���� ###################### 
layout(location = 2 ) in vec2 texCoord;

// ###################### �o�� ###################### 
out vec4 color;

// ###################### Unifrom ###################### 
uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoord).r);
    color = vec4(textColor,1.0) * sampled;
}  