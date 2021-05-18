#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

//�R���X�g���N�^
FrameWork::Shader::Shader()
{
	program = 0;	//�V�F�[�_�[�v���O������������
}


//�V�F�[�_�[�����[�h
bool FrameWork::Shader::LoadShader(const char* vert, const char* frag)
{

	glDeleteShader(program);

	program = loadProgram(vert, frag);

	if (program == 0)
	{
		std::cerr << "�V�F�[�_�[�v���O�����쐬�G���[" << std::endl;
		//assert(program);
		//exit(1);
		return false;
	}

	return true;
}




//�V�F�[�_�[�����[�h
GLuint FrameWork::Shader::loadProgram(const char* vert, const char* frag)
{
	std::vector<GLchar> vsrc;
	const bool vstat = ReadShaderSource(vert, vsrc);
	

	std::vector<GLchar> fsrc;
	const bool fstat = ReadShaderSource(frag, fsrc);
	
	if (vstat && fstat)
	{
		return CreateProgram(vsrc.data(), fsrc.data());
		
	}
	else {
		//printf("������");
		//assert(0 && "�V�F�[�_�[�t�@�C���ǂݍ��݃G���[");
		return 0;
	}
}



//�V�F�[�_�[�t�@�C����ǂݍ���
bool FrameWork::Shader::ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == NULL)
	{
		//assert(0 && "�V�F�[�_�[�t�@�C�����w�肳��Ă��܂���B");
		return false;
	}
	

	std::ifstream file(name, std::ios::binary);
	if (file.fail() == true)
	{
		//printf("��������");
		std::cerr << "�\�[�X�t�@�C�����ǂݍ��߂܂���: " << name << std::endl;
		file.close();
		return false;
	}
	else
	{
		file.seekg(0L, std::ios::end);
		GLsizei length = static_cast<GLsizei>(file.tellg());
		buffer.resize(length + 1);

		file.seekg(0L, std::ios::beg);
		file.read(buffer.data(), length);
		buffer[length] = '\0';

		

		file.close();
	}
	file.close();

	return true;
}


//�V�F�[�_�[�G���[���O���擾
GLboolean FrameWork::Shader::CompileInfoLog(GLuint shader,const char* str)
{
	GLint status;

	//�R���p�C������
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << str << std::endl;
	}
	
	//�G���[���O�̒����𓾂�
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);

		std::cerr<< &infoLog[0] << std::endl;
	}



	return (GLboolean)status;
}

//�v���O�����I�u�W�F�N�g�쐬
GLuint FrameWork::Shader::CreateProgram(const char* vsrc, const char* fsrc)
{
	const GLuint program = glCreateProgram();	//�V�F�[�_�[�v���O�������쐬
	
	//std::cout << program << std::endl;

	if (vsrc != NULL)
	{
		const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);


		//std::cerr << "���_�V�F�[�_�[�@�R���p�C���G���[" << std::endl << std::endl;
		CompileInfoLog(vobj, vsrc);

		glAttachShader(program, vobj);
		glDeleteShader(vobj);

	}
	else {
		std::cout << "���_�V�F�[�_�[�ǂݍ��ݎ��s" << std::endl;
	}

	if (fsrc != NULL)
	{
		const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		//std::cerr << "�t���O�����g�V�F�[�_�[�@�R���p�C���G���[" << std::endl << std::endl;
		CompileInfoLog(fobj, fsrc);

		glAttachShader(program, fobj);
		glDeleteShader(fobj);
	}
	else {
		std::cout << "�t���O�����g�V�F�[�_�[�ǂݍ��ݎ��s" << std::endl;

	}

	glLinkProgram(program);		//�����N�v���O����
	ProgramInfoLog(program);	//�����N���̃��O��\��
	
	return program;
}

//�v���O�����̃G���[��\��
GLboolean FrameWork::Shader::ProgramInfoLog(GLuint program)
{
	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1) 
	{
		std::vector<GLchar> infoLog(bufSize);
	
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr<<"Program Info Log: "<< infoLog.data() <<std::endl;

		return false;
	}
	else
	{
		return true;
	}
}

//location���擾
GLint FrameWork::Shader::getAttribLocation(const char* str)
{
	return glGetAttribLocation(program,str);
}



//���_�V�F�[�_�[�ɑ����ϐ����֘A������
void FrameWork::Shader::setBindAttribVertex(const char* str)
{
	GLint n = glGetAttribLocation(program, str);

	//�G���[����
	if (n == -1)
	{
		std::cerr <<"setBindAttribVertex(): "<< n << std::endl;
	}
	else 
	{
		glBindAttribLocation(program, n, str);
	}
}


//�t���O�����g�V�F�[�_�[�ɑ����ϐ����֘A������
void FrameWork::Shader::setBindAttribFragment(const char* str)
{
	GLint n = glGetAttribLocation(program, str);

	//�G���[����
	if (n == -1)
	{
		std::cerr << "setBindAttribFragment(): " << n << std::endl;
	}
	else 
	{
		glBindFragDataLocation(program, n, str);
	}
}

//�L���ɂ���
void FrameWork::Shader::setEnable()
{
	glUseProgram(program);

}

//�����ɂ���
void FrameWork::Shader::setDisable()
{
	glUseProgram(0);

}

// ###################### Uniform �ݒ� ######################
  
//vec1
void FrameWork::Shader::setUniform1f(const char* name, const float vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniform1f(object,vec);
}

//vec2
void FrameWork::Shader::setUniform2f(const char* name, const glm::vec2 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniform2f(object,vec.x,vec.y);
}

//vec3
void FrameWork::Shader::setUniform3f(const char* name, const glm::vec3 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniform3f(object,vec.x, vec.y,vec.z);
}

//vec4
void FrameWork::Shader::setUniform4f(const char* name, const glm::vec4 vec)
{	
	const GLuint object = glGetUniformLocation(program,name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniform4f(object, vec.x, vec.y, vec.z, vec.w);	
}


//�s��2
void FrameWork::Shader::setUniformMatrix2fv(const char* name, const glm::mat2 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniformMatrix2fv(object,1,false,glm::value_ptr(m));
}

//�s��R
void FrameWork::Shader::setUniformMatrix3fv(const char* name, const glm::mat3 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniformMatrix3fv(object, 1, false, glm::value_ptr(m));
}

//�s��4
void FrameWork::Shader::setUniformMatrix4fv(const char* name, const glm::mat4 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//�G���[����
	glUniformMatrix4fv(object, 1, false, glm::value_ptr(m));

}

//�f�X�g���N�^
FrameWork::Shader::~Shader()
{
	//std::cout << "shader class �f�X�g���N�^\n" << std::endl;	
	glDeleteProgram(program);
}