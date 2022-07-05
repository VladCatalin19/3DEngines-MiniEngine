#ifndef M3GTR_SRC_MATH_TVECTOR3_HXX_INCLUDED
#define M3GTR_SRC_MATH_TVECTOR3_HXX_INCLUDED

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>                          // glm::tvec3

#include <ostream>              // std::ostream
#include <string>               // std::string

namespace MG3TR
{
    template<typename TInternalType>
    class TVector3
    {
    private:
        glm::tvec3<TInternalType> m_vec3;

        constexpr TVector3(const glm::tvec3<TInternalType> &v);

    public:
        constexpr TVector3() noexcept;
        constexpr TVector3(TInternalType x, TInternalType y, TInternalType z) noexcept;
        constexpr TVector3(const TVector3<TInternalType> &v) noexcept;
        constexpr TVector3(TVector3<TInternalType> &&v) noexcept;

        constexpr TVector3<TInternalType>& operator=(const TVector3<TInternalType> &v) noexcept;
        constexpr TVector3<TInternalType>& operator=(TVector3<TInternalType> &&v) noexcept;

        constexpr TInternalType& operator[](std::size_t index) noexcept;
        constexpr const TInternalType& operator[](std::size_t index) const noexcept;

        TInternalType& at(std::size_t index);
        const TInternalType& at(std::size_t index) const;

        constexpr TInternalType& x() noexcept;
        constexpr TInternalType& y() noexcept;
        constexpr TInternalType& z() noexcept;

        constexpr TInternalType x() const noexcept;
        constexpr TInternalType y() const noexcept;
        constexpr TInternalType z() const noexcept;

        static constexpr std::size_t Size() noexcept;

        constexpr TVector3<TInternalType>& Set(TInternalType x, TInternalType y, TInternalType z) noexcept;

        TInternalType* InternalDataPointer() noexcept;
        const TInternalType* InternalDataPointer() const noexcept;

        TVector3<TInternalType> Cross(const TVector3<TInternalType> &v) const noexcept;
        static TVector3<TInternalType> Cross(const TVector3<TInternalType> &v1,
                                             const TVector3<TInternalType> &v2) noexcept;

        TInternalType Distance(const TVector3<TInternalType> &v) const noexcept;
        static TInternalType Distance(const TVector3<TInternalType> &v1,
                                      const TVector3<TInternalType> &v2) noexcept;

        TInternalType Dot(const TVector3<TInternalType> &v) const noexcept;
        static TInternalType Dot(const TVector3<TInternalType> &v1,
                                           const TVector3<TInternalType> &v2) noexcept;

        static TVector3<TInternalType> FaceForward(const TVector3<TInternalType> &in,
                                                             const TVector3<TInternalType> &normal,
                                                             const TVector3 &normal_ref) noexcept;

        static TVector3<TInternalType> Lerp(const TVector3<TInternalType> &v1,
                                                      const TVector3<TInternalType> &v2,
                                                      float t) noexcept;

        float Magnitude() const noexcept;
        float SquareMagnitude() const noexcept;

        TVector3<TInternalType>& Normalize() noexcept;
        static TVector3<TInternalType> Normalize(const TVector3<TInternalType> &v) noexcept;

        static TVector3<TInternalType> Reflect(const TVector3<TInternalType> &in,
                                               const TVector3<TInternalType> &normal) noexcept;
        static TVector3<TInternalType> Refract(const TVector3<TInternalType> &in,
                                               const TVector3<TInternalType> &normal,
                                               TInternalType eta) noexcept;

        TVector3<TInternalType>& Scale(const TVector3<TInternalType> &v) noexcept;
        static TVector3<TInternalType> Scale(const TVector3<TInternalType> &v1,
                                                       const TVector3<TInternalType> &v2) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector3<TInternalType>& operator+=(const TVector3<TOtherInternalType> &v) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector3<TInternalType>& operator-=(const TVector3<TOtherInternalType> &v) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector3<TInternalType>& operator*=(TOtherInternalType scalar) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector3<TInternalType>& operator/=(TOtherInternalType scalar) noexcept;

        constexpr bool operator==(const TVector3<TInternalType> &v) noexcept;
        constexpr bool operator!=(const TVector3<TInternalType> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector3<TInternal> operator+(const TVector3<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector3<TInternal> operator-(const TVector3<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator+(const TVector3<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector3<TInternal> operator+(const TVector3<TInternal> &v1,
                                                       const TVector3<TInternal> &v2) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator+(TOtherInternalType scalar,
                                                       const TVector3<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator-(const TVector3<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector3<TInternal> operator-(const TVector3<TInternal> &v1,
                                                       const TVector3<TInternal> &v2) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator-(TOtherInternalType scalar,
                                                       const TVector3<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator*(const TVector3<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator*(TOtherInternalType scalar,
                                                       const TVector3<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector3<TInternal> operator/(const TVector3<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        std::string ToString() const;
        template<typename TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TVector3<TInternal> &v);
    };
}

#include "TVector3.ixx"

#endif // M3GTR_SRC_MATH_TVECTOR3_HXX_INCLUDED
