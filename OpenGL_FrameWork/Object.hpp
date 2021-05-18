#ifndef ___OBJECT_H
#define ___OBJECT_H

#include <iostream>
#include <glew/include/GL/glew.h>

//図形オブジェクト
class Object
{
public:

	//頂点
	struct Vertex
	{
		GLfloat position[2];	//座標
	};



	Object(GLint size,GLsizei vertexcount,const Vertex *vertex);
	virtual ~Object();
	void bind()const;
	




private:
	GLuint vao;	//頂点配列オブジェクト
	GLuint vbo;	//頂点バッファオブジェクト
	Object(const Object& o);	//コピー禁止
	Object& operator = (const Object& o);	//代入禁止


};



#endif
