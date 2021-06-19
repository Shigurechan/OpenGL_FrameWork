#include "FrameWork.hpp"

/*NOTE
* 
* ウインドウコンテキストの宣言は初期化の後でバージョン設定よりも前に置く
* 
* エントリーポイントの例
int main()
{
	FrameWork::Init();	//初期化
	std::shared_ptr<FrameWork::Window> window = std::make_shared<FrameWork::Window>(48 * 26,48 * 18,"Dungeon");	//ウインドウコンテキスト
	FrameWork::setVersion(4,5);	//バージョン設定
	while (*window)
	{
		window->FrameUpdate();
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Entry

		window->SwapBuffers();
		window->Wait();
	}

	return 0;
}
*/


namespace FrameWork
{
	std::shared_ptr<FrameWork::Window> windowContext;	//ウインドウコンテキスト

	// ##################################### 初期化 ##################################### 
	bool Init()
	{
		setlocale(LC_CTYPE, "");    //ローカルを設定

		if (glfwInit() == GL_FALSE)
		{
			std::cerr << "glfw初期化失敗。" << std::endl;
			return false;
		}

		windowContext = std::make_shared<FrameWork::Window>(48 * 26, 48 * 18, "Dungeon");
		atexit(glfwTerminate);	//プログラム終了時の処理を登録
	
		return true;
	}

	// ##################################### ウインドウコンテキストを取得 ##################################### 
	std::shared_ptr<FrameWork::Window> getWindowContext()
	{
		return windowContext;
	}

	// ##################################### バージョンの指定 ##################################### 
	void setVersion(int a, int b)
	{
		//OpenGL Verison 4.5 Core Profile　を選択する
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
}