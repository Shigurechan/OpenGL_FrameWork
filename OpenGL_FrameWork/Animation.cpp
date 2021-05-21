#include "Animation.hpp"

//�R���X�g���N�^
FrameWork::Animation::Animation(std::shared_ptr<Window> w,int num)
{
	windowContext = w;
	clipNum = num;
	next = 0;											//���̃N���b�v�܂ł̃t���[��
	nowClip = 0;										//���݂̃N���b�v
	flag = false;										//�؂�ւ��t���[����ݒ�
	speed = 0;											//�t���[�����x


}


//�A�j���[�V����������t���[�������w��
int FrameWork::Animation::getClip(int spd)
{
	if (flag == false || speed != spd) {
		speed = spd;
		if (windowContext->getProgressFrame() + spd > PROGRESS_FRAME_MAX)
		{
			int a = (windowContext->getProgressFrame() + spd) - PROGRESS_FRAME_MAX;
			int b = spd - a;
			next = b + a;
		}
		else {
			next = windowContext->getProgressFrame() + spd;
		}
		
		flag = true;
	}


	if (windowContext->getProgressFrame() == next)
	{
		nowClip++;
		if (clipNum < nowClip)
		{
			nowClip = 0;
		}
		flag = false;
	}

	return nowClip;


}








//�f�X�g���N�^
FrameWork::Animation::~Animation()
{

}
