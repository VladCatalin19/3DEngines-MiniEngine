#include "Frustum.hpp"

#include <Components/Camera.hpp>
#include <Math/Math.hxx>
#include <Math/Vector3.hpp>
#include <Scripting/Transform.hpp>

namespace MG3TR
{
    Frustum::Frustum(const Camera &camera) 
    {
        const auto camera_transform = camera.GetTransform().lock();
        const Vector3 camera_position = camera_transform->GetWorldPosition();

        const float half_vertical_side = camera.GetZfar() * Math::Tan(camera.GetFov() * 0.5F);
        const float half_horizontal_side = half_vertical_side * camera.GetAspectRatio();
        const Vector3 front_times_far = camera.GetZfar() * camera_transform->GetForwards();
    
        const Vector3 mear_face_normal = camera_transform->GetForwards();
        const Vector3 near_face_center = camera_position + camera.GetZnear() * camera_transform->GetForwards();
        m_near_face = Plane(mear_face_normal, near_face_center);

        const Vector3 far_face_normal = -camera_transform->GetForwards();
        const Vector3 far_face_center = camera_position + camera.GetZfar() * camera_transform->GetForwards();
        m_far_face = Plane(far_face_normal, far_face_center);

        const Vector3 right_face_normal = Vector3::Cross(camera_transform->GetUp().Normalize(),
                                                         (front_times_far + camera_transform->GetRight() * half_horizontal_side).Normalize());
        const Vector3 right_face_position = camera_position;
        m_right_face = Plane(right_face_normal, right_face_position);

        const Vector3 left_face_normal = Vector3::Cross((front_times_far - camera_transform->GetRight() * half_horizontal_side).Normalize(),
                                                         camera_transform->GetUp().Normalize());
        const Vector3 left_face_position = camera_position;
        m_left_face = Plane(left_face_normal, left_face_position);

        const Vector3 top_face_normal = Vector3::Cross((front_times_far + camera_transform->GetUp() * half_vertical_side).Normalize(),
                                                        camera_transform->GetRight().Normalize());
        const Vector3 top_face_position = camera_position;
        m_top_face = Plane(top_face_normal, top_face_position);

        const Vector3 bottom_face_normal = Vector3::Cross(camera_transform->GetRight().Normalize(),
                                                          (front_times_far - camera_transform->GetUp() * half_vertical_side).Normalize());
        const Vector3 bottom_face_position = camera_position;
        m_bottom_face = Plane(bottom_face_normal, bottom_face_position);
    }

    Plane Frustum::GetTopFace() const
    {
        return m_top_face;
    }

    Plane Frustum::GetBottomFace() const
    {
        return m_bottom_face;
    }

    Plane Frustum::GetRightFace() const
    {
        return m_right_face;
    }

    Plane Frustum::GetLeftFace() const
    {
        return m_left_face;
    }

    Plane Frustum::GetFarFace() const
    {
        return m_far_face;
    }

    Plane Frustum::GetNearFace() const
    {
        return m_near_face;
    }
}
