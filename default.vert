/*Codigo fuente Vertex Shader en lenguaje OpenGL (GLSL)*/
//version de GLSL que estoy usando 
#version 330 core
layout (location = 0) in vec3 aPos; //lee lo que esta en la aplicacion 
layout (location = 1) in vec3 aColor; 

out vec3 color;

void main ()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = aColor;
};