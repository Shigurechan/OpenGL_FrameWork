#ifndef ___WINDOW_HPP_
#define ___WINDOW_HPP_

#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include "glm/glm.hpp"

#define FRAME_RATE 60	//�t���[�����[�g
/*#########################################################################
# Window�R���e�L�X�g�N���X

����
	�E�C���h�E�R���e�L�X�g�ƃt���[�����[�g�ƃL�[���͂𐧌�
###########################################################################*/
namespace FrameWork
{
	class Window
	{

	public:

		Window(int width = 640, int height = 480, const char* title = "Hello!");	//�R���X�g���N�^
		~Window();																	//�f�X�g���N�^

		explicit operator bool();			//bool ���Z�q
		void SwapBuffers()const;			//�_�u���o�b�t�@�����O
		const int getKeyInput(int input);	//�L�[����

		//�t���[���Ǘ�
		void FrameUpdate(glm::vec4 color);	//�ҋ@�t���[�����v�Z
		void Wait();		//�ҋ@
		int getFrame();		//�t���[�����擾 60�܂�

		const glm::vec2 getSize() const;		//�T�C�Y���擾
		const std::string getDropPath()const;	//�h���b�N���h���b�v�����p�X���擾
		glm::vec2 getMousePos();				//�}�E�X���W���擾
		int getMouseButton(int mouse);			//�}�E�X�{�^���������ꂽ���ǂ����H
		double getMouseScroll();				//�}�E�X�X�N���[�����擾
		unsigned int InputKeyBoard();			//�L�[����(��������)

		//�C�x���g����
		static void Resize(GLFWwindow* const win, int width, int height);			//�T�C�Y�ύX
		static void DragAndDrop(GLFWwindow* const win, int num, const char* str[]);	//�h���b�N���h���b�v
		static void MouseScroll(GLFWwindow* win,double x, double y);				//�}�E�X�X�N���[��
		static void KeyInputString(GLFWwindow* win,unsigned int n);					//�L�[����(��������)

	private:

		GLFWwindow* const window;	//�E�C���h�E�R���e�L�X�g
		glm::vec2 size;				//�E�C���h�T�C�Y
		int keyBoard[500];			//�L�[����
		int mouseButton[2];			//�}�E�X����
		double mouseWheel = 0;		//�}�E�X�z�C�[��
		unsigned int inputKey = 0;	//��������

		//�t���[���Ǘ�
		int count;		//���݂̃t���[��
		int startCount;	//�ŏ��̎���
		double wait;	//�ҋ@����

		std::string drop;	//�h���b�N���h���b�v�����p�X
	};
}
#endif
