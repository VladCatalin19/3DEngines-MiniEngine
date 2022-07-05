#ifndef MG3TR_SRC_COMPONENTS_CAMERA_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_CAMERA_HPP_INCLUDED

#include <Components/Component.hpp>

#include <Math/Vector3.hpp>
#include <Math/Matrix4x4.hpp>

#include <memory>               // std::weak_ptr

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
        Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
            : Component(game_object, transform)
        {}

        Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
               float fov, float aspect_ratio, float znear, float zfar) noexcept
            : Component(game_object, transform),
              m_camera_mode(CameraMode::Perspective),
              m_fov(fov),
              m_aspect_ratio(aspect_ratio),
              m_znear(znear),
              m_zfar(zfar)
        {}

        Camera(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform,
               float xmin, float xmax, float ymin, float ymax, float znear, float zfar) noexcept
            : Component(game_object, transform),
              m_camera_mode(CameraMode::Orthographic),
              m_xmin(xmin),
              m_xmax(xmax),
              m_ymin(ymin),
              m_ymax(ymax),
              m_znear(znear),
              m_zfar(zfar)
        {}
        virtual ~Camera() noexcept = default;

        Camera(const Camera &) = delete;
        Camera& operator=(const Camera &) = delete;

        Camera(Camera &&) noexcept = default;
        Camera& operator=(Camera &&) noexcept = default;

        Matrix4x4 GetViewMatrix() const noexcept;
        Matrix4x4 GetProjectionMatrix() const;

        CameraMode GetCameraMode() const noexcept { return m_camera_mode; }
        float GetFov() const noexcept { return m_fov; }
        float GetAspectRatio() const noexcept { return m_aspect_ratio; }

        float GetXmin() const noexcept { return m_xmin; }
        float GetXmax() const noexcept { return m_xmax; }
        float GetYmin() const noexcept { return m_ymin; }
        float GetYmax() const noexcept { return m_ymax; }

        float GetZnear() const noexcept { return m_znear; }
        float GetZfar() const noexcept { return m_zfar; }

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_CAMERA_HPP_INCLUDED
