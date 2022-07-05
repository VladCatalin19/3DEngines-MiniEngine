#include "Frustum.hpp"

#include <Math/Math.hxx>
#include <Math/Vector3.hpp>
#include <Scripting/Transform.hpp>

namespace MG3TR
{
    Frustum::Frustum(const Camera &camera) 
    {
        auto camera_transform = camera.GetTransform().lock();
        Vector3 camera_position = camera_transform->GetWorldPosition();

        float half_vertical_side = camera.GetZfar() * Math::Tan(camera.GetFov() * 0.5F);
        float half_horizontal_side = half_vertical_side * camera.GetAspectRatio();
        Vector3 front_times_far = camera.GetZfar() * camera_transform->GetForwards();
    
        Vector3 mear_face_normal = camera_transform->GetForwards();
        Vector3 near_face_center = camera_position + camera.GetZnear() * camera_transform->GetForwards();
        m_near_face = Plane(mear_face_normal, near_face_center);

        Vector3 far_face_normal = -camera_transform->GetForwards();
        Vector3 far_face_center = camera_position + camera.GetZfar() * camera_transform->GetForwards();
        m_far_face = Plane(far_face_normal, far_face_center);

        Vector3 right_face_normal = Vector3::Cross(camera_transform->GetUp().Normalize(),
                                                   (front_times_far + camera_transform->GetRight() * half_horizontal_side).Normalize());
        Vector3 right_face_position = camera_position;
        m_right_face = Plane(right_face_normal, right_face_position);

        Vector3 left_face_normal = Vector3::Cross((front_times_far - camera_transform->GetRight() * half_horizontal_side).Normalize(),
                                                  camera_transform->GetUp().Normalize());
        Vector3 left_face_position = camera_position;
        m_left_face = Plane(left_face_normal, left_face_position);

        Vector3 top_face_normal = Vector3::Cross((front_times_far + camera_transform->GetUp() * half_vertical_side).Normalize(),
                                                 camera_transform->GetRight().Normalize());
        Vector3 top_face_position = camera_position;
        m_top_face = Plane(top_face_normal, top_face_position);

        Vector3 bottom_face_normal = Vector3::Cross(camera_transform->GetRight().Normalize(),
                                                    (front_times_far - camera_transform->GetUp() * half_vertical_side).Normalize());
        Vector3 bottom_face_position = camera_position;
        m_bottom_face = Plane(bottom_face_normal, bottom_face_position);
    }
}
