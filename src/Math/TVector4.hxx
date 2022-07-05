#ifndef M3GTR_SRC_MATH_TVECTOR4_HXX_INCLUDED
#define M3GTR_SRC_MATH_TVECTOR4_HXX_INCLUDED

#include "TVector3.hxx"

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>                          // glm::tvec4

#include <ostream>              // std::ostream
#include <string>               // std::string

namespace MG3TR
{
    template<typename TInternalType>
    class TVector4
    {
    private:
        glm::tvec4<TInternalType> m_vec4;

        constexpr TVector4(const glm::tvec4<TInternalType> &v);

    public:
        constexpr TVector4() noexcept;
        constexpr TVector4(TInternalType x, TInternalType y, TInternalType z, TInternalType w) noexcept;
        constexpr TVector4(const TVector3<TInternalType> &v, TInternalType w) noexcept;
        constexpr TVector4(const TVector4<TInternalType> &v) noexcept;
        constexpr TVector4(TVector4<TInternalType> &&v) noexcept;

        constexpr TVector4<TInternalType>& operator=(const TVector4<TInternalType> &v) noexcept;
        constexpr TVector4<TInternalType>& operator=(TVector4<TInternalType> &&v) noexcept;

        constexpr TInternalType& operator[](std::size_t index) noexcept;
        constexpr const TInternalType& operator[](std::size_t index) const noexcept;

        TInternalType& at(std::size_t index);
        const TInternalType& at(std::size_t index) const;

        constexpr TInternalType& x() noexcept;
        constexpr TInternalType& y() noexcept;
        constexpr TInternalType& z() noexcept;
        constexpr TInternalType& w() noexcept;

        constexpr TInternalType x() const noexcept;
        constexpr TInternalType y() const noexcept;
        constexpr TInternalType z() const noexcept;
        constexpr TInternalType w() const noexcept;

        static constexpr std::size_t Size() noexcept;

        constexpr TVector4<TInternalType>& Set(TInternalType x, TInternalType y, TInternalType z, TInternalType w) noexcept;

        TInternalType* InternalDataPointer() noexcept;
        const TInternalType* InternalDataPointer() const noexcept;

        TInternalType Distance(const TVector4<TInternalType> &v) const noexcept;
        static TInternalType Distance(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2) noexcept;

        TInternalType Dot(const TVector4<TInternalType> &v) const noexcept;
        static TInternalType Dot(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2) noexcept;

        static TVector4<TInternalType> FaceForward(const TVector4<TInternalType> &in,
                                                   const TVector4<TInternalType> &normal,
                                                   const TVector4<TInternalType> &normal_ref) noexcept;

        static TVector4<TInternalType> Lerp(const TVector4<TInternalType> &v1,
                                            const TVector4<TInternalType> &v2,
                                            float t) noexcept;

        float Magnitude() const noexcept;
        float SquareMagnitude() const noexcept;

        TVector4<TInternalType>& Normalize() noexcept;
        static TVector4<TInternalType> Normalize(const TVector4<TInternalType> &v) noexcept;

        static TVector4<TInternalType> Reflect(const TVector4<TInternalType> &in,
                                               const TVector4<TInternalType> &normal) noexcept;
        static TVector4<TInternalType> Refract(const TVector4<TInternalType> &in,
                                               const TVector4<TInternalType> &normal,
                                               TInternalType eta) noexcept;

        TVector4<TInternalType>& Scale(const TVector4<TInternalType> &v) noexcept;
        static TVector4<TInternalType> Scale(const TVector4<TInternalType> &v1,
                                             const TVector4<TInternalType> &v2) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector4<TInternalType>& operator+=(const TVector4<TOtherInternalType> &v) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector4<TInternalType>& operator-=(const TVector4<TOtherInternalType> &v) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector4<TInternalType>& operator*=(TOtherInternalType scalar) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector4<TInternalType>& operator/=(TOtherInternalType scalar) noexcept;

        constexpr bool operator==(const TVector4<TInternalType> &v) noexcept;

        constexpr bool operator!=(const TVector4<TInternalType> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator+(const TVector4<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator-(const TVector4<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator+(const TVector4<TInternal> &v, TInternal scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator+(const TVector4<TInternal> &v1, const TVector4<TInternal> &v2) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator+(TInternal scalar, const TVector4<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator-(const TVector4<TInternal> &v, TInternal scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator-(const TVector4<TInternal> &v1, const TVector4<TInternal> &v2) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator-(TInternal scalar, const TVector4<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator*(const TVector4<TInternal> &v, TInternal scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator*(TInternal scalar, const TVector4<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector4<TInternal> operator/(const TVector4<TInternal> &v, TInternal scalar) noexcept;

        std::string ToString() const;
        template<typename TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TVector4<TInternal> &v);
    };
}

#include "TVector4.ixx"

#endif // M3GTR_SRC_MATH_TVECTOR4_HXX_INCLUDED
