#version 430

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

layout(location = 0) out vec3 world_normal;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(vertex_position, 1.0);
    world_normal = normalize(vertex_normal);
}
