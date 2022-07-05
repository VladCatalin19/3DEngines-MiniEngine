#version 430

layout(location = 0) in vec3 frag_normal;
layout(location = 0) out vec4 frag_colour;

void main()
{
    frag_colour = vec4((frag_normal + 1) / 2, 1.0);
}
