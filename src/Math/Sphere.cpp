#include "Sphere.hpp"

namespace MG3TR
{
    Sphere::Sphere(const Vector3& center, const float radius)
        : m_center(center),
          m_radius(radius)
    {

    }

    Vector3 Sphere::GetCenter() const
    {
        return m_center;
    }

    float Sphere::GetRadius() const
    {
        return m_radius;
    }

    bool Sphere::IsOnOrInFrontOfPlane(const Plane &plane) const
    {
        const float signed_distance = plane.GetSignedDistance(m_center);

        bool is_on_or_in_front = false;

        if (signed_distance > -m_radius)
        {
            is_on_or_in_front = true;
        }
        
        return is_on_or_in_front;
    }
}