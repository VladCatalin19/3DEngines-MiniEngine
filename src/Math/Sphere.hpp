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
        Sphere() = default;
        Sphere(const Vector3& center, const float radius);
        ~Sphere() = default;

        Sphere(const Sphere&) = default;
        Sphere(Sphere&&) = default;
        
        Sphere& operator=(const Sphere&) = default;
        Sphere& operator=(Sphere&&) = default;

        Vector3 GetCenter() const;
        float GetRadius() const;

        bool IsOnOrInFrontOfPlane(const Plane& plane) const;
    };
}

#endif // MG3TR_SRC_MATH_SPHERE_HPP_INCLUDED
