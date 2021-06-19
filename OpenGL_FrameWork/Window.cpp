#include "Window.hpp"

#include <chrono>
#include <thread>

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Window::Window(int width, int height, const char* title) : window(glfwCreateWindow(width, height, title, NULL, NULL))	
{
	//���͊Ǘ�
	std::fill(std::begin(keyBoard), std::end(keyBoard), 0);			//�L�[�{�[�h���͔z���������
	std::fill(std::begin(mouseButton), std::end(mouseButton), 0);	//�}�E�X���͔z���������
	mouseWheel = 0;	//�}�E�X�z�C�[��
	inputKey = 0;	//��������

	//�t���[���Ǘ�
	count = 0;		//���݂̃t���[��
	startCount = 0;	//�ŏ��̎���
	wait = 0;		//�ҋ@����

	//�R���e�L�X�g�̍쐬�Ɏ��s
	if (window == NULL)
	{
		std::cerr << "�E�C���h�E�������s" << std::endl;
		exit(1);	//�ُ�I��
	}

	glfwMakeContextCurrent(window);	//�R���e�L�X�g���쐬
	glfwSwapInterval(1);			//��������

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLFW ���������s" << std::endl;
		exit(1);
	}

	atexit(glfwTerminate);	//�v���O�����I�����̏�����o�^
	glfwSwapInterval(1);	//��������


	//�C�x���g����
	glfwSetWindowUserPointer(window, this);			//���̃C���X�^���X��this
	glfwSetWindowSizeCallback(window, Resize);		//�E�C���h�E�T�C�Y��ύX���鎞�ɌĂяo������
	glfwSetDropCallback(window,DragAndDrop);		//�h���b�N���h���b�v
	glfwSetScrollCallback(window,MouseScroll);		//�}�E�X�̃z�C�[��
	//glfwSetCharCallback(window,KeyInputString);	//�L�[����(��������)�@������

	Resize(window, width, height);	//���T�C�Y
}

// ##################################### ��ʃT�C�Y�ύX ##################################### 
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

// ##################################### �}�E�X�X�N���[�� ##################################### 
void FrameWork::Window::MouseScroll(GLFWwindow* win,double x, double y)
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{

		instance->mouseWheel = y;
	}	
}

// ##################################### �}�E�X�X�N���[�����擾 ##################################### 
double FrameWork::Window::getMouseScroll()
{
	return mouseWheel;
}

// ##################################### �h���b�N���h���b�v�����p�X���擾 ##################################### 
const std::string FrameWork::Window::getDropPath()const
{
	return drop;
}

// ##################################### �h���b�N���h���b�v ##################################### 
void FrameWork::Window::DragAndDrop(GLFWwindow* const win,int num, const char* str[])
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->drop = std::string(str[0]);		
	}
}
// ##################################### �}�E�X���W���擾 ##################################### 
glm::vec2 FrameWork::Window::getMousePos()
{
	double x;
	double y;
	glfwGetCursorPos(window,&x,&y);

	glm::vec2 pos((float)x, (float)y);

	return pos;
}
// ##################################### �}�E�X�{�^������ ##################################### 
int FrameWork::Window::getMouseButton(int mouse )
{
	if (glfwGetMouseButton(window, mouse))
	{
		mouseButton[mouse]++;

		//�l�̃I�[�o�[�t���[��h��
		if (mouseButton[mouse] > 6000)
		{
			mouseButton[mouse] = 6000;
		}
	}
	else
	{
		mouseButton[mouse] = 0;
	}

	return mouseButton[mouse];
}


// ##################################### �ҋ@�t���[�����v�Z ##################################### 
void FrameWork::Window::FrameUpdate(glm::vec4 color)
{
	float c = 1.0f / 255.0f;
	glClearColor(color.x * c, color.y * c, color.z * c, color.w * c);									//�J���[�o�b�t�@�̃N���A�F
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);	//�t���[���o�b�t�@��������

	glEnable(GL_BLEND);	//�A���t�@�u�����h�L��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//�u�����h�^�C�v

	//�t���[�����[�g�𐧌䂷��
	if (count == FRAME_RATE)
	{
		int t = (int)(1000 - ((glfwGetTime() * 1000.0) - startCount));
		wait += t / FRAME_RATE;
		count = 0;
	}

	if (count == 0)
	{
		startCount = ((int)(glfwGetTime() * 1000.0f));
	}

	count++;
}

// ##################################### �t���[�����擾 ##################################### 
int FrameWork::Window::getFrame()
{
	return count;
}

// ##################################### �t���[�����[�g�@�ҋ@ ##################################### 
void FrameWork::Window::Wait()
{
	if ((int)(wait * 1000.0f) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(wait * 1000.0f))); // 3 �~���b
	}
}

// ##################################### �E�C���h�E�T�C�Y���擾 ##################################### 
const glm::vec2 FrameWork::Window::getSize() const
{
	return size;
}

// ##################################### �L�[���� ##################################### 
const int FrameWork::Window::getKeyInput(int input)
{
	int key = glfwGetKey(window, input);

	if (key == GLFW_PRESS)
	{
		keyBoard[input]++;
		if (keyBoard[input] > 6000)
		{
			keyBoard[input] = 6000;
		}	
	}
	else if (key == GLFW_RELEASE)
	{	
		keyBoard[input] = 0;
	}

	return keyBoard[input];
}

// ##################################### bool���Z�q ##################################### 
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//�C�x���g�����o��

#ifndef DEBUG
	//�G���[����
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "glGetError(): 0x" << std::hex << err << std::endl;
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
	else 
	{
		return true;
	}
}

// ##################################### �_�u���o�b�t�@�����O ##################################### 
void FrameWork::Window::SwapBuffers()const
{
	glfwSwapBuffers(window);
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Window::~Window()
{
	glfwDestroyWindow(window);
}
