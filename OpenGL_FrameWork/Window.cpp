#include "Window.hpp"
 #include <chrono>
 #include <thread>


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
	
	if (count == 60)
	{
		int t = ((int)(glfwGetTime() * 1000.0f)) - startCount;



		//std::cout << "glfwGetTime(): " << (int)(glfwGetTime() * 1000.0f) << std::endl;
		//std::cout << "startCount: " << startCount << std::endl;
		//std::cout <<"t: "<< t << std::endl;

		wait = t / 60;
		//std::cout << wait << std::endl;
		//startCount = 0;
		count = 0;
		//glfwSetTime(0);
	}



	if (count == 0)
	{
		startCount = ((int)(glfwGetTime() * 1000.0f));
		//std::cout << "startCount: " << startCount << std::endl;


	}


	count++;

}



//待機
void FrameWork::Window::Wait()
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(wait)); // 3 ミリ秒

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

	if ( key == GLFW_PRESS)
	{
		keyBoard[key] += 1;
		if (keyBoard[key] > 1)
		{
			keyBoard[key] = 2;
		} 
	}
	else if (key == GLFW_RELEASE)
	{
		keyBoard[key] = 0;
	}

	return keyBoard[key];
}


//bool 演算子
FrameWork::Window::operator bool()
{
	glfwPollEvents();	//イベントを取り出す


#define DEBUG 1
#ifndef DEBUG
	//エラー処理
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{	
		std::cout <<"glGetError(): 0x"<< std::hex << err << std::endl;
	}
#endif;


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
