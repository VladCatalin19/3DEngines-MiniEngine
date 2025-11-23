#ifndef MG3TR_SRC_COMPONENTS_TESTMOVEMENT_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_TESTMOVEMENT_HPP_INCLUDED

#include "Component.hpp"

#include <Math/Vector3.hpp>

namespace MG3TR
{
    class TestMovement : public Component
    {
    private:
        Vector3 m_initial_local_position;
        float m_total_time;

        static constexpr float k_movement_sensitivity = 0.4F;

    public:
        TestMovement(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform);
        virtual ~TestMovement() = default;

        TestMovement(const TestMovement &) = delete;
        TestMovement(TestMovement &&) = default;
        
        TestMovement& operator=(const TestMovement &) = delete;
        TestMovement& operator=(TestMovement &&) = default;

        virtual void Initialize() override;
        virtual void FrameUpdate(const float delta_time) override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_TESTMOVEMENT_HPP_INCLUDED
