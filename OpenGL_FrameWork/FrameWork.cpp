#include "FrameWork.hpp"




/*NOTE
* 
* �E�C���h�E�R���e�L�X�g�̐錾�͏������̌�Ńo�[�W�����ݒ�����O�ɒu��
*/


namespace FrameWork
{
	//������
	bool Init()
	{
		if (glfwInit() == GL_FALSE)
		{
			std::cerr << "glfw���������s�B" << std::endl;
			return false;
		}

		atexit(glfwTerminate);	//�v���O�����I�����̏�����o�^


		
		return true;
	}

	//�o�[�W�����ݒ�
	void setVersion(int a, int b)
	{
		//OpenGL Verison 4.5 Core Profile�@��I������
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	}

}