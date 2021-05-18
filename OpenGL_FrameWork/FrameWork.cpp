#include "FrameWork.hpp"




/*NOTE
* 
* ウインドウコンテキストの宣言は初期化の後でバージョン設定よりも前に置く
*/


namespace FrameWork
{
	//初期化
	bool Init()
	{
		if (glfwInit() == GL_FALSE)
		{
			std::cerr << "glfw初期化失敗。" << std::endl;
			return false;
		}

		atexit(glfwTerminate);	//プログラム終了時の処理を登録


		
		return true;
	}

	//バージョン設定
	void setVersion(int a, int b)
	{
		//OpenGL Verison 4.5 Core Profile　を選択する
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	}

}