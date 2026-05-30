#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderClass.h"

class Camera
{
public:
	// Vectores de posición y orientación de la cámara
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Dimensiones de la ventana
	int width;
	int height;

	// Configuración de movimiento y sensibilidad
	float speed = 0.05f;
	float sensitivity = 100.0f;

	// Variables para evitar saltos bruscos del mouse al arrancar
	bool firstClick = true;

	// Constructor
	Camera(int width, int height, glm::vec3 position);

	// Envía las matrices de Vista y Proyección al Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

	// Maneja las entradas del teclado y mouse
	void Inputs(GLFWwindow* window);
};

#endif
