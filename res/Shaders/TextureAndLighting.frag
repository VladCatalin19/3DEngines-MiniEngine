#version 430

uniform sampler2D u_texture_0;
uniform vec3 u_camera_position;
uniform vec3 u_light_position;

layout(location = 0) in vec3 in_world_position;
layout(location = 1) in vec3 in_world_normal;
layout(location = 2) in vec2 in_uv;

layout(location = 0) out vec4 out_color;

const float k_ambient = 0.7F;
const float k_diffuse = 1.2F;
const float k_specular = 0.01F;

void main()
{
    vec4 texture_color = texture(u_texture_0, in_uv);

    if (texture_color.a < 0.5F)
    {
        discard;
    }

    vec3 normal = normalize(in_world_normal);
    vec3 light_direction = normalize(u_light_position - in_world_position);
    vec3 view_direction = normalize(u_camera_position - in_world_position);
    vec3 reflection_direction = reflect(light_direction, normal);

    float ambient_light = k_ambient;
    float diffuse_light = k_diffuse * max(dot(normal, light_direction), -0.15F);
    float specular_light = k_specular * pow(max(dot(reflection_direction, view_direction), 0.0F), 0.5F);

    out_color = (ambient_light + diffuse_light + specular_light) * texture_color;
}
