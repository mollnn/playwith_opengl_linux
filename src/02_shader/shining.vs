#version 330 core
layout (location = 0) in vec3 position;


void main()
{
    gl_Position = vec4(0.5*position.x+0.5, 0.5*position.y-0.5, 0.5*position.z-0.5, 1.0f);
}