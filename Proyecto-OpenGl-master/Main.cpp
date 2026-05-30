#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>

/*Matrices*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"ShaderClass.h"
#include"VAO.h"
#include"EBO.h"
#include "camera.h"

/*Luego de crear las clases aparte en esta incluir los encabezados creados, reemplazando 
las funciones predeterminadas */

/*escena del sombreador, generar los vertices del sombreador, trabajaremos en 2D origen 
en el medio de la ventana, ejex a la derecha y el ejey apunta hacia arriba 
*/

/*Creacion de matriz GLFW que contiene las cooordenadas del triangulo,
estas deben estar entre -1 y 1*/

//Coordenadas de los vetices 
GLfloat vertices[] =
{/*           COORDENADAS                /           COLORES              */
	-0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f, // Front-bottom-left
	 0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f, // Front-bottom-right
	 0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f, // Front-top-right
	-0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f, // Front-top-left
	-0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f, // Back-bottom-left
	 0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 1.0f, // Back-bottom-right
	 0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f, // Back-top-right
	-0.5f,  0.5f, -0.5f,     0.1f, 0.1f, 0.1f  // Back-top-left
};

GLuint indices[] =
{
	0, 1, 2,  2, 3, 0, // Cara frontal
	1, 5, 6,  6, 2, 1, // Cara derecha
	7, 6, 5,  5, 4, 7, // Cara trasera
	4, 0, 3,  3, 7, 4, // Cara izquierda
	4, 5, 1,  1, 0, 4, // Cara inferior
	3, 2, 6,  6, 7, 3  // Cara superior
};


glm::vec3 calcularBezierCubica(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t) {
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;

	// Aplicamos la fórmula matemática
	glm::vec3 p = uuu * p0; // (1-t)^3 * P0
	p += 3.0f * uu * t * p1; // 3 * (1-t)^2 * t * P1
	p += 3.0f * u * tt * p2; // 3 * (1-t) * t^2 * P2
	p += ttt * p3;           // t^3 * P3

	return p;
}

const int PUNTOS_CURVA = 100; // 100 segmentos harán que se vea muy fluida


int main()
{
	//inicializar GLFW y finalizarla
	glfwInit();

	//sugerencias
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Version principal
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Version menor
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
    VAO1.LinkAttrib(VBO1, 0,3,GL_FLOAT,6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1,3,GL_FLOAT,6 * sizeof(float), (void*)(3 * sizeof(float)));

	EBO1.Bind();
	/*Desvincular para evitar modificarlo accidentalmente*/
	VAO1.Unbind();
	VBO1.Unbind();

	/*Para que no se vea transparente, guarda la distancia (coordenada Z) de cada píxel*/
	glEnable(GL_DEPTH_TEST);

	Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 3.0f));

	// Definir puntos de control para la trayectoria del cubo
	glm::vec3 P0 = glm::vec3(-3.0f, 0.0f, -2.0f); // Inicio
	glm::vec3 P1 = glm::vec3(-1.5f, 4.0f, 0.0f); // Curva hacia arriba
	glm::vec3 P2 = glm::vec3(1.5f, -4.0f, 2.0f); // Curva hacia abajo
	glm::vec3 P3 = glm::vec3(3.0f, 0.0f, -2.0f); // Fin

	float t_bezier = 0.0f;    // Parámetro de la curva
	float velocidad = 0.2f;   // Qué tan rápido recorre la curva
	bool avanzando = true;    // Para hacer un efecto de "ida y vuelta" (ping-pong)

	/*Generar los puntos de la curva de Bézier*/
	std::vector<GLfloat> verticesCurva;
	for (int i = 0; i <= PUNTOS_CURVA; i++) {
		float t = (float)i / (float)PUNTOS_CURVA;
		// Usamos tus mismos puntos de control P0, P1, P2, P3
		glm::vec3 punto = calcularBezierCubica(P0, P1, P2, P3, t);

		// Guardamos la posición (X, Y, Z)
		verticesCurva.push_back(punto.x);
		verticesCurva.push_back(punto.y);
		verticesCurva.push_back(punto.z);
	}

	// 2. Crear buffers de OpenGL exclusivos para la línea
	GLuint VAO_Linea, VBO_Linea;
	glGenVertexArrays(1, &VAO_Linea);
	glGenBuffers(1, &VBO_Linea);

	glBindVertexArray(VAO_Linea);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Linea);
	// Pasamos los datos del vector a la GPU
	glBufferData(GL_ARRAY_BUFFER, verticesCurva.size() * sizeof(GLfloat), verticesCurva.data(), GL_STATIC_DRAW);

	// Configurar el atributo de posición (locación 0 en el shader)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Desvincular para seguridad
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		/*Color fondo*/
		glClearColor(0.78f, 0.65f, 0.90f, 1.0f); 

		// Limpiar buffer de color y profundidad
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		
		/*Decirle a OpenGl que programa usar y activarlo*/
		shaderProgram.Activate();

		if (avanzando) {
			t_bezier += velocidad * 0.01f;
			if (t_bezier >= 1.0f) {
				t_bezier = 1.0f;
				avanzando = false;
			}
		}
		else {
			t_bezier -= velocidad * 0.01f;
			if (t_bezier <= 0.0f) {
				t_bezier = 0.0f;
				avanzando = true;
			}
		}

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0, shaderProgram, "camMatrix");

		glUniform1i(glGetUniformLocation(shaderProgram.ID, "esLinea"), GL_FALSE);

		glm::vec3 posicionCubo = calcularBezierCubica(P0, P1, P2, P3, t_bezier);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, posicionCubo); // Traslación en la curva

		float rotation = (float)glfwGetTime() * glm::radians(50.0f);
		model = glm::rotate(model, rotation, glm::vec3(0.5f, 1.0f, 0.0f)); // Rotación propia

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		GLuint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 índices para un cubo
		VAO1.Unbind();

		glUniform1i(glGetUniformLocation(shaderProgram.ID, "esLinea"), GL_TRUE);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "colorLinea"), 0.5f, 0.0f, 0.8f);

		glm::mat4 modelLinea = glm::mat4(1.0f); // Línea estática en el mapa
		modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLinea));

		glLineWidth(3.0f);
		glBindVertexArray(VAO_Linea);
		glDrawArrays(GL_LINE_STRIP, 0, PUNTOS_CURVA + 1);
		glBindVertexArray(0);

		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

	//Se eliminan todos los objetos creados 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glDeleteVertexArrays(1, &VAO_Linea);
	glDeleteBuffers(1, &VBO_Linea);

	//Borrar la ventana cuando acabe el programa
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
