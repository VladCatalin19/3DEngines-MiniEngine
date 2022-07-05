#include "Camera.hpp"

#include <Constants/JSONConstants.hpp>
#include <Math/Matrix4x4.hpp>
#include <Scripting/Transform.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <nlohmann/json.hxx>

#include <stdexcept>                // std::logic_error

namespace MG3TR
{
    Matrix4x4 Camera::GetViewMatrix() const noexcept
    {
        const auto &transform = GetTransform().lock();

        Vector3 eye = transform->GetWorldPosition();
        Vector3 center = eye + transform->GetForwards();
        Vector3 up = transform->GetUp();

        return Matrix4x4::LookAt(eye, center, up);
    }
    
    Matrix4x4 Camera::GetProjectionMatrix() const try
    {
        switch (m_camera_mode)
        {
            case CameraMode::Perspective:
            {
                return Matrix4x4::Perspective(m_fov, m_aspect_ratio, m_znear, m_zfar);
            }
            break;
            case CameraMode::Orthographic:
            {
                return Matrix4x4::Orthographic(m_xmin, m_xmax, m_ymin, m_ymax, m_znear, m_zfar);
            }
            break;
        }
        throw std::logic_error("Invalid camera type.");
    }
    CATCH_RETHROW_EXCEPTIONS
    
    nlohmann::json Camera::Serialize() const try
    {
        namespace Constants = CameraJSONConstants;

        nlohmann::json json;

        json[Constants::k_parent_node][Constants::k_uid_attribute] = GetUID();
        json[Constants::k_parent_node][Constants::k_camera_mode_attribute] = static_cast<unsigned>(m_camera_mode);

        json[Constants::k_parent_node][Constants::k_fov_attribute] = m_fov;
        json[Constants::k_parent_node][Constants::k_aspect_ratio_attribute] = m_aspect_ratio;

        json[Constants::k_parent_node][Constants::k_xmin_attribute] = m_xmin;
        json[Constants::k_parent_node][Constants::k_xmax_attribute] = m_xmax;
        json[Constants::k_parent_node][Constants::k_ymin_attribute] = m_ymin;
        json[Constants::k_parent_node][Constants::k_ymax_attribute] = m_ymax;

        json[Constants::k_parent_node][Constants::k_znear_attribute] = m_znear;
        json[Constants::k_parent_node][Constants::k_zfar_attribute] = m_zfar;

        return json;
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Camera::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = CameraJSONConstants;

        nlohmann::json camera_json = json.at(Constants::k_parent_node);

        SetUID(camera_json.at(Constants::k_uid_attribute));
        m_camera_mode = camera_json.at(Constants::k_camera_mode_attribute);

        m_fov = camera_json.at(Constants::k_fov_attribute);
        m_aspect_ratio = camera_json.at(Constants::k_aspect_ratio_attribute);

        m_xmin = camera_json.at(Constants::k_xmin_attribute);
        m_xmax = camera_json.at(Constants::k_xmax_attribute);
        m_ymin = camera_json.at(Constants::k_ymin_attribute);
        m_ymax = camera_json.at(Constants::k_ymax_attribute);

        m_znear = camera_json.at(Constants::k_znear_attribute);
        m_zfar = camera_json.at(Constants::k_zfar_attribute);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Camera::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
}
