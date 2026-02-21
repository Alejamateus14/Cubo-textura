#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

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
	/* hace que la ventana se un contexto, que es un objeto de Open GL, 
	como se crea la ventana tambien hay que eliminarla se crea un ciclio While que 
	evita que apenas se cree se destruya automaticamente*/

	gladLoadGL();

	glViewport(0, 0, 800, 800); //que es lo que Open Gl debe renderizar

	//Borrar color y poner otro
	glClearColor(0.78f, 0.65f, 0.90f, 1.0f); //Color lila
	glClear(GL_COLOR_BUFFER_BIT); //Open GL ejecuta el comando del buffer

	glfwSwapBuffers(window); //cambia del porterior al frontal

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); 
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}