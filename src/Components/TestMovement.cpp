#include "TestMovement.hpp"

#include <Constants/JSONConstants.hpp>
#include <Math/Math.hxx>
#include <Scripting/Transform.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

namespace MG3TR
{
    void TestMovement::Initialize() try
    {
        m_initial_local_position = GetTransform().lock()->GetLocalPosition();
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TestMovement::FrameUpdate(float delta_time) try
    {
        m_total_time += delta_time;
        float delta_movement = Math::Sin(m_total_time);
        GetTransform().lock()->SetLocalPosition(m_initial_local_position + Vector3(delta_movement * 0.4F, delta_movement, 0.0F));
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json TestMovement::Serialize() const try
    {
        namespace Constants = TestMovementJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TestMovement::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = TestMovementJSONConstants;

        SetUID(json.at(Constants::k_parent_node).at(Constants::k_uid_attribute));
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TestMovement::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
}
