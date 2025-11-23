#ifndef MG3TR_SRC_COMPONENTS_MESHRENDERER_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_MESHRENDERER_HPP_INCLUDED

#include <Components/Component.hpp>
#include <Math/Sphere.hpp>

#include <memory>

namespace MG3TR
{
    class Mesh;
    class Shader;
    class Camera;

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
        MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform);

        MeshRenderer(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                     const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                     const std::weak_ptr<Camera> &camera, const bool use_frustum_culling = true);
        virtual ~MeshRenderer() = default;

        MeshRenderer(const MeshRenderer &) = delete;
        MeshRenderer(MeshRenderer &&) = default;
        
        MeshRenderer& operator=(const MeshRenderer &) = delete;
        MeshRenderer& operator=(MeshRenderer &&) = default;

        Sphere GetBoundingSphere() const;

        virtual void FrameEnd([[maybe_unused]] const float delta_time) override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
        virtual void LateBind(Scene &scene) override;

    private:
        void Construct(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                       const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Shader> &shader,
                       const std::weak_ptr<Camera> &camera, const bool use_frustum_culling);
    };
}

#endif // MG3TR_SRC_COMPONENTS_MESHRENDERER_HPP_INCLUDED
