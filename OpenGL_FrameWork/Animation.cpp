#include "Animation.hpp"

//コンストラクタ
FrameWork::Animation::Animation(std::shared_ptr<Window> w,int num)
{
	windowContext = w;
	clipNum = num;
	next = 0;											//次のクリップまでのフレーム
	nowClip = 0;										//現在のクリップ
	flag = false;										//切り替えフレームを設定
	speed = 0;											//フレーム速度


}


//アニメーションをするフレーム数を指定
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








//デストラクタ
FrameWork::Animation::~Animation()
{

}
