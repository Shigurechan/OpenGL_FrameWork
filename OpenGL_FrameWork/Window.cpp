#include "Window.hpp"
 #include <chrono>
 #include <thread>

double FrameWork::Window::lasttime = 0;


//コンストラクタ
FrameWork::Window::Window(int width, int height, const char* title)
	:window(glfwCreateWindow(width, height, title, NULL, NULL))	
{
	std::fill(std::begin(keyBoard), std::end(keyBoard), 0);


	if (window == NULL)
	{
		std::cerr << "ウインドウ生成失敗" << std::endl;
		exit(1);
	}

	glfwMakeContextCurrent(window);	//コンテキストを作成
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLFW 初期化失敗" << std::endl;
		exit(1);
	}

	atexit(glfwTerminate);	//プログラム終了時の処理を登録
	glfwSwapInterval(1);	//垂直同期


	//イベント処理
	glfwSetWindowUserPointer(window, this);		//このインスタンスのthis
	glfwSetWindowSizeCallback(window, Resize);	//ウインドウサイズを変更する時に呼び出す処理
	Resize(window, width, height);	//リサイズ

}

//サイズ変更
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


//待機フレームを計算
void FrameWork::Window::FrameUpdate()
{

	if (count == FRAME_RATE)
	{
		int t = (int)(1000 - ((glfwGetTime() * 1000.0) - startCount));
		wait += t / FRAME_RATE;
		count = 0;
	}



	if (count == 0)
	{
		startCount = ((int)(glfwGetTime() * 1000.0f));
		//std::cout << "startCount: " << startCount << std::endl;


	}


	count++;

}


//フレームを取得
int FrameWork::Window::getFrame()
{
	return count;

}


//待機
void FrameWork::Window::Wait()
{
	if ((int)(wait * 1000.0f) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(wait * 1000.0f))); // 3 ミリ秒
		//std::cout << wait * 1000.0f << std::endl;
	}

}







//ウインドウサイズを取得
const glm::vec2 FrameWork::Window::getSize() const
{
	return size;
}

//キー入力を取得
const int FrameWork::Window::getKeyInput(int input)
{
	int key = glfwGetKey(window, input);

	//printf("input: %d\n",input);

	if (key == GLFW_PRESS)
	{
		keyBoard[input]++;
		if (keyBoard[input] > 1)
		{
			keyBoard[input] = 2;
		}	
	}
	else if (key == GLFW_RELEASE)
	{
	
		keyBoard[input] = 0;

	}

	return keyBoard[input];
}


//bool 演算子
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//イベントを取り出す


//#define DEBUG 
#ifndef DEBUG

	//エラー処理
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "glGetError(): 0x" << std::hex << err << std::endl;
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
	else {
		return true;
	}
}







//ダブルバッファリング
void FrameWork::Window::SwapBuffers()const
{
	glfwSwapBuffers(window);
}

//デストラクタ
FrameWork::Window::~Window()
{
	glfwDestroyWindow(window);
}
