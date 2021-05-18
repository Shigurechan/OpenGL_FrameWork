#include "Window.hpp"
 #include <chrono>
 #include <thread>


//�R���X�g���N�^
FrameWork::Window::Window(int width, int height, const char* title)
	:window(glfwCreateWindow(width, height, title, NULL, NULL))	
{
	std::fill(std::begin(keyBoard), std::end(keyBoard), 0);


	if (window == NULL)
	{
		std::cerr << "�E�C���h�E�������s" << std::endl;
		exit(1);
	}

	glfwMakeContextCurrent(window);	//�R���e�L�X�g���쐬

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLFW ���������s" << std::endl;
		exit(1);
	}

	atexit(glfwTerminate);	//�v���O�����I�����̏�����o�^
	glfwSwapInterval(1);	//��������


	//�C�x���g����
	glfwSetWindowUserPointer(window, this);		//���̃C���X�^���X��this
	glfwSetWindowSizeCallback(window, Resize);	//�E�C���h�E�T�C�Y��ύX���鎞�ɌĂяo������
	Resize(window, width, height);	//���T�C�Y

}

//�T�C�Y�ύX
void FrameWork::Window::Resize(GLFWwindow* const win, int width, int height)
{
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(win, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->size.x = (GLfloat)width;
		instance->size.y = (GLfloat)height;		
	}
}


//�ҋ@�t���[�����v�Z
void FrameWork::Window::FrameUpdate()
{
	
	if (count == 60)
	{
		int t = ((int)(glfwGetTime() * 1000.0f)) - startCount;



		//std::cout << "glfwGetTime(): " << (int)(glfwGetTime() * 1000.0f) << std::endl;
		//std::cout << "startCount: " << startCount << std::endl;
		//std::cout <<"t: "<< t << std::endl;

		wait = t / 60;
		//std::cout << wait << std::endl;
		//startCount = 0;
		count = 0;
		//glfwSetTime(0);
	}



	if (count == 0)
	{
		startCount = ((int)(glfwGetTime() * 1000.0f));
		//std::cout << "startCount: " << startCount << std::endl;


	}


	count++;

}



//�ҋ@
void FrameWork::Window::Wait()
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(wait)); // 3 �~���b

}







//�E�C���h�E�T�C�Y���擾
const glm::vec2 FrameWork::Window::getSize() const
{
	return size;
}

//�L�[���͂��擾
const int FrameWork::Window::getKeyInput(int input)
{
	int key = glfwGetKey(window, input);

	if ( key == GLFW_PRESS)
	{
		keyBoard[key] += 1;
		if (keyBoard[key] > 1)
		{
			keyBoard[key] = 2;
		} 
	}
	else if (key == GLFW_RELEASE)
	{
		keyBoard[key] = 0;
	}

	return keyBoard[key];
}


//bool ���Z�q
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//�C�x���g�����o��


#define DEBUG 1
#ifndef DEBUG
	//�G���[����
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{	
		std::cout <<"glGetError(): 0x"<< std::hex << err << std::endl;
	}
#endif;


	//ESC�L�[�ŏI��
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 1)
	{
		exit(1);
	}




	//�E�C���h�E�����K�v������� false
	if (glfwWindowShouldClose(window) != 0)
	{
		return false;
	}
	else {
		return true;
	}
}







//�_�u���o�b�t�@�����O
void FrameWork::Window::SwapBuffers()const
{
	glfwSwapBuffers(window);
}

//�f�X�g���N�^
FrameWork::Window::~Window()
{
	glfwDestroyWindow(window);
}
