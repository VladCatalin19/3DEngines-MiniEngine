#include "TestRotation.hpp"

#include <Constants/JSONConstants.hpp>
#include <Math/Math.hxx>
#include <Math/Vector3.hpp>
#include <Math/Quaternion.hpp>
#include <Scripting/Transform.hpp>

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
    
    nlohmann::json TestRotation::Serialize() const
    {
        namespace Constants = TestMRotationJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        return json;
    }
    
    void TestRotation::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = TestMRotationJSONConstants;

        SetUID(json.at(Constants::k_parent_node).at(Constants::k_uid_attribute));
    }
    
    void TestRotation::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
}
