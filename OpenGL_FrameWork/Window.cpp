#include "Window.hpp"
 #include <chrono>
 #include <thread>

double FrameWork::Window::lasttime = 0;


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
	glfwSwapInterval(1);
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

	if (count == FRAME_RATE)
	{
		int t = (int)(1000 - ((glfwGetTime() * 1000.0) - startCount));
		wait += t / FRAME_RATE;
		count = 0;
	}



	if (count == 0)
	{
		startCount = ((int)(glfwGetTime() * 1000.0f));
		//std::cout << "startCount: " << startCount << std::endl;


	}


	count++;

}


//�t���[�����擾
int FrameWork::Window::getFrame()
{
	return count;

}


//�ҋ@
void FrameWork::Window::Wait()
{
	if ((int)(wait * 1000.0f) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(wait * 1000.0f))); // 3 �~���b
		//std::cout << wait * 1000.0f << std::endl;
	}

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

	//printf("input: %d\n",input);

	if (key == GLFW_PRESS)
	{
		keyBoard[input]++;
		if (keyBoard[input] > 1)
		{
			keyBoard[input] = 2;
		}	
	}
	else if (key == GLFW_RELEASE)
	{
	
		keyBoard[input] = 0;

	}

	return keyBoard[input];
}


//bool ���Z�q
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//�C�x���g�����o��


//#define DEBUG 
#ifndef DEBUG

	//�G���[����
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "glGetError(): 0x" << std::hex << err << std::endl;
	}


#endif

	
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
