#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
	public:
		GLuint ID; //identificacion publica
		VBO(GLfloat* vertices, GLsizeiptr size); /*Constructor que recibe los vertices en bytes*/

		void Bind(); //Enlazar
		void Unbind(); //Desenlazar
		void Delete();
};

#endif 

