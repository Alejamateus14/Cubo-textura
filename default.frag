//Codigo fuente Fragment Shader
#version 330 core
out vec4 FragColor;

in vec3 color;

void main()
{
	//Color del triangulo(rosado)
	FragColor = vec4(color,1.0f);

};