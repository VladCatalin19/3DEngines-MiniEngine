#ifndef MG3TR_SRC_COMPONENTS_MESHRENDERER_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_MESHRENDERER_HPP_INCLUDED

#include <Components/Component.hpp>
#include <Components/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Shader.hpp>
#include <Math/Sphere.hpp>

#include <memory>               // std::shared_ptr, std::weak_ptr

namespace MG3TR
{
    class MeshRenderer : public Component
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        std::shared_ptr<Shader> m_shader;
        std::weak_ptr<Camera> m_camera;
        Sphere m_mesh_bounding_sphere;
        bool m_use_frustum_culling;
        TUID m_camera_uid;

    public:
        MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
            : Component(game_object, transform)
        {}

        MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                     const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                     const std::weak_ptr<Camera> &camera, bool use_frustum_culling = true);
        virtual ~MeshRenderer() noexcept = default;

        MeshRenderer(const MeshRenderer &) = delete;
        MeshRenderer& operator=(const MeshRenderer &) = delete;

        MeshRenderer(MeshRenderer &&) noexcept = default;
        MeshRenderer& operator=(MeshRenderer &&) noexcept = default;

        Sphere GetBoundingSphere() const noexcept { return m_mesh_bounding_sphere; }

        virtual void FrameEnd(float) override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        void Construct(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                       const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                       const std::weak_ptr<Camera> &camera, bool use_frustum_culling);
    };
}

#endif // MG3TR_SRC_COMPONENTS_MESHRENDERER_HPP_INCLUDED
