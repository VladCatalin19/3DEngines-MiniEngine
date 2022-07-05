#include "CameraController.hpp"

#include <Components/Component.hpp>
#include <Constants/JSONConstants.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Math.hxx>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

#include <iostream>

namespace MG3TR
{
    void CameraController::Initialize() 
    {
        Vector3 euler_angles = GetTransform().lock()->GetWorldRotation().EulerAngles();
        m_pitch = euler_angles.x();
        m_yaw = euler_angles.y();

        m_current_mouse_position = m_current_mouse_position = { 0.0F, 0.0F };
    }
    
    void CameraController::ParseInput(const Input &input) 
    {
        m_forward_movement = m_side_movement = m_vertical_movement = 0.0F;

        if (input.IsKeyHold(Key::S)) { m_forward_movement -= 1.0F; }
        if (input.IsKeyHold(Key::W)) { m_forward_movement += 1.0F; }

        if (input.IsKeyHold(Key::A)) { m_side_movement -= 1.0F; }
        if (input.IsKeyHold(Key::D)) { m_side_movement += 1.0F; }

        if (input.IsKeyHold(Key::Q)) { m_vertical_movement -= 1.0F; }
        if (input.IsKeyHold(Key::E)) { m_vertical_movement += 1.0F; }

        m_is_walking = input.IsKeyHold(Key::LeftAlt);
        m_is_running = input.IsKeyHold(Key::LeftShift);

        m_was_rotating_previous_frame = m_is_rotating_in_current_frame;
        m_is_rotating_in_current_frame = input.IsMouseButtonHold(MouseButton::Right);

        m_previous_mouse_position = m_current_mouse_position;
        m_current_mouse_position = input.GetMousePosition();
    }
    
    void CameraController::FrameUpdate(float delta_time) 
    {
        UpdateMovement(delta_time);
        UpdateRotation(delta_time);
    }
    
    nlohmann::json CameraController::Serialize() const 
    {
        namespace Constants = CameraControllerJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        json[Constants::k_parent_node][Constants::k_walk_speed_attribute] = m_walk_speed;
        json[Constants::k_parent_node][Constants::k_move_speed_attribute] = m_move_speed;
        json[Constants::k_parent_node][Constants::k_run_speed_attribute] = m_run_speed;

        return json;
    }
    
    void CameraController::Deserialize(const nlohmann::json &json) 
    {
        namespace Constants = CameraControllerJSONConstants;

        nlohmann::json controller_json = json.at(Constants::k_parent_node);

        SetUID(controller_json.at(Constants::k_uid_attribute));
        m_walk_speed = controller_json.at(Constants::k_walk_speed_attribute);
        m_move_speed = controller_json.at(Constants::k_move_speed_attribute);
        m_run_speed = controller_json.at(Constants::k_run_speed_attribute);
    }
    
    void CameraController::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
    
    void CameraController::UpdateMovement(float delta_time) 
    {
        const auto &transform = GetTransform().lock();

        Vector3 move_direction = transform->GetForwards() * m_forward_movement
                                 + transform->GetRight() * m_side_movement
                                 + transform->GetUp() * m_vertical_movement;
        move_direction.Normalize();

        float speed = m_move_speed;
        if (m_is_walking)
        {
            speed = m_walk_speed;
        }
        if (m_is_running)
        {
            speed = m_run_speed;
        }

        Vector3 world_position = transform->GetWorldPosition();
        Vector3 new_world_position = world_position + move_direction * speed * delta_time;
        transform->SetWorldPosition(new_world_position);
    }
    
    void CameraController::UpdateRotation([[maybe_unused]] float delta_time) 
    {
        if (!m_is_rotating_in_current_frame)
        {
            return;
        }

        Vector2 mouse_delta_movement = m_current_mouse_position - m_previous_mouse_position;

        m_yaw -= mouse_delta_movement.x() * 0.2F;
        m_pitch += mouse_delta_movement.y() * 0.2F;

        m_pitch = Math::Clamp(m_pitch, -90.0F, 90.0F);
        Quaternion local_rotation( { Math::DegreesToRadians(m_pitch), Math::DegreesToRadians(m_yaw), 0.0F } );

        GetTransform().lock()->SetWorldRotation(local_rotation);
    }
}
