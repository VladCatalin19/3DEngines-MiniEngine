#include "MeshRenderer.hpp"

#include <Components/Camera.hpp>
#include <Constants/ComponentConstants.hpp>
#include <Constants/ShaderConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Constants/MathConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/ShaderType.hpp>
#include <Math/Math.hxx>
#include <Math/Frustum.hpp>
#include <Math/Matrix4x4.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/TryCathRethrowStacktrace.hpp>

static MG3TR::Sphere CalculateMeshBoundingSphereRadiusInWorldSpace(const MG3TR::Mesh &mesh)
{
    MG3TR::Vector3 min_coordinates;
    MG3TR::Vector3 max_coordinates;

    for (const auto &mesh : mesh.GetSubmeshes())
    {
        for (auto vertex : mesh.GetVertices())
        {
            min_coordinates = MG3TR::Vector3::Min(min_coordinates, vertex);
            max_coordinates = MG3TR::Vector3::Max(max_coordinates, vertex);
        }
    }

    const MG3TR::Vector3 center = MG3TR::Vector3::Lerp(max_coordinates, min_coordinates, 0.5F);
    const float radius = (max_coordinates - min_coordinates).Magnitude() * 0.5F;
    const MG3TR::Sphere sphere(center, radius);

    return sphere;
}

static bool IsObjectInsideCameraFrustum(const MG3TR::Camera &camera, const MG3TR::Transform &object_transform,
                                        const MG3TR::Sphere &bounding_sphere)
{
    const MG3TR::Frustum camera_frustum(camera);
    const MG3TR::Vector3 object_scale = object_transform.GetWorldScale();
    const float max_scale = MG3TR::Math::Max(object_scale.x(), object_scale.y(), object_scale.z());

    const MG3TR::Vector3 object_center = object_transform.TransformPointToWorldSpace(bounding_sphere.GetCenter());
    const float object_radius = bounding_sphere.GetRadius() * max_scale;

    const MG3TR::Sphere world_space_sphere(object_center, object_radius);
    const bool result = world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetLeftFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetRightFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetFarFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetNearFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetTopFace())
           && world_space_sphere.IsOnOrInFrontOfPlane(camera_frustum.GetBottomFace());

    return result;
}

namespace MG3TR
{
    MeshRenderer::MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform)
        : Component(game_object, transform)
    {

    }
    
    MeshRenderer::MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                               const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                               const std::weak_ptr<Camera> &camera, const bool use_frustum_culling)
        : Component(game_object, transform),
          m_mesh_bounding_sphere({}, 0.0F)
    {
        Construct(game_object, transform, mesh, shader, camera, use_frustum_culling);
    }

    Sphere MeshRenderer::GetBoundingSphere() const
    {
        return m_mesh_bounding_sphere;
    }

    void MeshRenderer::FrameEnd([[maybe_unused]] float delta_time)
    {
        if (m_use_frustum_culling)
        {
            const bool is_visible_by_camera = IsObjectInsideCameraFrustum(*m_camera.lock(), *GetTransform().lock(), m_mesh_bounding_sphere);

            if (is_visible_by_camera)
            {
                return;
            }
        }

        m_shader->Use();
        m_shader->SetUniforms();
        m_shader->BindAdditionals();

        for (const auto &submesh : m_mesh->GetSubmeshes())
        {
            auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

            api.DrawSubMesh(submesh);
        }
    }

    void MeshRenderer::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = MeshRendererSerialisationConstants;

        const TUID uid = GetUID();
        const TUID camera_uid = m_camera.lock()->GetUID();
        const ComponentType type = ComponentConstants::k_type_to_component.at(typeid(*this));

        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute, uid);
        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ComponentSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);

        serialiser.SerialiseUnsigned(Constants::k_camera_uid_attribute, camera_uid);
        serialiser.SerialiseBool(Constants::k_use_frustum_culling_attribute, m_use_frustum_culling);

        serialiser.BeginSerialisingChild(Constants::k_mesh_attribute);
        m_mesh->Serialise(serialiser);
        serialiser.EndSerialisingLastChild();

        serialiser.BeginSerialisingChild(Constants::k_shader_attribute);
        m_shader->Serialise(serialiser);
        serialiser.EndSerialisingLastChild();
    }

    void MeshRenderer::Deserialise(IDeserialiser &deserialiser)
    {
        namespace Constants = MeshRendererSerialisationConstants;

        const TUID uid = deserialiser.DeserialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute);
        SetUID(uid);

        m_mesh = std::make_shared<Mesh>();

        deserialiser.BeginDeserialisingChild(Constants::k_mesh_attribute);
        m_mesh->Deserialise(deserialiser);
        deserialiser.EndDeserialisingLastChild();

        m_mesh_bounding_sphere = CalculateMeshBoundingSphereRadiusInWorldSpace(*m_mesh);
        m_camera_uid = deserialiser.DeserialiseUnsigned(Constants::k_camera_uid_attribute);
        m_use_frustum_culling = deserialiser.DeserialiseBool(Constants::k_use_frustum_culling_attribute);

        deserialiser.BeginDeserialisingChild(Constants::k_shader_attribute);

        const auto shader_type = static_cast<ShaderType>(deserialiser.DeserialiseUnsigned(ShaderSerialisationConstants::k_type_attribute));
        ShaderConstants::TShaderConstructor shader_constructor;
        TRY_CATCH_RETHROW_STACKTRACE(shader_constructor = ShaderConstants::k_shader_to_constructor.at(shader_type));

        m_shader = shader_constructor();

        m_shader->Deserialise(deserialiser);

        deserialiser.EndDeserialisingLastChild();
    }

    void MeshRenderer::LateBind(Scene &scene)
    {
        auto found_camera = scene.FindCameraWithUID(m_camera_uid);

        if (found_camera == nullptr)
        {
            throw ExceptionWithStacktrace("Could not find camera with UID " + std::to_string(m_camera_uid)
                                          + " for MeshRenderer script");
        }
        m_camera = found_camera;

        m_shader->LateBind(scene);
    }

    void MeshRenderer::Construct(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                                 const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                                 const std::weak_ptr<Camera> &camera, const bool use_frustum_culling)
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
}
