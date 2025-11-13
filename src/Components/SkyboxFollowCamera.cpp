#include "SkyboxFollowCamera.hpp"

#include <Constants/JSONConstants.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

namespace MG3TR
{
    SkyboxFollowCamera::SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform)
        : Component(game_object, transform)
    {

    }
    
    SkyboxFollowCamera::SkyboxFollowCamera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                                           const std::weak_ptr<Transform> &camera)
        : Component(game_object, transform),
          m_camera(camera)
    {
        if (camera.lock() != nullptr)
        {
            m_camera_uid = camera.lock()->GetUID();
        }
    }
    
    void SkyboxFollowCamera::FrameUpdate([[maybe_unused]] float delta_time)
    {
        const auto camera_world_position = m_camera.lock()->GetWorldPosition();
        GetTransform().lock()->SetWorldPosition(camera_world_position);
    }
    
    nlohmann::json SkyboxFollowCamera::Serialize() const
    {
        namespace Constants = SkyboxFollowCameraJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        json[Constants::k_parent_node][Constants::k_camera_uid_attribute] = m_camera.lock()->GetUID();
        return json;
    }
    
    void SkyboxFollowCamera::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = SkyboxFollowCameraJSONConstants;

        nlohmann::json script_json = json.at(Constants::k_parent_node);

        SetUID(script_json.at(Constants::k_uid_attribute));
        m_camera_uid = script_json.at(Constants::k_camera_uid_attribute);
    }
    
    void SkyboxFollowCamera::LateBindAfterDeserialization(Scene &scene)
    {
        auto found_camera = scene.FindTransformWithUID(m_camera_uid);

        if (found_camera == nullptr)
        {
            throw ExceptionWithStacktrace("Could not find camera transform with UID " + std::to_string(m_camera_uid)
                                          + " for SkyboxFollowCamera script");
        }
        m_camera = found_camera;
    }
}
