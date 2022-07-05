#include "SkyboxFollowCamera.hpp"

#include <Components/Component.hpp>
#include <Constants/JSONConstants.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

#include <iostream>

namespace MG3TR
{
    SkyboxFollowCamera::SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                                           const std::weak_ptr<Transform> &camera) noexcept
        : Component(game_object, transform),
          m_camera(camera)
    {
        if (camera.lock() != nullptr)
        {
            m_camera_uid = camera.lock()->GetUID();
        }
    }
    
    void SkyboxFollowCamera::FrameUpdate([[maybe_unused]] float delta_time) try
    {
        GetTransform().lock()->SetWorldPosition(m_camera.lock()->GetWorldPosition());
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json SkyboxFollowCamera::Serialize() const try
    {
        namespace Constants = SkyboxFollowCameraJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void SkyboxFollowCamera::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = SkyboxFollowCameraJSONConstants;

        nlohmann::json script_json = json.at(Constants::k_parent_node);

        SetUID(script_json.at(Constants::k_uid_attribute));
        m_camera_uid = script_json.at(Constants::k_camera_uid_attribute);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void SkyboxFollowCamera::LateBindAfterDeserialization(Scene &scene) try
    {
        auto found_camera = scene.FindTransformWithUID(m_camera_uid);

        if (found_camera == nullptr)
        {
            throw std::logic_error("Could not find camera transform with UID " + std::to_string(m_camera_uid)
                                   + " for SkyboxFollowCamera script");
        }
        m_camera = found_camera;
    }
    CATCH_RETHROW_EXCEPTIONS
}
