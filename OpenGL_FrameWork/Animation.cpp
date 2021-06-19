#include "Animation.hpp"
#include "FrameWork.hpp"

// ##################################### コンストラクタ ##################################### 
FrameWork::Animation::Animation(int num)
{
	clipNum = num;
	next = 0;											//次のクリップまでのフレーム
	nowClip = 0;										//現在のクリップ
	speed = 0;											//フレーム速度

	flag = false;										//切り替えフレームを設定
	isOnce = false;										//一回再生したかどうか？
	flagOnce = false;									//切り替えフレームを設定一回だけの場合の時
	isFirst = false;									//最初のフレームかどうか？
}

// ##################################### アニメーションをするフレーム数を指定 ##################################### 
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

// ##################################### 一回だけ再生されるアニメーション ##################################### 
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

// ##################################### 一回だけ再生をリセット ##################################### 
void FrameWork::Animation::ResetOnceClip()
{
	flag = false;										//切り替えフレームを設定
	isOnce = false;										//一回再生したかどうか？
	flagOnce = false;									//切り替えフレームを設定一回だけの場合の時
	isFirst = false;									//最初のフレームかどうか？
	nowClip = 0;										//現在のクリップ
}

// ##################################### デストラクタ ##################################### 
FrameWork::Animation::~Animation()
{

}
