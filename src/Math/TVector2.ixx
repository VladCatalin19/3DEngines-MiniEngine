
#include <glm/glm.hpp>                          // glm::tvec2, std::numeric_limits, glm::distance, glm::dot,
                                                // glm::faceforward, glm::mix, glm::length, glm::normalize
                                                // glm::reflect, glm::refract
#include <glm/gtc/type_ptr.hpp>                 // glm::value_ptr
#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <memory>               // std::move
#include <ostream>              // std::ostream
#include <stdexcept>            // std::out_of_range
#include <string>               // std::string, std::to_string

namespace MG3TR
{
    template<typename TInternalType>
    constexpr TVector2<TInternalType>::TVector2(const glm::tvec2<TInternalType> &v)
        : m_vec2(v)
    {}

    template<typename TInternalType>
    constexpr TVector2<TInternalType>::TVector2() noexcept
        : m_vec2(static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {}

    template<typename TInternalType>
    constexpr TVector2<TInternalType>::TVector2(TInternalType x, TInternalType y) noexcept
        : m_vec2(x, y)
    {}

    template<typename TInternalType>
    constexpr TVector2<TInternalType>::TVector2(const TVector2<TInternalType> &v) noexcept
        : m_vec2(v.m_vec2)
    {}

    template<typename TInternalType>
    constexpr TVector2<TInternalType>::TVector2(TVector2<TInternalType> &&v) noexcept
        : m_vec2(std::move(v.m_vec2))
    {}

    template<typename TInternalType>
    constexpr TVector2<TInternalType>& TVector2<TInternalType>::operator=(const TVector2<TInternalType> &v) noexcept
    {
        m_vec2 = v.m_vec2;
        return *this;
    }

    template<typename TInternalType>
    constexpr TVector2<TInternalType>& TVector2<TInternalType>::operator=(TVector2<TInternalType> &&v) noexcept
    {
        m_vec2 = std::move(v.m_vec2);
        return *this;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector2<TInternalType>::operator[](std::size_t index) noexcept
    {
        return m_vec2[index];
    }
    template<typename TInternalType>
    constexpr const TInternalType& TVector2<TInternalType>::operator[](std::size_t index) const noexcept
    {
        return m_vec2[index];
    }

    template<typename TInternalType>
    TInternalType& TVector2<TInternalType>::at(std::size_t index) try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid vector2 subscript");
        }
        return m_vec2[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    const TInternalType& TVector2<TInternalType>::at(std::size_t index) const try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid vector2 subscript");
        }
        return m_vec2[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    constexpr TInternalType& TVector2<TInternalType>::x() noexcept
    {
        return m_vec2.x;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector2<TInternalType>::y() noexcept
    {
        return m_vec2.y;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector2<TInternalType>::x() const noexcept
    {
        return m_vec2.x;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector2<TInternalType>::y() const noexcept
    {
        return m_vec2.y;
    }

    template<typename TInternalType>
    constexpr std::size_t TVector2<TInternalType>::Size() noexcept
    {
        return static_cast<std::size_t>(2);
    }

    template<typename TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::Set(TInternalType x, TInternalType y) noexcept
    {
        m_vec2.x = x;
        m_vec2.y = y;
        return *this;
    }

    template<typename TInternalType>
    TInternalType* TVector2<TInternalType>::InternalDataPointer() noexcept
    {
        return glm::value_ptr(m_vec2);
    }

    template<typename TInternalType>
    const TInternalType* TVector2<TInternalType>::InternalDataPointer() const noexcept
    {
        return glm::value_ptr(m_vec2);
    }

    template<typename TInternalType>
    TInternalType TVector2<TInternalType>::Distance(const TVector2<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        return glm::distance(m_vec2, v.m_vec2);
    }

    template<typename TInternalType>
    TInternalType TVector2<TInternalType>::Distance(const TVector2<TInternalType> &v1,
                                                              const TVector2<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        return glm::distance(v1.m_vec2, v2.m_vec2);
    }

    template<typename TInternalType>
    TInternalType TVector2<TInternalType>::Dot(const TVector2<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(m_vec2, v.m_vec2);
    }

    template<typename TInternalType>
    TInternalType TVector2<TInternalType>::Dot(const TVector2<TInternalType> &v1,
                                               const TVector2<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(v1.m_vec2, v2.m_vec2);
    }

    template<typename TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::FaceForward(const TVector2<TInternalType> &in,
                                                                 const TVector2<TInternalType> &normal,
                                                                 const TVector2<TInternalType> &normal_ref) noexcept
    {
        return TVector2<TInternalType>(glm::faceforward(in.m_vec2, normal.m_vec2, normal_ref.m_vec2));
    }

    template<typename TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Lerp(const TVector2<TInternalType> &v1,
                                                          const TVector2<TInternalType> &v2,
                                                          float t) noexcept
    {
        return TVector2<TInternalType>(glm::mix(v1.m_vec2, v2.m_vec2, t));
    }

    template<typename TInternalType>
    float TVector2<TInternalType>::Magnitude() const noexcept
    {
        if constexpr (std::numeric_limits<TInternalType>::is_iec559)
        {
            return static_cast<float>(glm::length(m_vec2));
        }

        glm::tvec2<float> v(m_vec2.x, m_vec2.y);
        return static_cast<float>(glm::length(v));
    }

    template<typename TInternalType>
    float TVector2<TInternalType>::SquareMagnitude() const noexcept
    {
        return (m_vec2.x * m_vec2.x) + (m_vec2.y * m_vec2.y);
    }

    template<typename TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::Normalize() noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        TInternalType length = glm::length(m_vec2);
        if (length < 0.001F)
        {
            return *this;
        }
        m_vec2 = m_vec2 / length;
        return *this;
    }

    template<typename TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Normalize(const TVector2<TInternalType> &v) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        TInternalType length = glm::length(v.m_vec2);
        if (length < 0.001F)
        {
            return v;
        }
        return TVector2<TInternalType>(v.m_vec2 / length);
    }

    template<typename TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Reflect(const TVector2<TInternalType> &in,
                                                             const TVector2<TInternalType> &normal) noexcept
    {
        return TVector2<TInternalType>(glm::reflect(in.m_vec2, normal.m_vec2));
    }

    template<typename TInternalType>
    TVector2<TInternalType>TVector2<TInternalType>:: Refract(const TVector2<TInternalType> &in,
                                                             const TVector2<TInternalType> &normal,
                                                             TInternalType eta) noexcept
    {
        return TVector2<TInternalType>(glm::refract(in.m_vec2, normal.m_vec2, eta));
    }

    template<typename TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::Scale(const TVector2<TInternalType> &v) noexcept
    {
        m_vec2 *= v.m_vec2;
        return *this;
    }

    template<typename TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Scale(const TVector2<TInternalType> &v1,
                                                           const TVector2<TInternalType> &v2) noexcept
    {
        return TVector2<TInternalType>(v1.m_vec2 * v2.m_vec2);
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector2<TInternalType>& TVector2<TInternalType>::operator+=(const TVector2<TOtherInternalType> &v) noexcept
    {
        m_vec2 += v.m_vec2;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector2<TInternalType>& TVector2<TInternalType>::operator-=(const TVector2<TOtherInternalType> &v) noexcept
    {
        m_vec2 -= v.m_vec2;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector2<TInternalType>& TVector2<TInternalType>::operator*=(TOtherInternalType scalar) noexcept
    {
        m_vec2 *= scalar;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector2<TInternalType>& TVector2<TInternalType>::operator/=(TOtherInternalType scalar) noexcept
    {
        m_vec2 /= scalar;
        return *this;
    }

    template<typename TInternalType>
    constexpr bool TVector2<TInternalType>::operator==(const TVector2<TInternalType> &v) noexcept
    {
        return m_vec2 == v.m_vec2;
    }

    template<typename TInternalType>
    constexpr bool TVector2<TInternalType>::operator!=(const TVector2<TInternalType> &v) noexcept
    {
        return m_vec2 != v.m_vec2;
    }

    template<typename TInternalType>
    constexpr TVector2<TInternalType> operator+(const TVector2<TInternalType> &v) noexcept
    {
        return v;
    }

    template<typename TInternalType>
    constexpr TVector2<TInternalType> operator-(const TVector2<TInternalType> &v) noexcept
    {
        return TVector2<TInternalType>(-v.m_vec2);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator+(const TVector2<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector2<TInternalType>(v.m_vec2 + scalar);
    }

    template<typename TInternalType>
    constexpr TVector2<TInternalType> operator+(const TVector2<TInternalType> &v1, const TVector2<TInternalType> &v2) noexcept
    {
        return TVector2<TInternalType>(v1.m_vec2 + v2.m_vec2);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator+(TOtherInternalType scalar, const TVector2<TInternalType> &v) noexcept
    {
        return TVector2<TInternalType>(scalar + v.m_vec2);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator-(const TVector2<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector2<TInternalType>(v.m_vec2 - scalar);
    }

    template<typename TInternalType>
    constexpr TVector2<TInternalType> operator-(const TVector2<TInternalType> &v1, const TVector2<TInternalType> &v2) noexcept
    {
        return TVector2<TInternalType>(v1.m_vec2 - v2.m_vec2);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator-(TOtherInternalType scalar, const TVector2<TInternalType> &v) noexcept
    {
        return TVector2<TInternalType>(scalar - v.m_vec2);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator*(const TVector2<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector2<TInternalType>(v.m_vec2 * scalar);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator*(TOtherInternalType scalar, const TVector2<TInternalType> &v) noexcept
    {
        return TVector2<TInternalType>(scalar * v.m_vec2);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector2<TInternalType> operator/(const TVector2<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector2<TInternalType>(v.m_vec2 / scalar);
    }

    template<typename TInternalType>
    std::string TVector2<TInternalType>::ToString() const try
    {
        return "[" + std::to_string(m_vec2.x) + ", " + std::to_string(m_vec2.y) + "]";
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    std::ostream& operator<<(std::ostream &os, const TVector2<TInternalType> &v) try
    {
        return os << "[" << v.m_vec2.x << ", " << v.m_vec2.y << "]";
    }
    CATCH_RETHROW_EXCEPTIONS
}
