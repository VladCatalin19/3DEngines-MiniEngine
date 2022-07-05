#version 430

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

layout(location = 0) in vec3 in_vertex_position;
layout(location = 1) in vec3 in_vertex_normal;
layout(location = 2) in vec2 in_vertex_uv;

layout(location = 0) out vec3 out_world_position;
layout(location = 1) out vec3 out_world_normal;
layout(location = 2) out vec2 out_uv;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(in_vertex_position, 1.0);

    out_world_position = (u_model * vec4(in_vertex_position, 1.0F)).xyz;
	out_world_normal = (u_model * vec4(in_vertex_normal, 1.0F)).xyz;
	out_uv = in_vertex_uv;
}
