#ifndef ___WINDOW_HPP
#define ___WINDOW_HPP

#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include "glm/glm.hpp"

#define FRAME_RATE 60

namespace FrameWork
{
	class Window
	{
	public:

		Window(int width = 640, int height = 480, const char* title = "Hello!");	//コンストラクタ
		~Window();																	//デストラクタ

		explicit operator bool();	//bool 演算子
		void SwapBuffers()const;	//ダブルバッファリング
		const int getKeyInput(int input);	//キー入力

		//フレーム管理
		void FrameUpdate();	//待機フレームを計算
		void Wait();		//待機
		int getFrame();		//フレームを取得

		const glm::vec2 getSize() const;		//サイズを取得
		const std::string getDropPath()const;	//ドラック＆ドロップしたパスを取得
		glm::vec2 getMousePos();				//マウス座標を取得
		bool getMouseButton(int mouse);			//マウスボタンが押されたかどうか？



		//イベント処理
		static void Resize(GLFWwindow* const win, int width, int height);					//サイズ変更
		static void DragAndDrop(GLFWwindow* const win,int num,const char* str[]);			//ドラック＆ドロップ

	private:

		GLFWwindow* const window;	//ウインドウコンテキスト
		glm::vec2 size;				//ウインドサイズ
		char keyBoard[500];			//キー入力




		//フレーム管理
		static double lasttime;
		double nowtime = 0;
		double deltatime = 0;
		double limittime = 1.0 / 60;

		int count = 0;
		int startCount = 0;
		double wait  = 0;


		std::string drop;	//ドラック＆ドロップしたパス
	};
}
#endif
