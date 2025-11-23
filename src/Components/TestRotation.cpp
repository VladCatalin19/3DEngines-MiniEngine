#include "TestRotation.hpp"

#include <Constants/ComponentConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Math/Math.hxx>
#include <Math/Vector3.hpp>
#include <Math/Quaternion.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>

namespace MG3TR
{
     TestRotation::TestRotation(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform)
        : Component(game_object, transform)
    {

    }
    
    void TestRotation::FrameUpdate(const float delta_time)
    {
        auto transform = GetTransform().lock();

        const auto rotation = transform->GetWorldRotation();
        const auto additional_rotation = Quaternion(Vector3(0.0F, delta_time, 0.0F));
        const auto world_rotation = rotation * additional_rotation;

        transform->SetWorldRotation(world_rotation);
    }

    void TestRotation::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = TestRotationSerialisationConstants;

        const TUID uid = GetUID();
        const ComponentType type = ComponentConstants::k_type_to_component.at(typeid(*this));

        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute, uid);
        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ComponentSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);
    }

    void TestRotation::Deserialise(IDeserialiser &deserialiser)
    {
        const TUID uid = deserialiser.DeserialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute);
        SetUID(uid);
    }
}
