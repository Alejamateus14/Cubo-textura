#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 model;
uniform mat4 camMatrix; // <--- Reemplazamos 'view' y 'proj' por esta

void main() {
    // Multiplicamos la matriz de la cámara por la del modelo
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
    color = aColor;
}