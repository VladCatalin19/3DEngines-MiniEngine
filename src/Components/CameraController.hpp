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

        float m_forward_movement;
        float m_side_movement;
        float m_vertical_movement;

        bool m_was_rotating_previous_frame;
        bool m_is_rotating_in_current_frame;

        Vector2 m_previous_mouse_position;
        Vector2 m_current_mouse_position;

        float m_walk_speed;
        float m_move_speed;
        float m_run_speed;

        bool m_is_walking;
        bool m_is_running;

    public:
        CameraController(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
            : Component(game_object, transform)
        {}

        CameraController(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                         float walk_speed, float move_speed, float run_speed) noexcept
            : Component(game_object, transform),
              m_walk_speed(walk_speed),
              m_move_speed(move_speed),
              m_run_speed(run_speed)
        {}
        virtual ~CameraController() noexcept = default;

        CameraController(const CameraController &) = delete;
        CameraController& operator=(const CameraController &) = delete;

        CameraController(CameraController &&) noexcept = default;
        CameraController& operator=(CameraController &&) noexcept = default;

        virtual void Initialize() override;
        virtual void ParseInput(const Input &input) override;
        virtual void FrameUpdate(float delta_time) override;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        void UpdateMovement(float delta_time);
        void UpdateRotation(float delta_time);
    };
}

#endif // MG3TR_SRC_COMPONENTS_CAMERACONTROLLER_HPP_INCLUDED
