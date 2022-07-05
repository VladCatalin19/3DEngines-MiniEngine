#include "MeshRenderer.hpp"

#include <Components/Camera.hpp>
#include <Constants/JSONConstants.hpp>
#include <Constants/MathConstants.hpp>
#include <Graphics/Shaders/FragmentNormalShader.hpp>
#include <Graphics/Shaders/TextureAndLightingShader.hpp>
#include <Graphics/Shaders/TextureShader.hpp>
#include <Math/Math.hxx>
#include <Math/Frustum.hpp>
#include <Math/Matrix4x4.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

#include <Utils/PrintGLErrors.hpp>              // PRINT_GL_ERRORS_IF_ANY
#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <memory>           // std::make_shared

static MG3TR::Vector3 MinComponentWise(const MG3TR::Vector3 &v1, const MG3TR::Vector3 &v2) noexcept
{
    return
    {
        MG3TR::Math::Min(v1.x(), v2.x()),
        MG3TR::Math::Min(v1.y(), v2.y()),
        MG3TR::Math::Min(v1.z(), v2.z())
    };
}

static MG3TR::Vector3 MaxComponentWise(const MG3TR::Vector3 &v1, const MG3TR::Vector3 &v2) noexcept
{
    return
    {
        MG3TR::Math::Max(v1.x(), v2.x()),
        MG3TR::Math::Max(v1.y(), v2.y()),
        MG3TR::Math::Max(v1.z(), v2.z())
    };
}

static float MaxComponent(const MG3TR::Vector3 &v) noexcept
{
    return MG3TR::Math::Max(v.x(), v.y(), v.z());
}

static MG3TR::Sphere CalculateMeshBoundingSphereRadiusInWorldSpace(const MG3TR::Mesh &mesh) try
{
    MG3TR::Vector3 min_coordinates;
    MG3TR::Vector3 max_coordinates;

    for (const auto &mesh : mesh.GetSubmeshes())
    {
        for (const auto &vertex : mesh.GetVertices())
        {
            min_coordinates = MinComponentWise(min_coordinates, vertex);
            max_coordinates = MaxComponentWise(max_coordinates, vertex);
        }
    }

    MG3TR::Vector3 center = MG3TR::Vector3::Lerp(max_coordinates, min_coordinates, 0.5F);
    float radius = (max_coordinates - min_coordinates).Magnitude() * 0.5F;
    return { center, radius };
}
CATCH_RETHROW_EXCEPTIONS

static bool IsObjectInsideCameraFrustum(const MG3TR::Camera &camera, const MG3TR::Transform &object_transform,
                                        const MG3TR::Sphere &bounding_sphere)
{
    MG3TR::Frustum camera_frustum(camera);
    MG3TR::Vector3 object_scale = object_transform.GetWorldScale();
    float max_scale = MaxComponent(object_scale);

    MG3TR::Vector3 object_center = object_transform.TransformPointToWorldSpace(bounding_sphere.GetCenter());
    float object_radius = bounding_sphere.GetRadius() * max_scale;

    MG3TR::Sphere world_space_sphere(object_center, object_radius);

    return world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetLeftFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetRightFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetFarFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetNearFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetTopFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetBottomFace());
}

namespace MG3TR
{
    MeshRenderer::MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                               const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                               const std::weak_ptr<Camera> &camera, bool use_frustum_culling) try
        : Component(game_object, transform),
          m_mesh_bounding_sphere({}, 0.0F)
    {
        Construct(game_object, transform, mesh, shader, camera, use_frustum_culling);
    }
    CATCH_RETHROW_EXCEPTIONS

    void MeshRenderer::FrameEnd([[maybe_unused]] float delta_time) try
    {
        if (m_use_frustum_culling && !IsObjectInsideCameraFrustum(*m_camera.lock(), *GetTransform().lock(), m_mesh_bounding_sphere))
        {
            return;
        }

        m_shader->Use();
        m_shader->SetUniforms();
        m_shader->BindAdditionals();

        for (const auto &submesh : m_mesh->GetSubmeshes())
        {
            glBindVertexArray(submesh.GetVAO());
            PRINT_GL_ERRORS_IF_ANY();

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(submesh.GetIndices().size()), GL_UNSIGNED_INT, nullptr);
            PRINT_GL_ERRORS_IF_ANY();
        }
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json MeshRenderer::Serialize() const try
    {
        namespace Constants = MeshRendererJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        json[Constants::k_parent_node][Constants::k_mesh_attribute] = m_mesh->Serialize()["mesh"];
        json[Constants::k_parent_node][Constants::k_shader_attribute] = m_shader->Serialize();
        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        json[Constants::k_parent_node][Constants::k_use_frustum_culling_attribute] = m_use_frustum_culling;
        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void MeshRenderer::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = MeshRendererJSONConstants;

        nlohmann::json renderer_json = json.at(Constants::k_parent_node);

        SetUID(renderer_json.at(Constants::k_uid_attribute));

        m_mesh = std::make_shared<Mesh>();
        m_mesh->Deserialize(renderer_json);
        m_mesh_bounding_sphere = CalculateMeshBoundingSphereRadiusInWorldSpace(*m_mesh);

        nlohmann::json shader_json = renderer_json.at(Constants::k_shader_attribute);

        if (shader_json.contains(ShaderJSONConstants::k_parent_node))
        {
            m_shader = std::make_shared<Shader>();
        }
        else if (shader_json.contains(TextureShaderJSONConstants::k_parent_node))
        {
            m_shader = std::make_shared<TextureShader>();
        }
        else if (shader_json.contains(TextureAndLightingShaderJSONConstants::k_parent_node))
        {
            m_shader = std::make_shared<TextureAndLightingShader>();
        }
        else if (shader_json.contains(FragmentNormalShaderJSONConstants::k_parent_node))
        {
            m_shader = std::make_shared<FragmentNormalShader>();
        }
        else
        {
            throw std::logic_error("Could not determine what shader was used!" + shader_json.dump());
        }
        m_shader->Deserialize(shader_json);

        m_camera_uid = renderer_json.at(Constants::k_camera_uid_attribute);
        m_use_frustum_culling = renderer_json.at(Constants::k_use_frustum_culling_attribute);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void MeshRenderer::LateBindAfterDeserialization(Scene &scene) 
    {
        auto found_camera = scene.FindCameraWithUID(m_camera_uid);

        if (found_camera == nullptr)
        {
            throw std::logic_error("Could not find camera with UID " + std::to_string(m_camera_uid)
                                   + " for MeshRenderer script");
        }
        m_camera = found_camera;

        m_mesh->LateBindAfterDeserialization(scene);
        m_shader->LateBindAfterDeserialization(scene);
    }

    void MeshRenderer::Construct(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                                 const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                                 const std::weak_ptr<Camera> &camera, bool use_frustum_culling) try
    {
        SetGameObject(game_object);
        SetTransform(transform);
        m_mesh = mesh;
        m_shader = shader;
        m_camera = camera;
        m_use_frustum_culling = use_frustum_culling;

        if (camera.lock() != nullptr)
        {
            m_camera_uid = camera.lock()->GetUID();
        }

        if (mesh != nullptr)
        {
            m_mesh_bounding_sphere = CalculateMeshBoundingSphereRadiusInWorldSpace(*mesh);
        }
    }
    CATCH_RETHROW_EXCEPTIONS
}
