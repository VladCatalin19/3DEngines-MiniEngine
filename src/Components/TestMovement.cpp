#include "TestMovement.hpp"

#include <Constants/JSONConstants.hpp>
#include <Constants/MathConstants.hpp>
#include <Math/Math.hxx>
#include <Scripting/Transform.hpp>

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
    
    nlohmann::json TestMovement::Serialize() const
    {
        namespace Constants = TestMovementJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        return json;
    }
    
    void TestMovement::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = TestMovementJSONConstants;

        SetUID(json.at(Constants::k_parent_node).at(Constants::k_uid_attribute));
    }
    
    void TestMovement::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
}
