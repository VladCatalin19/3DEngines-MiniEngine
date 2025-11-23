#ifndef MG3TR_SRC_CONSTANTS_SERIALISATIONCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_SERIALISATIONCONSTANTS_HPP_INCLUDED

#include <string>

namespace MG3TR
{
    const std::size_t k_serialisation_indent = 4;

    namespace TransformSerialisationConstants
    {
        const std::string k_parent_node("transform");
        const std::string k_uid_attribute("uid");
        const std::string k_local_position_attribute("local position");
        const std::string k_local_rotation_attribute("local rotation");
        const std::string k_local_scale_attribute("local scale");
        const std::string k_children_attribute("children");
        const std::string k_game_object_attribute("game object");
    }

    namespace GameObjectSerialisationConstants
    {
        const std::string k_parent_node("game object");
        const std::string k_uid_attribute("uid");
        const std::string k_name_attribute("name");
        const std::string k_components_attribute("components");
    }

    namespace ComponentSerialisationConstants
    {
        const std::string k_parent_node("component");
        const std::string k_uid_attribute("uid");
        const std::string k_type_attribute("type");
        const std::string k_type_name_attribute("type name");
    }

    namespace CameraSerialisationConstants
    {
        const std::string k_type_name_value("camera");
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

    namespace CameraControllerSerialisationConstants
    {
        const std::string k_type_name_value("camera controller");
        const std::string k_walk_speed_attribute("walk speed");
        const std::string k_move_speed_attribute("move speed");
        const std::string k_run_speed_attribute("run speed");
    }

    namespace MeshRendererSerialisationConstants
    {
        const std::string k_type_name_value("mesh renderer");
        const std::string k_mesh_attribute("mesh");
        const std::string k_shader_attribute("shader");
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_use_frustum_culling_attribute("use frustum culling");
    }

    namespace SkyboxFollowCameraSerialisationConstants
    {
        const std::string k_type_name_value("skybox follow camera");
        const std::string k_camera_uid_attribute("camera uid");
    }

    namespace TestMovementSerialisationConstants
    {
        const std::string k_type_name_value("test movement");
    }

    namespace TestRotationSerialisationConstants
    {
        const std::string k_type_name_value("test rotation");
    }

    namespace MeshSerialisationConstants
    {
        const std::string k_parent_node("mesh");
        const std::string k_path_to_file_attribute("path to file");
    }

    namespace ShaderSerialisationConstants
    {
        const std::string k_vertex_shader_attribute("vertex shader");
        const std::string k_geometry_shader_attribute("geometry shader");
        const std::string k_fragment_shader_attribute("fragment shader");
        const std::string k_type_attribute("type");
        const std::string k_type_name_attribute("type name");
        const std::string k_type_name_value("generic shader");
    }

    namespace FragmentNormalShaderSerialisationConstants
    {
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_object_transform_uid_attribute("object transform uid");
        const std::string k_type_name_value("fragment normal shader");
    }

    namespace TextureShaderSerialisationConstants
    {
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_object_transform_uid_attribute("object transform uid");
        const std::string k_texture_path_attribute("texture path");
        const std::string k_type_name_value("texture shader");
    }

    namespace TextureAndLightingShaderSerialisationConstants
    {
        const std::string k_camera_uid_attribute("camera uid");
        const std::string k_object_transform_uid_attribute("object transform uid");
        const std::string k_texture_path_attribute("texture path");
        const std::string k_light_position_attribute("light position");
        const std::string k_type_name_value("texture and lighting shader");
    }
}

#endif // MG3TR_SRC_CONSTANTS_SERIALISATIONCONSTANTS_HPP_INCLUDED
