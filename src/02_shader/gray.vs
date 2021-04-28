#version 330 core
layout (location=0) in vec3 position;
layout (location=1) in float grayscale;

out vec4 vertexColor;

void main()
{
    gl_Position=vec4(position,1.0);
    vertexColor=vec4(grayscale,grayscale,grayscale,1.0f);
}