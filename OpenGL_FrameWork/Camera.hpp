#ifndef ___CAMERA_HPP_
#define ___CAMERA_HPP_

#include <iostream>
#include "glm/glm.hpp"


/*#########################################################################
# Cameraクラス

説明
	ゲームオブジェクトのDraw();関数の引数にカメラを設定
###########################################################################*/

namespace FrameWork
{
	class Window;

	class Camera
	{
	public:

		Camera(std::shared_ptr<Window> w);	//コンストラクタ
		~Camera();							//デストラクタ


		// ###################### 設定　関係 ###################### 
		void setPosition(glm::vec3 p);	//座標
		void setLook(glm::vec3 l);		//視線


		// ###################### 取得　関係 ###################### 
		glm::vec3 getPosition();	//座標
		glm::vec3 getLook();		//視線

		//カメラ行列を取得
		glm::mat4 getViewProjection();		//3Dカメラ
		glm::mat4 getProjection_2D();		//2Dカメラ



	private:
		glm::vec3 vecPosition;	//座標
		glm::vec3 vecLook;		//向き(視線)

		glm::mat4 view;			//ビュー行列
		glm::mat4 projection;	//透視射形行列

		std::shared_ptr<Window> windowContext;	//ウインドウコンテキスト

	};
}
#endif


