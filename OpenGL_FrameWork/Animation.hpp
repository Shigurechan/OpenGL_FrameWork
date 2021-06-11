#ifndef ___ANIMATION_HPP_
#define ___ANIMATION_HPP_
#include "Window.hpp"
#include <iostream>



/*############################################################################################
* アニメーションクラス　
*
* 説明
*
##############################################################################################*/




class Window;

namespace FrameWork
{
	class Animation
	{
	public:
		Animation(std::shared_ptr<Window> w, int num);	//コンストラクタ
		~Animation();									//デストラクタ

		int getClip(int spd);						//アニメーションをするフレーム数を指定
		bool getOnceClip(int spd,int &clip);		//一回だけ再生されるアニメーション
		void ResetOnceClip();						//一回だけ再生をリセット


	private:

		std::shared_ptr<Window> windowContext;				//ウインドウコンテキスト
		int clipNum;										//クリップの数
		int next;											//次のクリップまでのフレーム
		int nowClip;										//現在のクリップ
		int speed;											//フレーム速度を指定

		bool isOnce;										//一回再生したかどうか？
		bool flagOnce;										//切り替えフレームを設定一回だけの場合の時
		bool isFirst;											//最初のフレーム
		bool flag;											//切り替えフレームを設定

	};
};
#endif



