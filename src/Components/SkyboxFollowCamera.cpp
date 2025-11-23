#include "SkyboxFollowCamera.hpp"

#include <Constants/ComponentConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
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

    void SkyboxFollowCamera::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = SkyboxFollowCameraSerialisationConstants;

        const TUID uid = GetUID();
        const TUID camera_uid = m_camera.lock()->GetUID();
        const ComponentType type = ComponentConstants::k_type_to_component.at(typeid(*this));

        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute, uid);
        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ComponentSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);

        serialiser.SerialiseUnsigned(Constants::k_camera_uid_attribute, camera_uid);
    }

    void SkyboxFollowCamera::Deserialise(IDeserialiser &deserialiser)
    {
        namespace Constants = SkyboxFollowCameraSerialisationConstants;
        
        const TUID uid = deserialiser.DeserialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute);
        SetUID(uid);

        m_camera_uid = deserialiser.DeserialiseUnsigned(Constants::k_camera_uid_attribute);
    }

    void SkyboxFollowCamera::LateBind(Scene &scene)
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
