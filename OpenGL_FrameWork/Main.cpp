/*
#include <iostream>
#include "FrameWork.hpp"
#include "glm/glm.hpp"

int main()
{

	FrameWork::Init();				//初期化
	std::shared_ptr<FrameWork::Window> window = FrameWork::getWindowContext();//std::make_shared<FrameWork::Window>(48 * 26, 48 * 18, "Dungeon");
	FrameWork::setVersion(4, 5);	//バージョン設定

	std::unique_ptr<FrameWork::Text> text = std::make_unique<FrameWork::Text>(40,"あいうえお");

	while (*window)
	{
		window->FrameUpdate(glm::vec4(0.0f, 0.0f, 0.0f, 255.0f));

		text->Draw(glm::vec2(100,100),glm::vec4(0,255,0,255));



	


		window->SwapBuffers();
		window->Wait();
	}




	return 0;
}
*/