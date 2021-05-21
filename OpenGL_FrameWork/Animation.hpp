#ifndef ___ANIMATION_HPP_
#define ___ANIMATION_HPP_
#include "Window.hpp"

#include <iostream>
class Window;

namespace FrameWork
{
	class Animation
	{
	public:
		Animation(std::shared_ptr<Window> w, int num);	//�R���X�g���N�^
		~Animation();									//�f�X�g���N�^

		int getClip(int spd);	//�A�j���[�V����������t���[�������w��

	private:

		std::shared_ptr<Window> windowContext;				//�E�C���h�E�R���e�L�X�g
		int clipNum;										//�N���b�v�̐�
		int next;											//���̃N���b�v�܂ł̃t���[��
		int nowClip;										//���݂̃N���b�v
		bool flag;											//�؂�ւ��t���[����ݒ�
		int speed;											//�t���[�����x���w��
	};
};
#endif



