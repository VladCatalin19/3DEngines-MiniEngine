#include "TestMovement.hpp"

#include <Constants/ComponentConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Constants/MathConstants.hpp>
#include <Math/Math.hxx>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>

namespace MG3TR
{
    TestMovement::TestMovement(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform)
        : Component(game_object, transform),
          m_initial_local_position(Vector3Constants::k_zero),
          m_total_time(0.0F)
    {

    }
    
    void TestMovement::Initialize()
    {
        m_initial_local_position = GetTransform().lock()->GetLocalPosition();
    }
    
    void TestMovement::FrameUpdate(const float delta_time)
    {
        m_total_time += delta_time;

        const float delta_movement = Math::Sin(m_total_time);
        const Vector3 delta_position(delta_movement * k_movement_sensitivity, delta_movement, 0.0F);
        const Vector3 position = m_initial_local_position + delta_position;

        GetTransform().lock()->SetLocalPosition(position);
    }

    void TestMovement::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = TestMovementSerialisationConstants;

        const TUID uid = GetUID();
        const ComponentType type = ComponentConstants::k_type_to_component.at(typeid(*this));

        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute, uid);
        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ComponentSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);
    }

    void TestMovement::Deserialise(IDeserialiser &deserialiser)
    {
        const TUID uid = deserialiser.DeserialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute);
        SetUID(uid);
    }
}
