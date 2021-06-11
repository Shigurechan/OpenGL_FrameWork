#include "Animation.hpp"


// ##################################### コンストラクタ ##################################### 
FrameWork::Animation::Animation(std::shared_ptr<Window> w,int num)
{
	windowContext = w;									//ウインドウコンテキスト
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

// ##################################### 一回だけ再生されるアニメーション ##################################### 
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

// ##################################### 一回だけ再生をリセット ##################################### 
void FrameWork::Animation::ResetOnceClip()
{
	flag = false;										//切り替えフレームを設定
	isOnce = false;										//一回再生したかどうか？
	flagOnce = false;									//切り替えフレームを設定一回だけの場合の時
	isFirst = false;									//最初のフレームかどうか？
	nowClip = 0;
}

// ##################################### デストラクタ ##################################### 
FrameWork::Animation::~Animation()
{

}
