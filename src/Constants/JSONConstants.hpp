#ifndef MG3TR_SRC_CONSTANTS_JSONCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_JSONCONSTANTS_HPP_INCLUDED

namespace MG3TR
{
    namespace TransformJSONConstants
    {
        constexpr char k_parent_node[] = "transform";
        constexpr char k_uid_attribute[] = "uid";
        constexpr char k_local_position_attribute[] = "local position";
        constexpr char k_local_rotation_attribute[] = "local rotation";
        constexpr char k_local_scale_attribute[] = "local scale";
        constexpr char k_children_attribute[] = "children";
        constexpr char k_game_object_attribute[] = "game object";
    }

    namespace GameObjectJSONConstants
    {
        constexpr char k_parent_node[] = "game object";
        constexpr char k_uid_attribute[] = "uid";
        constexpr char k_name_attribute[] = "name";
        constexpr char k_components_attribute[] = "components";
    }

    namespace CameraJSONConstants
    {
        constexpr char k_parent_node[] = "camera";
        constexpr char k_uid_attribute[] = "uid";
        constexpr char k_camera_mode_attribute[] = "camera mode";
        constexpr char k_fov_attribute[] = "fov";
        constexpr char k_aspect_ratio_attribute[] = "aspect ratio";
        constexpr char k_xmin_attribute[] = "xmin";
        constexpr char k_xmax_attribute[] = "xmax";
        constexpr char k_ymin_attribute[] = "ymin";
        constexpr char k_ymax_attribute[] = "ymax";
        constexpr char k_znear_attribute[] = "znear";
        constexpr char k_zfar_attribute[] = "zfar";
    }

    namespace CameraControllerJSONConstants
    {
        constexpr char k_parent_node[] = "camera controller";
        constexpr char k_uid_attribute[] = "uid";
        constexpr char k_walk_speed_attribute[] = "walk speed";
        constexpr char k_move_speed_attribute[] = "move speed";
        constexpr char k_run_speed_attribute[] = "run speed";
    }

    namespace MeshRendererJSONConstants
    {
        constexpr char k_parent_node[] = "mesh renderer";
        constexpr char k_uid_attribute[] = "uid";
        constexpr char k_mesh_attribute[] = "mesh";
        constexpr char k_shader_attribute[] = "shader";
        constexpr char k_camera_uid_attribute[] = "camera uid";
        constexpr char k_use_frustum_culling_attribute[] = "use frustum culling";
    }

    namespace SkyboxFollowCameraJSONConstants
    {
        constexpr char k_parent_node[] = "skybox follow camera";
        constexpr char k_uid_attribute[] = "uid";
        constexpr char k_camera_uid_attribute[] = "camera uid";
    }

    namespace TestMovementJSONConstants
    {
        constexpr char k_parent_node[] = "test movement";
        constexpr char k_uid_attribute[] = "uid";
    }

    namespace TestMRotationJSONConstants
    {
        constexpr char k_parent_node[] = "test rotation";
        constexpr char k_uid_attribute[] = "uid";
    }

    namespace MeshJSONConstants
    {
        constexpr char k_parent_node[] = "mesh";
        constexpr char k_path_to_file_attribute[] = "path to file";
    }

    namespace ShaderJSONConstants
    {
        constexpr char k_parent_node[] = "generic shader";
        constexpr char k_vertex_shader_attribute[] = "vertex shader";
        constexpr char k_geometry_shader_attribute[] = "geometry shader";
        constexpr char k_fragment_shader_attribute[] = "fragment shader";
    }

    namespace FragmentNormalShaderJSONConstants
    {
        constexpr char k_parent_node[] = "fragment normal shader";
        constexpr char k_camera_uid_attribute[] = "camera uid";
        constexpr char k_object_transform_uid_attribute[] = "object transform uid";
    }

    namespace TextureShaderJSONConstants
    {
        constexpr char k_parent_node[] = "texture shader";
        constexpr char k_camera_uid_attribute[] = "camera uid";
        constexpr char k_object_transform_uid_attribute[] = "object transform uid";
        constexpr char k_texture_path_attribute[] = "texture path";
    }

    namespace TextureAndLightingShaderJSONConstants
    {
        constexpr char k_parent_node[] = "texture and lighting shader";
        constexpr char k_camera_uid_attribute[] = "camera uid";
        constexpr char k_object_transform_uid_attribute[] = "object transform uid";
        constexpr char k_texture_path_attribute[] = "texture path";
        constexpr char k_light_position_attribute[] = "light position";
    }
}

#endif // MG3TR_SRC_CONSTANTS_JSONCONSTANTS_HPP_INCLUDED
