#ifndef MG3TR_SRC_COMPONENTS_TESTROTATION_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_TESTROTATION_HPP_INCLUDED

#include "Component.hpp"

#include <Math/Vector3.hpp>

namespace MG3TR
{
    class TestRotation : public Component
    {
    public:
        TestRotation(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
            : Component(game_object, transform)
        {}
        virtual ~TestRotation() noexcept = default;

        TestRotation(const TestRotation &) = delete;
        TestRotation& operator=(const TestRotation &) = delete;

        TestRotation(TestRotation &&) noexcept = default;
        TestRotation& operator=(TestRotation &&) noexcept = default;

        virtual void FrameUpdate(float delta_time) override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_TESTROTATION_HPP_INCLUDED
