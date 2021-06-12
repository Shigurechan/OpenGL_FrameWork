#ifndef ___CAMERA_HPP_
#define ___CAMERA_HPP_
#include <iostream>
#include "glm/glm.hpp"
/*#########################################################################
# Camera�N���X

����
	
###########################################################################*/
namespace FrameWork
{
	class Window;

	class Camera
	{
	public:

		Camera(std::shared_ptr<Window> w);	//�R���X�g���N�^
		~Camera();							//�f�X�g���N�^

		// ###################### �ݒ�@�֌W ###################### 
		void setPosition(glm::vec3 p);	//���W
		void setLook(glm::vec3 l);		//����

		// ###################### �擾�@�֌W ###################### 
		glm::vec3 getPosition();	//���W
		glm::vec3 getLook();		//����

		//�J�����s����擾
		glm::mat4 getViewProjection();		//3D�J����
		glm::mat4 getProjection_2D();		//2D�J����

	private:
		glm::vec3 vecPosition;	//���W
		glm::vec3 vecLook;		//����(����)
		glm::mat4 view;			//�r���[�s��
		glm::mat4 projection;	//�����ˌ`�s��

		std::shared_ptr<Window> windowContext;	//�E�C���h�E�R���e�L�X�g
	};
}
#endif


