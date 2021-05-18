#ifndef ___SHAPE_HPP
#define ___SHAPE_HPP
#include <iostream>
#include "Object.hpp"


class Shape 
{
public:
	Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex);
	void Draw()const;


private:
	std::shared_ptr<const Object> object;
protected:
	const GLsizei vertexcount;
	virtual void execute()const;

};


#endif