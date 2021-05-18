#ifndef ___SHADER_HPP
#define ___SHADER_HPP

#include <iostream>
#include <vector>
#include "glm/glm.hpp"


#include <glew/include/GL/glew.h>
//#include <glfw/include/GLFW/glfw3.h>


namespace FrameWork
{
	class Shader
	{
	public:
		Shader();	//コンストラクタ
		~Shader();	//デストラクタ

		bool LoadShader(const char* vert, const char* frag);	//シェーダー読み込み


		void setEnable();	//有効
		void setDisable();	//無効

		void setBindAttribVertex(const char* str);		//頂点シェーダーに属性変数を関連ずける
		void setBindAttribFragment(const char* str);	//フラグメントシェーダーに属性変数を関連ずける
		GLint getAttribLocation(const char* str);		//locationを取得


		//Uniform 設定
		void setUniform1f(const char* name, const float vec);
		void setUniform2f(const char* name, const glm::vec2 vec);
		void setUniform3f(const char* name, const glm::vec3 vec);
		void setUniform4f(const char* name, const glm::vec4 vec);

		//Unform行列　設定
		void setUniformMatrix2fv(const char* name, const glm::mat2 m);
		void setUniformMatrix3fv(const char* name, const glm::mat3 m);
		void setUniformMatrix4fv(const char* name, const glm::mat4 m);



	private:


		GLuint CreateProgram(const char* vsrc, const char* fsrc);				//プログラムオブジェクトを作成
		GLboolean CompileInfoLog(GLuint shader, const char* str);				//コンパイルエラーログを取得
		GLboolean ProgramInfoLog(GLuint program);								//プログラムログを取得
		bool ReadShaderSource(const char* name, std::vector<GLchar>& buffer);	//ソースファイルを読み込み
		GLuint loadProgram(const char* vert, const char* frag);					//プログラムをオブジェクトをロード

		GLuint program;	//プログラムオブジェクトシェーダー

	};
}
#endif

