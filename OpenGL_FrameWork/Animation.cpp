#include "Animation.hpp"
#include "FrameWork.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
FrameWork::Animation::Animation(int num)
{
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
			next = FrameWork::getWindowContext()->getFrame() + spd;
			isFirst = true;
		}
		else 
		{
			next = getWindowContext()->getFrame() + spd - 1;
		}

		if (next > FRAME_RATE)
		{
			next = next - getWindowContext()->getFrame();
		}

		flag = true;
	}

	if (next == getWindowContext()->getFrame())
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
			next = getWindowContext()->getFrame() + spd;
			isFirst = true;
		}
		else 
		{
			next = getWindowContext()->getFrame() + spd - 1;
		}

		if (next > FRAME_RATE)
		{
			next = next - getWindowContext()->getFrame();
		}

		flagOnce = true;
	}

	if (next == getWindowContext()->getFrame())
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
	nowClip = 0;										//���݂̃N���b�v
}

// ##################################### �f�X�g���N�^ ##################################### 
FrameWork::Animation::~Animation()
{

}
