#ifndef MG3TR_SRC_CONSTANTS_GRAPHICSCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_GRAPHICSCONSTANTS_HPP_INCLUDED

#include <string>

namespace MG3TR
{
    namespace MeshConstants
    {
        const unsigned k_vertices_location = 0;
        const unsigned k_normals_location = 1;
        const unsigned k_uvs_location = 2;
    }

    namespace SceneConstants
    {
        const std::string k_cube_path(MG3TR_ROOT_DIR "res/Models/Cube/cube.obj");
        const std::string k_skybox_path(MG3TR_ROOT_DIR "res/Models/Skybox/skybox.obj");
        const std::string k_creeper_path(MG3TR_ROOT_DIR "res/Models/Creeper/creeper.obj");
        const std::string k_sphere_path(MG3TR_ROOT_DIR "res/Models/Sphere/sphere.obj");
        const std::string k_map_path(MG3TR_ROOT_DIR "res/Models/MinecraftScene/Mineways2Skfb.obj");
    }

    namespace ShaderConstants
    {
        const std::string k_fragment_normal_vertex_shader(MG3TR_ROOT_DIR "res/Shaders/FragmentNormal.vert");
        const std::string k_fragment_normal_fragment_shader(MG3TR_ROOT_DIR "res/Shaders/FragmentNormal.frag");

        const std::string k_texture_vertex_shader(MG3TR_ROOT_DIR "res/Shaders/Texture.vert");
        const std::string k_texture_fragment_shader(MG3TR_ROOT_DIR "res/Shaders/Texture.frag");

        const std::string k_texture_and_lighting_vertex_shader(MG3TR_ROOT_DIR "res/Shaders/TextureAndLighting.vert");
        const std::string k_texture_and_lighting_fragment_shader(MG3TR_ROOT_DIR "res/Shaders/TextureAndLighting.frag");
    
        const std::string k_model_uniform_location("u_model");
        const std::string k_view_uniform_location("u_view");
        const std::string k_projection_uniform_location("u_projection");

        const std::string k_camera_position_uniform_location("u_camera_position");
        const std::string k_light_position_uniform_location("u_light_position");
    }
}

#endif // MG3TR_SRC_CONSTANTS_GRAPHICSCONSTANTS_HPP_INCLUDED
