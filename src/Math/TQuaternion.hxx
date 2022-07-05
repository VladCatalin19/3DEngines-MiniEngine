#ifndef M3GTR_SRC_MATH_TQUATERNION_HXX_INCLUDED
#define M3GTR_SRC_MATH_TQUATERNION_HXX_INCLUDED

#include "TVector3.hxx"

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>                          // glm::tquat
#include <glm/detail/type_quat.hpp>             // glm::tquat

#include <ostream>              // std::ostream
#include <string>               // std::string

namespace MG3TR
{
    template<typename TInternalType>
    class TQuaternion
    {
    private:
        glm::tquat<TInternalType> m_quat;

        constexpr TQuaternion(const glm::tquat<TInternalType> &quat) noexcept;

    public:
        constexpr TQuaternion() noexcept;
        constexpr TQuaternion(TInternalType s, const TVector3<TInternalType> &v) noexcept;
        constexpr TQuaternion(TInternalType w, TInternalType x, TInternalType y, TInternalType z) noexcept;
        // from and to must be normalized
        constexpr TQuaternion(const TVector3<TInternalType> &from, const TVector3<TInternalType> &to) noexcept;
        constexpr TQuaternion(const TVector3<TInternalType> &euler_angles) noexcept;
        static constexpr TQuaternion<TInternalType> FromAngleAxis(TInternalType angle,
                                                                  const TVector3<TInternalType> &axis) noexcept;
        constexpr TQuaternion(const TQuaternion<TInternalType> &q) noexcept;
        constexpr TQuaternion(TQuaternion<TInternalType> &&q) noexcept;

        constexpr TQuaternion<TInternalType>& operator=(const TQuaternion<TInternalType> &q) noexcept;
        constexpr TQuaternion<TInternalType>& operator=(TQuaternion<TInternalType> &&q) noexcept;

        constexpr TInternalType& operator[](std::size_t index) noexcept;
        constexpr const TInternalType& operator[](std::size_t index) const noexcept;

        TInternalType& at(std::size_t index);
        const TInternalType& at(std::size_t index) const;

        constexpr TInternalType& w() noexcept;
        constexpr TInternalType& x() noexcept;
        constexpr TInternalType& y() noexcept;
        constexpr TInternalType& z() noexcept;

        constexpr TInternalType w() const noexcept;
        constexpr TInternalType x() const noexcept;
        constexpr TInternalType y() const noexcept;
        constexpr TInternalType z() const noexcept;

        static constexpr std::size_t Size() noexcept;

        TQuaternion<TInternalType>& Set(TInternalType w, TInternalType x, TInternalType y, TInternalType z) noexcept;

        TInternalType Angle() const noexcept;
        static TInternalType Angle(const TQuaternion<TInternalType> &q) noexcept;

        TVector3<TInternalType> Axis() const noexcept;
        static TVector3<TInternalType> Axis(const TQuaternion<TInternalType> &q) noexcept;

        TQuaternion<TInternalType>& Conjugate();
        static TQuaternion<TInternalType> Conjugate(TQuaternion<TInternalType> &q);

        TQuaternion<TInternalType> Cross(const TQuaternion<TInternalType> &q) const noexcept;
        static TQuaternion<TInternalType> Cross(const TQuaternion<TInternalType> &q1,
                                                const TQuaternion<TInternalType> &q2) noexcept;

        TInternalType Dot(const TQuaternion<TInternalType> &q) const noexcept;
        static TInternalType Dot(const TQuaternion<TInternalType> &q1,
                                 const TQuaternion<TInternalType> &q2) noexcept;

        TVector3<TInternalType> EulerAngles() const noexcept;
        static TVector3<TInternalType> EulerAngles(const TQuaternion<TInternalType> &q) noexcept;

        TQuaternion<TInternalType>& Inverse() noexcept;
        static TQuaternion<TInternalType> Inverse(const TQuaternion<TInternalType> &q) noexcept;

        static TQuaternion<TInternalType> Lerp(const TQuaternion<TInternalType> &q1,
                                               const TQuaternion<TInternalType> &q2,
                                               float t) noexcept;

        TQuaternion<TInternalType>& Normalize() noexcept;
        static TQuaternion<TInternalType> Normalize(const TQuaternion<TInternalType> &q) noexcept;

        static TQuaternion<TInternalType> Slerp(const TQuaternion<TInternalType> &q1,
                                                const TQuaternion<TInternalType> &q2,
                                                float t) noexcept;

        constexpr TQuaternion<TInternalType>& operator*=(const TQuaternion<TInternalType> &q) noexcept;
        constexpr TQuaternion<TInternalType>& operator*=(const TVector3<TInternalType> &v) noexcept;

        template<typename TInternal>
        friend constexpr TQuaternion<TInternal> operator*(const TQuaternion<TInternal> &q1,
                                                          const TQuaternion<TInternal> &q2) noexcept;
        template<typename TInternal>
        friend constexpr TVector3<TInternal> operator*(const TQuaternion<TInternal> &q,
                                                       const TVector3<TInternal> &v) noexcept;

        std::string ToString() const;
        template<typename TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TQuaternion<TInternal> &q);
    };
}

#include "TQuaternion.ixx"

#endif // M3GTR_SRC_MATH_TQUATERNION_HXX_INCLUDED