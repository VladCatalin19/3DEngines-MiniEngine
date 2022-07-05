#ifndef MG3TR_SRC_MATH_SPHERE_HPP_INCLUDED
#define MG3TR_SRC_MATH_SPHERE_HPP_INCLUDED

#include <Math/Plane.hpp>
#include <Math/Vector3.hpp>

namespace MG3TR
{
    class Sphere
    {
    private:
        Vector3 m_center;
        float m_radius;

    public:
        Sphere() noexcept = default;

        Sphere(Vector3 center, float radius) noexcept
            : m_center(center),
              m_radius(radius)
        {}

        Vector3 GetCenter() const noexcept { return m_center; }
        float GetRadius() const noexcept { return m_radius; }

        bool IsOnOrInFrontOfPlane(const Plane &plane) const noexcept
        {
            return plane.GetSignedDistance(m_center) > -m_radius;
        }
    };
}

#endif // MG3TR_SRC_MATH_SPHERE_HPP_INCLUDED
