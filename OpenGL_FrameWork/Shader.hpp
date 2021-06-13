#ifndef ___SHADER_HPP_
#define ___SHADER_HPP_
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include <glew/include/GL/glew.h>
/*#########################################################################
# �V�F�[�_�[�N���X

����
	�p�����ăV�F�[�_�[������
###########################################################################*/
namespace FrameWork
{
	class Shader
	{

	public:

		Shader();	//�R���X�g���N�^
		~Shader();	//�f�X�g���N�^

		bool LoadShader(const char* vert, const char* frag);	//�V�F�[�_�[�ǂݍ���

		void setEnable();	//�L��
		void setDisable();	//����

		void setBindAttribVertex(const char* str);		//���_�V�F�[�_�[�ɑ����ϐ����֘A������
		void setBindAttribFragment(const char* str);	//�t���O�����g�V�F�[�_�[�ɑ����ϐ����֘A������
		GLint getAttribLocation(const char* str);		//location���擾

		//Uniform �ݒ�
		void setUniform1f(const char* name, const float vec);
		void setUniform2f(const char* name, const glm::vec2 vec);
		void setUniform3f(const char* name, const glm::vec3 vec);
		void setUniform4f(const char* name, const glm::vec4 vec);

		//Unform�s��@�ݒ�
		void setUniformMatrix2fv(const char* name, const glm::mat2 m);
		void setUniformMatrix3fv(const char* name, const glm::mat3 m);
		void setUniformMatrix4fv(const char* name, const glm::mat4 m);

	private:

		GLuint CreateProgram(const char* vsrc, const char* fsrc);				//�v���O�����I�u�W�F�N�g���쐬
		GLboolean CompileInfoLog(GLuint shader, const char* str);				//�R���p�C���G���[���O���擾
		GLboolean ProgramInfoLog(GLuint program);								//�v���O�������O���擾
		bool ReadShaderSource(const char* name, std::vector<GLchar>& buffer);	//�\�[�X�t�@�C����ǂݍ���
		GLuint loadProgram(const char* vert, const char* frag);					//�v���O�������I�u�W�F�N�g�����[�h

		GLuint program;	//�v���O�����I�u�W�F�N�g�V�F�[�_�[
	};
}
#endif

