/*#########################################################################
# �P�F��3D�`��
###########################################################################*/
#extension GL_ARB_explicit_attrib_location: enable 


layout(location = 2) in vec4 vfragment;	


//�o��
out vec4 fragment;

void main()
{
	fragment = vfragment;
}