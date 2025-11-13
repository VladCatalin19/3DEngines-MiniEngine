#ifndef MG3TR_SRC_MATH_FRUSTUM_HPP_INCLUDED
#define MG3TR_SRC_MATH_FRUSTUM_HPP_INCLUDED

#include <Math/Plane.hpp>

namespace MG3TR
{
    class Camera;

    class Frustum
    {
    private:
        Plane m_top_face;
        Plane m_bottom_face;

        Plane m_right_face;
        Plane m_left_face;

        Plane m_far_face;
        Plane m_near_face;

    public:
        Frustum(const Camera& camera);
        ~Frustum() = default;

        Frustum(const Frustum&) = default;
        Frustum(Frustum&&) = default;

        Frustum& operator=(const Frustum&) = default;
        Frustum& operator=(Frustum&&) = default;

        Plane GetTopFace() const;
        Plane GetBottomFace() const;

        Plane GetRightFace() const;
        Plane GetLeftFace() const;

        Plane GetFarFace() const;
        Plane GetNearFace() const;
    };
}

#endif // MG3TR_SRC_MATH_FRUSTUM_HPP_INCLUDED
