#ifndef MG3TR_SRC_SOMPONENTS_SKYBOXFOLLOWPCAMERA_HPP_INCLUDED
#define MG3TR_SRC_SOMPONENTS_SKYBOXFOLLOWPCAMERA_HPP_INCLUDED

#include "Component.hpp"

#include <memory>

namespace MG3TR
{
    class SkyboxFollowCamera : public Component
    {
    private:
        std::weak_ptr<Transform> m_camera;
        TUID m_camera_uid;

    public:
        SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform);

        SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                           const std::weak_ptr<Transform> &camera);
        virtual ~SkyboxFollowCamera() = default;

        SkyboxFollowCamera(const SkyboxFollowCamera &) = delete;
        SkyboxFollowCamera(SkyboxFollowCamera &&) = default;
        
        SkyboxFollowCamera& operator=(const SkyboxFollowCamera &) = delete;
        SkyboxFollowCamera& operator=(SkyboxFollowCamera &&) = default;

        virtual void FrameUpdate(float delta_time) override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
        virtual void LateBind(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_SOMPONENTS_SKYBOXFOLLOWPCAMERA_HPP_INCLUDED
