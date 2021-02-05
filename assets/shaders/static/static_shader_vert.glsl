#version 440

in vec3 in_position;

uniform mat4 u_proj;
uniform mat4 u_model;

void main()
{
    gl_Position = u_proj * u_model * vec4(in_position, 1);
}