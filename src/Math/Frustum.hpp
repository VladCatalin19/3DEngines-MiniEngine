#ifndef MG3TR_SRC_MATH_FRUSTUM_HPP_INCLUDED
#define MG3TR_SRC_MATH_FRUSTUM_HPP_INCLUDED

#include <Components/Camera.hpp>
#include <Math/Plane.hpp>

namespace MG3TR
{
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
        Frustum(const Camera &camera);

        Plane GetTopFace() const noexcept { return m_top_face; }
        Plane GetBottomFace() const noexcept { return m_bottom_face; }

        Plane GetRightFace() const noexcept { return m_right_face; }
        Plane GetLeftFace() const noexcept { return m_left_face; }

        Plane GetFarFace() const noexcept { return m_far_face; }
        Plane GetNearFace() const noexcept { return m_near_face; }
    };
}

#endif // MG3TR_SRC_MATH_FRUSTUM_HPP_INCLUDED
