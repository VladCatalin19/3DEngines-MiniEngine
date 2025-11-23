#ifndef MG3TR_SRC_COMPONENTS_CAMERACONTROLLER_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_CAMERACONTROLLER_HPP_INCLUDED

#include "Component.hpp"

#include <Math/Vector2.hpp>

namespace MG3TR
{
    class CameraController : public Component
    {
    private:
        float m_pitch;
        float m_yaw;

        int m_forward_movement;
        int m_side_movement;
        int m_vertical_movement;

        bool m_was_rotating_previous_frame;
        bool m_is_rotating_in_current_frame;

        Vector2 m_previous_mouse_position;
        Vector2 m_current_mouse_position;

        float m_walk_speed;
        float m_move_speed;
        float m_run_speed;

        bool m_is_walking;
        bool m_is_running;

        static constexpr float k_yaw_sensitivity = 0.2F;
        static constexpr float k_pitch_sensitivity = 0.2F;

    public:
        CameraController(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform);

        CameraController(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                         const float walk_speed, const float move_speed, const float run_speed);
        virtual ~CameraController() = default;

        CameraController(const CameraController &) = delete;
        CameraController(CameraController &&) = default;
        
        CameraController& operator=(const CameraController &) = delete;
        CameraController& operator=(CameraController &&) = default;

        virtual void Initialize() override;
        virtual void ParseInput(const Input &input) override;
        virtual void FrameUpdate(const float delta_time) override;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;

    private:
        void UpdateMovement(const float delta_time);
        void UpdateRotation(const float delta_time);
    };
}

#endif // MG3TR_SRC_COMPONENTS_CAMERACONTROLLER_HPP_INCLUDED
