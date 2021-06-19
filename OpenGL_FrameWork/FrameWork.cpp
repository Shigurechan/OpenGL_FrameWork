#include "FrameWork.hpp"

/*NOTE
* 
* �E�C���h�E�R���e�L�X�g�̐錾�͏������̌�Ńo�[�W�����ݒ�����O�ɒu��
* 
* �G���g���[�|�C���g�̗�
int main()
{
	FrameWork::Init();	//������
	std::shared_ptr<FrameWork::Window> window = std::make_shared<FrameWork::Window>(48 * 26,48 * 18,"Dungeon");	//�E�C���h�E�R���e�L�X�g
	FrameWork::setVersion(4,5);	//�o�[�W�����ݒ�
	while (*window)
	{
		window->FrameUpdate();
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Entry

		window->SwapBuffers();
		window->Wait();
	}

	return 0;
}
*/


namespace FrameWork
{
	std::shared_ptr<FrameWork::Window> windowContext;	//�E�C���h�E�R���e�L�X�g

	// ##################################### ������ ##################################### 
	bool Init()
	{
		setlocale(LC_CTYPE, "");    //���[�J����ݒ�

		if (glfwInit() == GL_FALSE)
		{
			std::cerr << "glfw���������s�B" << std::endl;
			return false;
		}

		windowContext = std::make_shared<FrameWork::Window>(48 * 26, 48 * 18, "Dungeon");
		atexit(glfwTerminate);	//�v���O�����I�����̏�����o�^
	
		return true;
	}

	// ##################################### �E�C���h�E�R���e�L�X�g���擾 ##################################### 
	std::shared_ptr<FrameWork::Window> getWindowContext()
	{
		return windowContext;
	}

	// ##################################### �o�[�W�����̎w�� ##################################### 
	void setVersion(int a, int b)
	{
		//OpenGL Verison 4.5 Core Profile�@��I������
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
}