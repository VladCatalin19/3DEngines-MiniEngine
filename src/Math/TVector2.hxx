#ifndef M3GTR_SRC_MATH_TVECTOR2_HXX_INCLUDED
#define M3GTR_SRC_MATH_TVECTOR2_HXX_INCLUDED

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>                          // glm::tvec2

#include <ostream>              // std::ostream
#include <string>               // std::string

namespace MG3TR
{
    template<typename TInternalType>
    class TVector2
    {
    private:
        glm::tvec2<TInternalType> m_vec2;

        constexpr TVector2(const glm::tvec2<TInternalType> &v);

    public:
        constexpr TVector2() noexcept;
        constexpr TVector2(TInternalType x, TInternalType y) noexcept;
        constexpr TVector2(const TVector2<TInternalType> &v) noexcept;
        constexpr TVector2(TVector2<TInternalType> &&v) noexcept;

        constexpr TVector2<TInternalType>& operator=(const TVector2<TInternalType> &v) noexcept;
        constexpr TVector2<TInternalType>& operator=(TVector2<TInternalType> &&v) noexcept;

        constexpr TInternalType& operator[](std::size_t index) noexcept;
        constexpr const TInternalType& operator[](std::size_t index) const noexcept;

        TInternalType& at(std::size_t index);
        const TInternalType& at(std::size_t index) const;

        constexpr TInternalType& x() noexcept;
        constexpr TInternalType& y() noexcept;

        constexpr TInternalType x() const noexcept;
        constexpr TInternalType y() const noexcept;

        static constexpr std::size_t Size() noexcept;
        
        TVector2<TInternalType>& Set(TInternalType x, TInternalType y) noexcept;

        TInternalType* InternalDataPointer() noexcept;
        const TInternalType* InternalDataPointer() const noexcept;

        TInternalType Distance(const TVector2<TInternalType> &v) const noexcept;
        static TInternalType Distance(const TVector2<TInternalType> &v1,
                                      const TVector2<TInternalType> &v2) noexcept;

        TInternalType Dot(const TVector2<TInternalType> &v) const noexcept;
        static TInternalType Dot(const TVector2<TInternalType> &v1,
                                 const TVector2<TInternalType> &v2) noexcept;

        static TVector2<TInternalType> FaceForward(const TVector2<TInternalType> &in,
                                                   const TVector2<TInternalType> &normal,
                                                   const TVector2<TInternalType> &normal_ref) noexcept;

        static TVector2<TInternalType> Lerp(const TVector2<TInternalType> &v1,
                                            const TVector2<TInternalType> &v2,
                                            float t) noexcept;

        float Magnitude() const noexcept;
        float SquareMagnitude() const noexcept;

        TVector2<TInternalType>& Normalize() noexcept;
        static TVector2<TInternalType> Normalize(const TVector2<TInternalType> &v) noexcept;

        static TVector2<TInternalType> Reflect(const TVector2<TInternalType> &in,
                                               const TVector2<TInternalType> &normal) noexcept;
        static TVector2<TInternalType> Refract(const TVector2<TInternalType> &in,
                                               const TVector2<TInternalType> &normal,
                                               TInternalType eta) noexcept;

        TVector2<TInternalType>& Scale(const TVector2<TInternalType> &v) noexcept;
        static TVector2<TInternalType> Scale(const TVector2<TInternalType> &v1,
                                             const TVector2<TInternalType> &v2) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector2<TInternalType>& operator+=(const TVector2<TOtherInternalType> &v) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector2<TInternalType>& operator-=(const TVector2<TOtherInternalType> &v) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector2<TInternalType>& operator*=(TOtherInternalType scalar) noexcept;

        template<typename TOtherInternalType>
        constexpr TVector2<TInternalType>& operator/=(TOtherInternalType scalar) noexcept;

        constexpr bool operator==(const TVector2<TInternalType> &v) noexcept;
        constexpr bool operator!=(const TVector2<TInternalType> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector2<TInternal> operator+(const TVector2<TInternal> &v) noexcept;

        template<typename TInternal>
        friend constexpr TVector2<TInternal> operator-(const TVector2<TInternal> &v) noexcept;


        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator+(const TVector2<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector2<TInternal> operator+(const TVector2<TInternal> &v1,
                                                       const TVector2<TInternal> &v2) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator+(TOtherInternalType scalar,
                                                       const TVector2<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator-(const TVector2<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        template<typename TInternal>
        friend constexpr TVector2<TInternal> operator-(const TVector2<TInternal> &v1,
                                                       const TVector2<TInternal> &v2) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator-(TOtherInternalType scalar,
                                                       const TVector2<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator*(const TVector2<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator*(TOtherInternalType scalar,
                                                       const TVector2<TInternal> &v) noexcept;

        template<typename TInternal, typename TOtherInternalType>
        friend constexpr TVector2<TInternal> operator/(const TVector2<TInternal> &v,
                                                       TOtherInternalType scalar) noexcept;

        std::string ToString() const;
        template <typename TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TVector2<TInternal> &v);
    };
}

#include "TVector2.ixx"

#endif // M3GTR_SRC_MATH_TVECTOR2_HXX_INCLUDED
