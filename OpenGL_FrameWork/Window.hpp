#ifndef ___WINDOW_HPP
#define ___WINDOW_HPP

#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include "glm/glm.hpp"

#define FRAME_RATE 60

namespace FrameWork
{
	class Window
	{
	public:

		Window(int width = 640, int height = 480, const char* title = "Hello!");	//�R���X�g���N�^
		~Window();																	//�f�X�g���N�^

		explicit operator bool();	//bool ���Z�q
		void SwapBuffers()const;	//�_�u���o�b�t�@�����O
		const int getKeyInput(int input);	//�L�[����

		//�t���[���Ǘ�
		void FrameUpdate();		//�ҋ@�t���[�����v�Z
		void Wait();			//�ҋ@
		int getFrame();	//�t���[�����擾



		//�C�x���g����
		static void Resize(GLFWwindow* const win, int width, int height);						//�T�C�Y�ύX

		const glm::vec2 getSize() const;		//�T�C�Y���擾

	private:

		GLFWwindow* const window;	//�E�C���h�E�R���e�L�X�g
		glm::vec2 size;				//�E�C���h�T�C�Y
		char keyBoard[500];			//�L�[����




		//�t���[���Ǘ�
		static double lasttime;
		double nowtime = 0;
		double deltatime = 0;
		double limittime = 1.0 / 60;

		int count = 0;
		int startCount = 0;
		double wait  = 0;
	};
}
#endif

