#include "Camera.hpp"

#include <Constants/ComponentConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
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

    void Camera::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = CameraSerialisationConstants;

        const TUID uid = GetUID();
        const ComponentType type = ComponentConstants::k_type_to_component.at(typeid(*this));

        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute, uid);
        serialiser.SerialiseUnsigned(ComponentSerialisationConstants::k_type_attribute, static_cast<unsigned long long>(type));
        serialiser.SerialiseString(ComponentSerialisationConstants::k_type_name_attribute, Constants::k_type_name_value);

        serialiser.SerialiseUnsigned(Constants::k_camera_mode_attribute, static_cast<unsigned long long>(m_camera_mode));
        serialiser.SerialiseFloat(Constants::k_fov_attribute, m_fov);
        serialiser.SerialiseFloat(Constants::k_aspect_ratio_attribute, m_aspect_ratio);
        serialiser.SerialiseFloat(Constants::k_xmin_attribute, m_xmin);
        serialiser.SerialiseFloat(Constants::k_xmax_attribute, m_xmax);
        serialiser.SerialiseFloat(Constants::k_ymin_attribute, m_ymin);
        serialiser.SerialiseFloat(Constants::k_ymax_attribute, m_ymax);
        serialiser.SerialiseFloat(Constants::k_znear_attribute, m_znear);
        serialiser.SerialiseFloat(Constants::k_zfar_attribute, m_zfar);
    }

    void Camera::Deserialise(IDeserialiser &deserialiser)
    {
        namespace Constants = CameraSerialisationConstants;

        const TUID uid = deserialiser.DeserialiseUnsigned(ComponentSerialisationConstants::k_uid_attribute);
        SetUID(uid);

        m_camera_mode = static_cast<CameraMode>(deserialiser.DeserialiseUnsigned(Constants::k_camera_mode_attribute));

        m_fov = deserialiser.DeserialiseFloat(Constants::k_fov_attribute);
        m_aspect_ratio = deserialiser.DeserialiseFloat(Constants::k_aspect_ratio_attribute);

        m_xmin = deserialiser.DeserialiseFloat(Constants::k_xmin_attribute);
        m_xmax = deserialiser.DeserialiseFloat(Constants::k_xmax_attribute);
        m_ymin = deserialiser.DeserialiseFloat(Constants::k_ymin_attribute);
        m_ymax = deserialiser.DeserialiseFloat(Constants::k_ymax_attribute);

        m_znear = deserialiser.DeserialiseFloat(Constants::k_znear_attribute);
        m_zfar = deserialiser.DeserialiseFloat(Constants::k_zfar_attribute);
    }
}
