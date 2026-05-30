#include"ShaderClass.h"
std::string get_file_contents(const char* filename)
{

	/*Función Filereader*/
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

/*Constructor del Shader*/
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	/* Cadena de archivoa de los text file*/
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	/*Se convierten y guardan en matrices de caracteres*/
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	/*Creacion del objeto VertexShader 	Referencia para almacenar el vertex shader*/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*Ajustar el vertex shader al código fuente poner el Vertex shader al
	objeto ya creado*/
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	/*GPU no entiende codigo fuente, se debe complilar en código de maquina*/
	glCompileShader(vertexShader);

	//Se repiten los pasos anteriores para fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	/*Para usar ambos shaders se agregan a un programa de shaders*/
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	//Se borra por estetica
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

/*Funcion ativate*/

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}