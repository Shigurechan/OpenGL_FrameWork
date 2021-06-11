#include "Animation.hpp"


// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Animation::Animation(std::shared_ptr<Window> w,int num)
{
	windowContext = w;									//�E�C���h�E�R���e�L�X�g
	clipNum = num;
	next = 0;											//���̃N���b�v�܂ł̃t���[��
	nowClip = 0;										//���݂̃N���b�v
	speed = 0;											//�t���[�����x

	flag = false;										//�؂�ւ��t���[����ݒ�
	isOnce = false;										//���Đ��������ǂ����H
	flagOnce = false;									//�؂�ւ��t���[����ݒ��񂾂��̏ꍇ�̎�
	isFirst = false;									//�ŏ��̃t���[�����ǂ����H
}

// ##################################### �A�j���[�V����������t���[�������w�� ##################################### 
int FrameWork::Animation::getClip(int spd)
{

	if (flag == false)
	{
		if (isFirst == false)
		{
			next = windowContext->getFrame() + spd;
			isFirst = true;
		}
		else {
			next = windowContext->getFrame() + spd - 1;

		}

		if (next > FRAME_RATE)
		{
			next = next - windowContext->getFrame();
		}


		flag = true;
	}

	//std::cout << "next: " << next << std::endl;

	if (next == windowContext->getFrame())
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

// ##################################### ��񂾂��Đ������A�j���[�V���� ##################################### 
bool FrameWork::Animation::getOnceClip(int spd, int& clip)
{
	if (flagOnce == false)
	{
		if (isFirst == false)
		{
			next = windowContext->getFrame() + spd;
			isFirst = true;
		}
		else 
		{
			next = windowContext->getFrame() + spd - 1;
		}

		if (next > FRAME_RATE)
		{
			next = next - windowContext->getFrame();
		}
		flagOnce = true;
	}

	if (next == windowContext->getFrame())
	{
		nowClip++;
		if (clipNum < nowClip)
		{
			nowClip = clipNum;
			isOnce = true;
		}

		flagOnce = false;
	}

	clip = nowClip;
	return isOnce;
}

// ##################################### ��񂾂��Đ������Z�b�g ##################################### 
void FrameWork::Animation::ResetOnceClip()
{
	flag = false;										//�؂�ւ��t���[����ݒ�
	isOnce = false;										//���Đ��������ǂ����H
	flagOnce = false;									//�؂�ւ��t���[����ݒ��񂾂��̏ꍇ�̎�
	isFirst = false;									//�ŏ��̃t���[�����ǂ����H
	nowClip = 0;
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Animation::~Animation()
{

}
