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
		Animation(std::shared_ptr<Window> w, int num);	//コンストラクタ
		~Animation();									//デストラクタ

		int getClip(int spd);	//アニメーションをするフレーム数を指定

	private:

		std::shared_ptr<Window> windowContext;				//ウインドウコンテキスト
		int clipNum;										//クリップの数
		int next;											//次のクリップまでのフレーム
		int nowClip;										//現在のクリップ
		bool flag;											//切り替えフレームを設定
		int speed;											//フレーム速度を指定
	};
};
#endif



