#version 430

uniform sampler2D u_texture_0;

layout(location = 0) in vec2 in_uv;

layout(location = 0) out vec4 out_color;

void main()
{
    out_color = texture(u_texture_0, in_uv);

    if (out_color.a < 0.5F)
    {
        discard;
    }
}
