/* Aqui se delclarará la clase y otras funciones 
El #infdef y #define ayuda a que no se abra archivo dos veces */

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

/*Se crea una funcion que lea los Shaders, genera el contenido de un archivo texto como una cadena*/
std::string get_file_contents(const char* filename);

//declarar la clase del Shader (encapsulado)
class Shader
{
	public:
		//identificacion publica
		GLuint ID;

		//constructor que reciba el código fuente
		Shader(const char* vertexFile, const char* fragmentFile); 

		//Funciones 
		void Activate();
		void Delete();
};

#endif
