#include "Camera.hpp"

#include <Constants/JSONConstants.hpp>
#include <Scripting/Transform.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

namespace MG3TR
{
    Camera::Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform)
        : Component(game_object, transform)
    {

    }

    Camera::Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                   const float fov, const float aspect_ratio, const float znear, const float zfar)
        : Component(game_object, transform),
            m_camera_mode(CameraMode::Perspective),
            m_fov(fov),
            m_aspect_ratio(aspect_ratio),
            m_znear(znear),
            m_zfar(zfar)
    {

    }

    Camera::Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
                   const float xmin, const float xmax, const float ymin, const float ymax, const float znear, const float zfar)
        : Component(game_object, transform),
            m_camera_mode(CameraMode::Orthographic),
            m_xmin(xmin),
            m_xmax(xmax),
            m_ymin(ymin),
            m_ymax(ymax),
            m_znear(znear),
            m_zfar(zfar)
    {

    }

    Matrix4x4 Camera::GetViewMatrix() const
    {
        const auto &transform = GetTransform().lock();

        Vector3 eye = transform->GetWorldPosition();
        Vector3 center = eye + transform->GetForwards();
        Vector3 up = transform->GetUp();

        return Matrix4x4::LookAt(eye, center, up);
    }
    
    Matrix4x4 Camera::GetProjectionMatrix() const
    {
        Matrix4x4 matrix;

        switch (m_camera_mode)
        {
            case CameraMode::Perspective:
            {
                matrix = Matrix4x4::Perspective(m_fov, m_aspect_ratio, m_znear, m_zfar);
                break;
            }
            case CameraMode::Orthographic:
            {
                matrix = Matrix4x4::Orthographic(m_xmin, m_xmax, m_ymin, m_ymax, m_znear, m_zfar);
                break;
            }
            default:
            {
                throw ExceptionWithStacktrace("Invalid camera type.");
            }
        }

        return matrix;
    }

    CameraMode Camera::GetCameraMode() const
    {
        return m_camera_mode;
    }

    float Camera::GetFov() const
    {
        return m_fov;
    }

    float Camera::GetAspectRatio() const
    {
        return m_aspect_ratio;
    }

    float Camera::GetXmin() const
    {
        return m_xmin;
    }

    float Camera::GetXmax() const
    {
        return m_xmax;
    }

    float Camera::GetYmin() const
    {
        return m_ymin;
    }

    float Camera::GetYmax() const
    {
        return m_ymax;
    }

    float Camera::GetZnear() const
    {
        return m_znear;
    }

    float Camera::GetZfar() const
    {
        return m_zfar;
    }
    
    nlohmann::json Camera::Serialize() const
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
    
    void Camera::Deserialize(const nlohmann::json &json)
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
    
    void Camera::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
}
