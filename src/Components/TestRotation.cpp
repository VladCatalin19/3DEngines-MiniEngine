#include "TestRotation.hpp"

#include <Constants/JSONConstants.hpp>
#include <Math/Math.hxx>
#include <Math/Vector3.hpp>
#include <Math/Quaternion.hpp>
#include <Scripting/Transform.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

namespace MG3TR
{
    void TestRotation::FrameUpdate(float delta_time) try
    {
        auto transform = GetTransform().lock();

        auto rotation = transform->GetWorldRotation();
        auto additional_rotation = Quaternion(Vector3(0.0F, delta_time, 0.0F));

        transform->SetWorldRotation(rotation * additional_rotation);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json TestRotation::Serialize() const try
    {
        namespace Constants = TestMRotationJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TestRotation::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = TestMRotationJSONConstants;

        SetUID(json.at(Constants::k_parent_node).at(Constants::k_uid_attribute));
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void TestRotation::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
}
