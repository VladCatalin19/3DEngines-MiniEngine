#ifndef M3GTR_SRC_MATH_TMATRIX4X4_HXX_INCLUDED
#define M3GTR_SRC_MATH_TMATRIX4X4_HXX_INCLUDED

#include "TQuaternion.hxx"
#include "TVector3.hxx"
#include "TVector4.hxx"

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>                          // glm::tmat4x4

#include <ostream>              // std::ostream
#include <string>               // std::string
#include <utility>              // std::pair

namespace MG3TR
{
    template<typename TInternalType>
    class TMatrix4x4
    {
    private:
        glm::tmat4x4<TInternalType> m_mat4x4;

        constexpr TMatrix4x4(const glm::tmat4x4<TInternalType> &mat4x4) noexcept;

    public:
        constexpr TMatrix4x4(TInternalType value_on_diagonal = static_cast<TInternalType>(0)) noexcept;
        constexpr TMatrix4x4(TInternalType m00, TInternalType m01, TInternalType m02, TInternalType m03,
                             TInternalType m10, TInternalType m11, TInternalType m12, TInternalType m13,
                             TInternalType m20, TInternalType m21, TInternalType m22, TInternalType m23,
                             TInternalType m30, TInternalType m31, TInternalType m32, TInternalType m33) noexcept;
        constexpr TMatrix4x4(const TVector4<TInternalType> &c0, const TVector4<TInternalType> &c1,
                             const TVector4<TInternalType> &c2, const TVector4<TInternalType> &c3) noexcept;
        constexpr TMatrix4x4(const TMatrix4x4<TInternalType> &m) noexcept;
        constexpr TMatrix4x4(TMatrix4x4<TInternalType> &&m) noexcept;

        constexpr TMatrix4x4<TInternalType>& operator=(const TMatrix4x4<TInternalType> &m) noexcept;
        constexpr TMatrix4x4<TInternalType>& operator=(TMatrix4x4<TInternalType> &&m) noexcept;

        constexpr TVector4<TInternalType> operator[](std::size_t index) const noexcept;
        constexpr TInternalType& operator[](const std::pair<std::size_t, std::size_t> &position) noexcept;
        constexpr const TInternalType& operator[](const std::pair<std::size_t, std::size_t> &position) const noexcept;

        TVector4<TInternalType> at(std::size_t index) const;
        TInternalType& at(const std::pair<std::size_t, std::size_t> &position) noexcept;
        const TInternalType& at(const std::pair<std::size_t, std::size_t> &position) const noexcept;

        static constexpr std::size_t Size() noexcept;

        TInternalType* InternalDataPointer() noexcept;
        const TInternalType* InternalDataPointer() const noexcept;

        static TMatrix4x4<TInternalType> LookAt(const TVector3<TInternalType> &eye,
                                                const TVector3<TInternalType> &center,
                                                const TVector3<TInternalType> &up) noexcept;

        static TMatrix4x4<TInternalType> Perspective(TInternalType fov, TInternalType aspect,
                                                     TInternalType znear, TInternalType zfar) noexcept;

        static TMatrix4x4<TInternalType> Orthographic(TInternalType xmin, TInternalType xmax,
                                                      TInternalType ymin, TInternalType ymax,
                                                      TInternalType zmin, TInternalType zmax) noexcept;

        TMatrix4x4<TInternalType>& Translate(const TVector3<TInternalType> &v) noexcept;
        static TMatrix4x4<TInternalType> Translate(const TMatrix4x4<TInternalType> &m,
                                                   const TVector3<TInternalType> &v) noexcept;

        TMatrix4x4<TInternalType>& Scale(const TVector3<TInternalType> &v) noexcept;
        static TMatrix4x4<TInternalType> Scale(const TMatrix4x4<TInternalType> &m,
                                               const TVector3<TInternalType> &v) noexcept;

        TMatrix4x4<TInternalType>& Rotate(TInternalType angle, const TVector3<TInternalType> &axis) noexcept;
        static TMatrix4x4<TInternalType> Rotate(const TMatrix4x4<TInternalType> &m,
                                                TInternalType angle,
                                                const TVector3<TInternalType> &axis) noexcept;

        TMatrix4x4<TInternalType>& Rotate(const TQuaternion<TInternalType> &q) noexcept;
        static TMatrix4x4<TInternalType> Rotate(const TMatrix4x4<TInternalType> &m,
                                                const TQuaternion<TInternalType> &q) noexcept;

        TMatrix4x4<TInternalType>& Transpose() noexcept;
        static TMatrix4x4<TInternalType> Transpose(const TMatrix4x4<TInternalType> &m) noexcept;

        TMatrix4x4<TInternalType>& Inverse() noexcept;
        static TMatrix4x4<TInternalType> Inverse(const TMatrix4x4<TInternalType> &m) noexcept;

        template<typename TOtherInternalType>
        constexpr TMatrix4x4<TInternalType>& operator+=(const TMatrix4x4<TOtherInternalType> &m) noexcept;

        template<typename TOtherInternalType>
        constexpr TMatrix4x4<TInternalType>& operator-=(const TMatrix4x4<TOtherInternalType> &m) noexcept;

        template<typename TOtherInternalType>
        constexpr TMatrix4x4<TInternalType>& operator*=(const TMatrix4x4<TOtherInternalType> &m) noexcept;

        template<typename TOtherInternalType>
        constexpr TMatrix4x4<TInternalType>& operator*=(TOtherInternalType scalar) noexcept;

        template<typename TOtherInternalType>
        constexpr TMatrix4x4<TInternalType>& operator/=(TOtherInternalType scalar) noexcept;

        constexpr bool operator==(const TMatrix4x4<TInternalType> &m) noexcept;
        constexpr bool operator!=(const TMatrix4x4<TInternalType> &m) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator+(const TMatrix4x4<TInternal> &m) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator-(const TMatrix4x4<TInternal> &m) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TMatrix4x4<TInternal> operator+(const TMatrix4x4<TInternal> &m,
                                                         TOtherInternalType scalar) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator+(const TMatrix4x4<TInternal> &m1,
                                                         const TMatrix4x4<TInternal> &m2) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator+(TInternal scalar,
                                                         const TMatrix4x4<TInternal> &m) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator-(const TMatrix4x4<TInternal> &m,
                                                         TInternal scalar) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator-(const TMatrix4x4<TInternal> &m1,
                                                         const TMatrix4x4<TInternal> &m2) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator-(TInternal scalar,
                                                         const TMatrix4x4<TInternal> &m) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator*(const TMatrix4x4<TInternal> &m,
                                                         TInternal scalar) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator*(TInternal scalar,
                                                         const TMatrix4x4<TInternal> &m) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator*(const TMatrix4x4<TInternal> &m,
                                                       const TVector4<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator*(const TMatrix4x4<TInternal> &m1,
                                                         const TMatrix4x4<TInternal> &m2) noexcept;

        template<typename TInternal>
        friend constexpr TMatrix4x4<TInternal> operator/(const TMatrix4x4<TInternal> &m,
                                                         TInternal scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator/(const TMatrix4x4<TInternal> &m,
                                                       const TVector4<TInternal> &v) noexcept;

        std::string ToString(const std::string &row_indent = "") const;
        template<typename TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TMatrix4x4<TInternal> &m);
    };
}

#include "TMatrix4x4.ixx"

#endif // M3GTR_SRC_MATH_TMATRIX4X4_HXX_INCLUDED
