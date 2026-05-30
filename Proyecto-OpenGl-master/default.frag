#version 330 core
out vec4 FragColor;

in vec3 color; 

uniform vec3 colorLinea; 
uniform bool esLinea;    

void main()
{
    if (esLinea) 
    {
        FragColor = vec4(colorLinea, 1.0f); 
    } 
    else 
    {
        FragColor = vec4(color, 1.0f);      
    }
}