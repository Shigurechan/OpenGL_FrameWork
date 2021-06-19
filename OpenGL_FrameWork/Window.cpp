#include "Window.hpp"

#include <chrono>
#include <thread>

// ##################################### コンストラクタ ##################################### 
FrameWork::Window::Window(int width, int height, const char* title) : window(glfwCreateWindow(width, height, title, NULL, NULL))	
{
	//入力管理
	std::fill(std::begin(keyBoard), std::end(keyBoard), 0);			//キーボード入力配列を初期化
	std::fill(std::begin(mouseButton), std::end(mouseButton), 0);	//マウス入力配列を初期化
	mouseWheel = 0;	//マウスホイール
	inputKey = 0;	//文字入力

	//フレーム管理
	count = 0;		//現在のフレーム
	startCount = 0;	//最初の時間
	wait = 0;		//待機時間

	//コンテキストの作成に失敗
	if (window == NULL)
	{
		std::cerr << "ウインドウ生成失敗" << std::endl;
		exit(1);	//異常終了
	}

	glfwMakeContextCurrent(window);	//コンテキストを作成
	glfwSwapInterval(1);			//垂直同期

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLFW 初期化失敗" << std::endl;
		exit(1);
	}

	atexit(glfwTerminate);	//プログラム終了時の処理を登録
	glfwSwapInterval(1);	//垂直同期


	//イベント処理
	glfwSetWindowUserPointer(window, this);			//このインスタンスのthis
	glfwSetWindowSizeCallback(window, Resize);		//ウインドウサイズを変更する時に呼び出す処理
	glfwSetDropCallback(window,DragAndDrop);		//ドラック＆ドロップ
	glfwSetScrollCallback(window,MouseScroll);		//マウスのホイール
	//glfwSetCharCallback(window,KeyInputString);	//キー入力(文字入力)　未実装

	Resize(window, width, height);	//リサイズ
}

// ##################################### 画面サイズ変更 ##################################### 
void FrameWork::Window::Resize(GLFWwindow* const win, int width, int height)
{
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(win, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->size.x = (GLfloat)width;
		instance->size.y = (GLfloat)height;		
	}
}

// ##################################### マウススクロール ##################################### 
void FrameWork::Window::MouseScroll(GLFWwindow* win,double x, double y)
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{

		instance->mouseWheel = y;
	}	
}

// ##################################### マウススクロールを取得 ##################################### 
double FrameWork::Window::getMouseScroll()
{
	return mouseWheel;
}

// ##################################### ドラック＆ドロップしたパスを取得 ##################################### 
const std::string FrameWork::Window::getDropPath()const
{
	return drop;
}

// ##################################### ドラック＆ドロップ ##################################### 
void FrameWork::Window::DragAndDrop(GLFWwindow* const win,int num, const char* str[])
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->drop = std::string(str[0]);		
	}
}
// ##################################### マウス座標を取得 ##################################### 
glm::vec2 FrameWork::Window::getMousePos()
{
	double x;
	double y;
	glfwGetCursorPos(window,&x,&y);

	glm::vec2 pos((float)x, (float)y);

	return pos;
}
// ##################################### マウスボタン入力 ##################################### 
int FrameWork::Window::getMouseButton(int mouse )
{
	if (glfwGetMouseButton(window, mouse))
	{
		mouseButton[mouse]++;

		//値のオーバーフローを防ぐ
		if (mouseButton[mouse] > 6000)
		{
			mouseButton[mouse] = 6000;
		}
	}
	else
	{
		mouseButton[mouse] = 0;
	}

	return mouseButton[mouse];
}


// ##################################### 待機フレームを計算 ##################################### 
void FrameWork::Window::FrameUpdate(glm::vec4 color)
{
	float c = 1.0f / 255.0f;
	glClearColor(color.x * c, color.y * c, color.z * c, color.w * c);									//カラーバッファのクリア色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);	//フレームバッファを初期化

	glEnable(GL_BLEND);	//アルファブレンド有効
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//ブレンドタイプ

	//フレームレートを制御する
	if (count == FRAME_RATE)
	{
		int t = (int)(1000 - ((glfwGetTime() * 1000.0) - startCount));
		wait += t / FRAME_RATE;
		count = 0;
	}

	if (count == 0)
	{
		startCount = ((int)(glfwGetTime() * 1000.0f));
	}

	count++;
}

// ##################################### フレームを取得 ##################################### 
int FrameWork::Window::getFrame()
{
	return count;
}

// ##################################### フレームレート　待機 ##################################### 
void FrameWork::Window::Wait()
{
	if ((int)(wait * 1000.0f) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(wait * 1000.0f))); // 3 ミリ秒
	}
}

// ##################################### ウインドウサイズを取得 ##################################### 
const glm::vec2 FrameWork::Window::getSize() const
{
	return size;
}

// ##################################### キー入力 ##################################### 
const int FrameWork::Window::getKeyInput(int input)
{
	int key = glfwGetKey(window, input);

	if (key == GLFW_PRESS)
	{
		keyBoard[input]++;
		if (keyBoard[input] > 6000)
		{
			keyBoard[input] = 6000;
		}	
	}
	else if (key == GLFW_RELEASE)
	{	
		keyBoard[input] = 0;
	}

	return keyBoard[input];
}

// ##################################### bool演算子 ##################################### 
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//イベントを取り出す

#ifndef DEBUG
	//エラー処理
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "glGetError(): 0x" << std::hex << err << std::endl;
	}
#endif
	
	//ESCキーで終了
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 1)
	{
		exit(1);
	}

	//ウインドウを閉じる必要があれば false
	if (glfwWindowShouldClose(window) != 0)
	{
		return false;
	}
	else 
	{
		return true;
	}
}

// ##################################### ダブルバッファリング ##################################### 
void FrameWork::Window::SwapBuffers()const
{
	glfwSwapBuffers(window);
}

// ##################################### デストラクタ ##################################### 
FrameWork::Window::~Window()
{
	glfwDestroyWindow(window);
}
