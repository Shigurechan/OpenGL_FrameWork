#ifndef ___ANIMATION_HPP_
#define ___ANIMATION_HPP_
#include "Window.hpp"
#include <iostream>



/*############################################################################################
* �A�j���[�V�����N���X�@
*
* ����
*
##############################################################################################*/




class Window;

namespace FrameWork
{
	class Animation
	{
	public:
		Animation(std::shared_ptr<Window> w, int num);	//�R���X�g���N�^
		~Animation();									//�f�X�g���N�^

		int getClip(int spd);						//�A�j���[�V����������t���[�������w��
		bool getOnceClip(int spd,int &clip);		//��񂾂��Đ������A�j���[�V����
		void ResetOnceClip();						//��񂾂��Đ������Z�b�g


	private:

		std::shared_ptr<Window> windowContext;				//�E�C���h�E�R���e�L�X�g
		int clipNum;										//�N���b�v�̐�
		int next;											//���̃N���b�v�܂ł̃t���[��
		int nowClip;										//���݂̃N���b�v
		int speed;											//�t���[�����x���w��

		bool isOnce;										//���Đ��������ǂ����H
		bool flagOnce;										//�؂�ւ��t���[����ݒ��񂾂��̏ꍇ�̎�
		bool isFirst;											//�ŏ��̃t���[��
		bool flag;											//�؂�ւ��t���[����ݒ�

	};
};
#endif



