#ifndef MG3TR_SRC_CONSTANTS_GRAPHICSCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_GRAPHICSCONSTANTS_HPP_INCLUDED

namespace MG3TR
{
    namespace MeshConstants
    {
        constexpr unsigned k_vertices_location = 0;
        constexpr unsigned k_normals_location = 1;
        constexpr unsigned k_uvs_location = 2;
    }

    namespace ShaderConstants
    {
        constexpr char k_fragment_normal_vertex_shader[] = "res/Shaders/FragmentNormal.vert";
        constexpr char k_fragment_normal_fragment_shader[] = "res/Shaders/FragmentNormal.frag";

        constexpr char k_texture_vertex_shader[] = "res/Shaders/Texture.vert";
        constexpr char k_texture_fragment_shader[] = "res/Shaders/Texture.frag";

        constexpr char k_texture_and_lighting_vertex_shader[] = "res/Shaders/TextureAndLighting.vert";
        constexpr char k_texture_and_lighting_fragment_shader[] = "res/Shaders/TextureAndLighting.frag";
    
        constexpr char k_model_uniform_location[] = "u_model";
        constexpr char k_view_uniform_location[] = "u_view";
        constexpr char k_projection_uniform_location[] = "u_projection";

        constexpr char k_camera_position_uniform_location[] = "u_camera_position";
        constexpr char k_light_position_uniform_location[] = "u_light_position";
    }
}

#endif // MG3TR_SRC_CONSTANTS_GRAPHICSCONSTANTS_HPP_INCLUDED
