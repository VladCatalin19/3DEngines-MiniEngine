#ifndef MG3TR_SRC_COMPONENTS_CAMERA_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_CAMERA_HPP_INCLUDED

#include <Components/Component.hpp>

#include <Math/Vector3.hpp>
#include <Math/Matrix4x4.hpp>

#include <memory>

namespace MG3TR
{
    enum class CameraMode : unsigned char
    {
        Perspective = 0U,
        Orthographic = 1U
    };

    class Camera : public Component
    {
    private:
        CameraMode m_camera_mode;

        // Persecpective fields
        float m_fov;
        float m_aspect_ratio;

        // Orthographic fields
        float m_xmin;
        float m_xmax;
        float m_ymin;
        float m_ymax;

        // Both perspective and orthographic fields
        float m_znear;
        float m_zfar;

    public:
        Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform);

        Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
               const float fov, const float aspect_ratio, const float znear, const float zfar);

        Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
               const float xmin, const float xmax, const float ymin, const float ymax, const float znear, const float zfar);
        virtual ~Camera() = default;

        Camera(const Camera &) = delete;
        Camera(Camera &&) = default;
        
        Camera& operator=(const Camera &) = delete;
        Camera& operator=(Camera &&) = default;

        Matrix4x4 GetViewMatrix() const;
        Matrix4x4 GetProjectionMatrix() const;

        CameraMode GetCameraMode() const;
        float GetFov() const;
        float GetAspectRatio() const;

        float GetXmin() const;
        float GetXmax() const;
        float GetYmin() const;
        float GetYmax() const;

        float GetZnear() const;
        float GetZfar() const;

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_CAMERA_HPP_INCLUDED
