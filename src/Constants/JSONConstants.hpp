#ifndef MG3TR_SRC_CONSTANTS_JSONCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_JSONCONSTANTS_HPP_INCLUDED

#include <string>

namespace MG3TR
{
    namespace TransformJSONConstants
    {
        const std::string k_parent_node("transform");
        const std::string k_uid_attribute("uid");
        const std::string k_local_position_attribute("local position");
        const std::string k_local_rotation_attribute("local rotation");
        const std::string k_local_scale_attribute("local scale");
        const std::string k_children_attribute("children");
        const std::string k_game_object_attribute("game object");
    }

    namespace GameObjectJSONConstants
    {
        const std::string k_parent_node("game object");
        const std::string k_uid_attribute("uid");
        const std::string k_name_attribute("name");
        const std::string k_components_attribute("components");
    }

    namespace CameraJSONConstants
    {
        const std::string k_parent_node("camera");
        const std::string k_uid_attribute("uid");
        const std::string k_camera_mode_attribute("camera mode");
        const std::string k_fov_attribute("fov");
        const std::string k_aspect_ratio_attribute("aspect ratio");
        const std::string k_xmin_attribute("xmin");
        const std::string k_xmax_attribute("xmax");
        const std::string k_ymin_attribute("ymin");
        const std::string k_ymax_attribute("ymax");
        const std::string k_znear_attribute("znear");
        const std::string k_zfar_attribute("zfar");
    }

    namespace CameraControllerJSONConstants
    {
        const std::string k_parent_node("camera controller");
        const std::string k_uid_attribute("uid");
        const std::string k_walk_speed_attribute("walk speed");
        const std::string k_move_speed_attribute("move speed");
        const std::string k_run_speed_attribute("run speed");
    }

    namespace MeshRendererJSONConstants
    {
        const std::string k_parent_node("mesh renderer");
        const std::string k_uid_attribute("uid");
        const std::string k_mesh_attribute("mesh");
        const std::string k_shader_attribute("shader");
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_use_frustum_culling_attribute("use frustum culling");
    }

    namespace SkyboxFollowCameraJSONConstants
    {
        const std::string k_parent_node("skybox follow camera");
        const std::string k_uid_attribute("uid");
        const std::string k_camera_uid_attribute("camera uid");
    }

    namespace TestMovementJSONConstants
    {
        const std::string k_parent_node("test movement");
        const std::string k_uid_attribute("uid");
    }

    namespace TestMRotationJSONConstants
    {
        const std::string k_parent_node("test rotation");
        const std::string k_uid_attribute("uid");
    }

    namespace MeshJSONConstants
    {
        const std::string k_parent_node("mesh");
        const std::string k_path_to_file_attribute("path to file");
    }

    namespace ShaderJSONConstants
    {
        const std::string k_parent_node("generic shader");
        const std::string k_vertex_shader_attribute("vertex shader");
        const std::string k_geometry_shader_attribute("geometry shader");
        const std::string k_fragment_shader_attribute("fragment shader");
    }

    namespace FragmentNormalShaderJSONConstants
    {
        const std::string k_parent_node("fragment normal shader");
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_object_transform_uid_attribute("object transform uid");
    }

    namespace TextureShaderJSONConstants
    {
        const std::string k_parent_node("texture shader");
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_object_transform_uid_attribute("object transform uid");
        const std::string k_texture_path_attribute("texture path");
    }

    namespace TextureAndLightingShaderJSONConstants
    {
        const std::string k_parent_node("texture and lighting shader");
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_object_transform_uid_attribute("object transform uid");
        const std::string k_texture_path_attribute("texture path");
        const std::string k_light_position_attribute("light position");
    }
}

#endif // MG3TR_SRC_CONSTANTS_JSONCONSTANTS_HPP_INCLUDED
