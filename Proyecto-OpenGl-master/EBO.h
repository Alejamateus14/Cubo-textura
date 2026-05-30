#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID; //identificacion publica
	EBO(GLuint* indices, GLsizeiptr size); /*Constructor que recibe los indices en bytes*/

	void Bind();
	void Unbind();
	void Delete();
};

#endif 
