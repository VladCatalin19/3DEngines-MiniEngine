#ifndef MG3TR_SRC_MATH_PLANE_HPP_INCLUDED
#define MG3TR_SRC_MATH_PLANE_HPP_INCLUDED

#include <Constants/MathConstants.hpp>
#include <Math/Vector3.hpp>

namespace MG3TR
{
    class Plane
    {
    private:
        Vector3 m_normal;
        float m_distance;

    public:
        Plane(const Vector3 &normal = Vector3Constants::k_zero, float distance = 0.0F) noexcept
            : m_normal(normal),
              m_distance(distance)
        {}

        Plane(const Vector3 &normal, const Vector3 &in_point) noexcept
            : m_normal(Vector3::Normalize(normal)),
              m_distance(Vector3::Dot(normal, in_point))
        {}

        Vector3 GetNormal() const noexcept { return m_normal; }
        float GetDistance() const noexcept { return m_distance; }

        float GetSignedDistance(const Vector3 &point) const noexcept
        {
            return Vector3::Dot(m_normal, point) - m_distance;
        }
    };
}

#endif // MG3TR_SRC_MATH_PLANE_HPP_INCLUDED
