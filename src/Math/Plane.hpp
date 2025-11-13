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
        Plane(const Vector3& normal = Vector3Constants::k_zero, float distance = 0.0F);
        Plane(const Vector3& normal, const Vector3& in_point);
        ~Plane() = default;

        Plane(const Plane&) = default;
        Plane(Plane&&) = default;
        
        Plane& operator=(const Plane&) = default;
        Plane& operator=(Plane&&) = default;
        
        Vector3 GetNormal() const;
        float GetDistance() const;

        float GetSignedDistance(const Vector3& point) const;
    };
}

#endif // MG3TR_SRC_MATH_PLANE_HPP_INCLUDED
