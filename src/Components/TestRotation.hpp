#ifndef MG3TR_SRC_COMPONENTS_TESTROTATION_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_TESTROTATION_HPP_INCLUDED

#include "Component.hpp"

namespace MG3TR
{
    class TestRotation : public Component
    {
    public:
        TestRotation(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform);
        virtual ~TestRotation() = default;

        TestRotation(const TestRotation &) = delete;
        TestRotation(TestRotation &&) = default;
        
        TestRotation& operator=(const TestRotation &) = delete;
        TestRotation& operator=(TestRotation &&) = default;

        virtual void FrameUpdate(const float delta_time) override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_TESTROTATION_HPP_INCLUDED
