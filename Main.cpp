#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"EBO.h"

/*Hola mundo */

/*Luego de crear las clases aparte en esta incluir los encabezados creados, reemplazando 
las funciones predeterminadas */

/*escena del sombreador, generar los vertices del sombreador, trabajaremos en 2D origen 
en el medio de la ventana, ejex a la derecha y el ejey apunta hacia arriba 
*/

/*Creacion de matriz GLFW que contiene las cooordenadas del triangulo,
estas deben estar entre -1 y 1*/

//Coordenadas de los vetices 
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,    /*esquina inferior izquierda*/
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    /*esquina inferior derecha*/
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    /*esquina superior*/
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
};

GLuint indices[] =
{
	0,3,5,
	3,2,4,
	5,4,1
};


int main()
{
	//inicializar GLFW y finalizarla
	glfwInit();

	//sugerencias
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Version principal
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Version menor

	/*perfil: paquete de funciones, CORE: funciones modernas*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//Creacion de la ventana
	GLFWwindow* window = glfwCreateWindow(800, 800, "Ventana OpenGL", NULL,NULL);

	//verificacion de errores
	if (window == NULL)
	{
		std::cout << "Error al crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}
	 
	glfwMakeContextCurrent(window);
	/* hace que la ventana sea un contexto, que es un objeto de Open GL, como se crea la ventana tambien hay que eliminarla se crea un ciclio While que 
	evita que apenas se cree se destruya automaticamente*/

	gladLoadGL();

	glViewport(0, 0, 800, 800); //que es lo que Open Gl debe renderizar

	/*Crear el objeto Shader*/
	Shader shaderProgram("default.vert", "default.frag");

	/*Crear objeto matriz de vertices y bincular*/
	VAO VAO1;
	VAO1.Bind();

	/*Generate vertex buffer object and link ot to vertices*/
	VBO VBO1(vertices, sizeof(vertices));
	/*Generate element buffer object and link ot to indices*/
	EBO EBO1(indices, sizeof(indices));

	/*vincular VBO a VAO*/
    VAO1.LinkVBO(VBO1, 0);

	EBO1.Bind();
	/*Desvincular para evitar modificarlo accidentalmente*/
	VAO1.Unbind();
	VBO1.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.78f, 0.65f, 0.90f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 

		/*Decirle a OpenGl que programa usar y activarlo*/
		shaderProgram.Activate();

		/*atar el VAO para que OpenGL lo sepa usar*/
		VAO1.Bind();

        /*dibujar el triangulo con las primitivas de OpenGL usando los indices*/
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents(); 
	}

	//Se eliminan todos los objetos creados 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	//Borrar la ventana cuando acabe el programa
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
