#ifndef MG3TR_SRC_COMPONENTS_TESTMOVEMENT_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_TESTMOVEMENT_HPP_INCLUDED

#include "Component.hpp"

#include <Constants/MathConstants.hpp>
#include <Math/Vector3.hpp>

namespace MG3TR
{
    class TestMovement : public Component
    {
    private:
        Vector3 m_initial_local_position;
        float m_total_time;

    public:
        TestMovement(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
            : Component(game_object, transform),
              m_initial_local_position(Vector3Constants::k_zero),
              m_total_time(0.0F)
        {}
        virtual ~TestMovement() noexcept = default;

        TestMovement(const TestMovement &) = delete;
        TestMovement& operator=(const TestMovement &) = delete;

        TestMovement(TestMovement &&) noexcept = default;
        TestMovement& operator=(TestMovement &&) noexcept = default;

        virtual void Initialize() override;
        virtual void FrameUpdate(float delta_time) override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_TESTMOVEMENT_HPP_INCLUDED
