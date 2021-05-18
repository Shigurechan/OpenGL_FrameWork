#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

//コンストラクタ
FrameWork::Shader::Shader()
{
	program = 0;	//シェーダープログラムを初期化
}


//シェーダーをロード
bool FrameWork::Shader::LoadShader(const char* vert, const char* frag)
{

	glDeleteShader(program);

	program = loadProgram(vert, frag);

	if (program == 0)
	{
		std::cerr << "シェーダープログラム作成エラー" << std::endl;
		//assert(program);
		//exit(1);
		return false;
	}

	return true;
}




//シェーダーをロード
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
		//printf("あああ");
		//assert(0 && "シェーダーファイル読み込みエラー");
		return 0;
	}
}



//シェーダーファイルを読み込む
bool FrameWork::Shader::ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == NULL)
	{
		//assert(0 && "シェーダーファイルが指定されていません。");
		return false;
	}
	

	std::ifstream file(name, std::ios::binary);
	if (file.fail() == true)
	{
		//printf("うううう");
		std::cerr << "ソースファイルが読み込めません: " << name << std::endl;
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


//シェーダーエラーログを取得
GLboolean FrameWork::Shader::CompileInfoLog(GLuint shader,const char* str)
{
	GLint status;

	//コンパイル結果
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << str << std::endl;
	}
	
	//エラーログの長さを得る
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

//プログラムオブジェクト作成
GLuint FrameWork::Shader::CreateProgram(const char* vsrc, const char* fsrc)
{
	const GLuint program = glCreateProgram();	//シェーダープログラムを作成
	
	//std::cout << program << std::endl;

	if (vsrc != NULL)
	{
		const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);


		//std::cerr << "頂点シェーダー　コンパイルエラー" << std::endl << std::endl;
		CompileInfoLog(vobj, vsrc);

		glAttachShader(program, vobj);
		glDeleteShader(vobj);

	}
	else {
		std::cout << "頂点シェーダー読み込み失敗" << std::endl;
	}

	if (fsrc != NULL)
	{
		const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		//std::cerr << "フラグメントシェーダー　コンパイルエラー" << std::endl << std::endl;
		CompileInfoLog(fobj, fsrc);

		glAttachShader(program, fobj);
		glDeleteShader(fobj);
	}
	else {
		std::cout << "フラグメントシェーダー読み込み失敗" << std::endl;

	}

	glLinkProgram(program);		//リンクプログラム
	ProgramInfoLog(program);	//リンク時のログを表示
	
	return program;
}

//プログラムのエラーを表示
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

//locationを取得
GLint FrameWork::Shader::getAttribLocation(const char* str)
{
	return glGetAttribLocation(program,str);
}



//頂点シェーダーに属性変数を関連ずける
void FrameWork::Shader::setBindAttribVertex(const char* str)
{
	GLint n = glGetAttribLocation(program, str);

	//エラー処理
	if (n == -1)
	{
		std::cerr <<"setBindAttribVertex(): "<< n << std::endl;
	}
	else 
	{
		glBindAttribLocation(program, n, str);
	}
}


//フラグメントシェーダーに属性変数を関連ずける
void FrameWork::Shader::setBindAttribFragment(const char* str)
{
	GLint n = glGetAttribLocation(program, str);

	//エラー処理
	if (n == -1)
	{
		std::cerr << "setBindAttribFragment(): " << n << std::endl;
	}
	else 
	{
		glBindFragDataLocation(program, n, str);
	}
}

//有効にする
void FrameWork::Shader::setEnable()
{
	glUseProgram(program);

}

//無効にする
void FrameWork::Shader::setDisable()
{
	glUseProgram(0);

}

// ###################### Uniform 設定 ######################
  
//vec1
void FrameWork::Shader::setUniform1f(const char* name, const float vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform1f(object,vec);
}

//vec2
void FrameWork::Shader::setUniform2f(const char* name, const glm::vec2 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform2f(object,vec.x,vec.y);
}

//vec3
void FrameWork::Shader::setUniform3f(const char* name, const glm::vec3 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform3f(object,vec.x, vec.y,vec.z);
}

//vec4
void FrameWork::Shader::setUniform4f(const char* name, const glm::vec4 vec)
{	
	const GLuint object = glGetUniformLocation(program,name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform4f(object, vec.x, vec.y, vec.z, vec.w);	
}


//行列2
void FrameWork::Shader::setUniformMatrix2fv(const char* name, const glm::mat2 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniformMatrix2fv(object,1,false,glm::value_ptr(m));
}

//行列３
void FrameWork::Shader::setUniformMatrix3fv(const char* name, const glm::mat3 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniformMatrix3fv(object, 1, false, glm::value_ptr(m));
}

//行列4
void FrameWork::Shader::setUniformMatrix4fv(const char* name, const glm::mat4 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniformMatrix4fv(object, 1, false, glm::value_ptr(m));

}

//デストラクタ
FrameWork::Shader::~Shader()
{
	//std::cout << "shader class デストラクタ\n" << std::endl;	
	glDeleteProgram(program);
}
