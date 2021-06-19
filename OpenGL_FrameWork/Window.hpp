#ifndef ___WINDOW_HPP_
#define ___WINDOW_HPP_

#include <iostream>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include "glm/glm.hpp"

#define FRAME_RATE 60	//フレームレート
/*#########################################################################
# Windowコンテキストクラス

説明
	ウインドウコンテキストとフレームレートとキー入力を制御
###########################################################################*/
namespace FrameWork
{
	class Window
	{

	public:

		Window(int width = 640, int height = 480, const char* title = "Hello!");	//コンストラクタ
		~Window();																	//デストラクタ

		explicit operator bool();			//bool 演算子
		void SwapBuffers()const;			//ダブルバッファリング
		const int getKeyInput(int input);	//キー入力

		//フレーム管理
		void FrameUpdate(glm::vec4 color);	//待機フレームを計算
		void Wait();		//待機
		int getFrame();		//フレームを取得 60まで

		const glm::vec2 getSize() const;		//サイズを取得
		const std::string getDropPath()const;	//ドラック＆ドロップしたパスを取得
		glm::vec2 getMousePos();				//マウス座標を取得
		int getMouseButton(int mouse);			//マウスボタンが押されたかどうか？
		double getMouseScroll();				//マウススクロールを取得
		unsigned int InputKeyBoard();			//キー入力(文字入力)

		//イベント処理
		static void Resize(GLFWwindow* const win, int width, int height);			//サイズ変更
		static void DragAndDrop(GLFWwindow* const win, int num, const char* str[]);	//ドラック＆ドロップ
		static void MouseScroll(GLFWwindow* win,double x, double y);				//マウススクロール
		static void KeyInputString(GLFWwindow* win,unsigned int n);					//キー入力(文字入力)

	private:

		GLFWwindow* const window;	//ウインドウコンテキスト
		glm::vec2 size;				//ウインドサイズ
		int keyBoard[500];			//キー入力
		int mouseButton[2];			//マウス入力
		double mouseWheel = 0;		//マウスホイール
		unsigned int inputKey = 0;	//文字入力

		//フレーム管理
		int count;		//現在のフレーム
		int startCount;	//最初の時間
		double wait;	//待機時間

		std::string drop;	//ドラック＆ドロップしたパス
	};
}
#endif
