#include "Plane.hpp"

namespace MG3TR
{
    Plane::Plane(const Vector3& normal, const float distance)
        : m_normal(normal),
          m_distance(distance)
    {

    }

    Plane::Plane(const Vector3& normal, const Vector3& in_point)
        : m_normal(Vector3::Normalize(normal)),
          m_distance(Vector3::Dot(normal, in_point))
    {

    }

    Vector3 Plane::GetNormal() const 
    {
         return m_normal;
    }

    float Plane::GetDistance() const
    {
        return m_distance;
    }

    float Plane::GetSignedDistance(const Vector3& point) const
    {
        const float dot = Vector3::Dot(m_normal, point);
        const float distance = dot - m_distance;

        return distance;
    }
}