#ifndef MG3TR_SRC_SOMPONENTS_SKYBOXFOLLOWPCAMERA_HPP_INCLUDED
#define MG3TR_SRC_SOMPONENTS_SKYBOXFOLLOWPCAMERA_HPP_INCLUDED

#include "Component.hpp"

#include <memory>               // std::weak_ptr

namespace MG3TR
{
    class SkyboxFollowCamera : public Component
    {
    private:
        std::weak_ptr<Transform> m_camera;
        TUID m_camera_uid;

    public:
        SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
            : Component(game_object, transform)
        {}

        SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                           const std::weak_ptr<Transform> &camera) noexcept;
        virtual ~SkyboxFollowCamera() noexcept = default;

        SkyboxFollowCamera(const SkyboxFollowCamera &) = delete;
        SkyboxFollowCamera& operator=(const SkyboxFollowCamera &) = delete;

        SkyboxFollowCamera(SkyboxFollowCamera &&) noexcept = default;
        SkyboxFollowCamera& operator=(SkyboxFollowCamera &&) noexcept = default;

        virtual void FrameUpdate(float delta_time) override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_SOMPONENTS_SKYBOXFOLLOWPCAMERA_HPP_INCLUDED
