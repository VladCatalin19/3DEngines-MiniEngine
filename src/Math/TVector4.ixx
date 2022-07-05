
#include <glm/glm.hpp>                          // glm::tvec4, std::numeric_limits, glm::distance, glm::dot,
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
    constexpr TVector4<TInternalType>::TVector4(const glm::tvec4<TInternalType> &v)
        : m_vec4(v)
    {}

    template<typename TInternalType>
    constexpr TVector4<TInternalType>::TVector4() noexcept
        : m_vec4(static_cast<TInternalType>(0), static_cast<TInternalType>(0),
                 static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {}

    template<typename TInternalType>
    constexpr TVector4<TInternalType>::TVector4(TInternalType x, TInternalType y, TInternalType z, TInternalType w) noexcept
        : m_vec4(x, y, z, w)
    {}

    template<typename TInternalType>
    constexpr TVector4<TInternalType>::TVector4(const TVector3<TInternalType> &v, TInternalType w) noexcept
        : m_vec4(v.x(), v.y(), v.z(), w)
    {}

    template<typename TInternalType>
    constexpr TVector4<TInternalType>::TVector4(const TVector4<TInternalType> &v) noexcept
        : m_vec4(v.m_vec4)
    {}

    template<typename TInternalType>
    constexpr TVector4<TInternalType>::TVector4(TVector4<TInternalType> &&v) noexcept
        : m_vec4(std::move(v.m_vec4))
    {}

    template<typename TInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::operator=(const TVector4<TInternalType> &v) noexcept
    {
        m_vec4 = v.m_vec4;
        return *this;
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::operator=(TVector4<TInternalType> &&v) noexcept
    {
        m_vec4 = std::move(v.m_vec4);
        return *this;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector4<TInternalType>::operator[](std::size_t index) noexcept
    {
        return m_vec4[index];
    }

    template<typename TInternalType>
    constexpr const TInternalType& TVector4<TInternalType>::operator[](std::size_t index) const noexcept
    {
        return m_vec4[index];
    }

    template<typename TInternalType>
    TInternalType& TVector4<TInternalType>::at(std::size_t index) try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid vector4 subscript");
        }
        return m_vec4[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    const TInternalType& TVector4<TInternalType>::at(std::size_t index) const try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid vector4 subscript");
        }
        return m_vec4[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    constexpr TInternalType& TVector4<TInternalType>::x() noexcept
    {
        return m_vec4.x;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector4<TInternalType>::y() noexcept
    {
        return m_vec4.y;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector4<TInternalType>::z() noexcept
    {
        return m_vec4.z;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector4<TInternalType>::w() noexcept
    {
        return m_vec4.w;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector4<TInternalType>::x() const noexcept
    {
        return m_vec4.x;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector4<TInternalType>::y() const noexcept
    {
        return m_vec4.y;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector4<TInternalType>::z() const noexcept
    {
        return m_vec4.z;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector4<TInternalType>::w() const noexcept
    {
        return m_vec4.w;
    }

    template<typename TInternalType>
    constexpr std::size_t TVector4<TInternalType>::Size() noexcept
    {
        return static_cast<std::size_t>(4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::Set(TInternalType x, TInternalType y,
                                                                    TInternalType z, TInternalType w) noexcept
    {
        m_vec4.x = x;
        m_vec4.y = y;
        m_vec4.z = z;
        m_vec4.w = w;
        return *this;
    }

    template<typename TInternalType>
    TInternalType* TVector4<TInternalType>::InternalDataPointer() noexcept
    {
        return glm::value_ptr(m_vec4);
    }

    template<typename TInternalType>
    const TInternalType* TVector4<TInternalType>::InternalDataPointer() const noexcept
    {
        return glm::value_ptr(m_vec4);
    }

    template<typename TInternalType>
    TInternalType TVector4<TInternalType>::Distance(const TVector4<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        return glm::distance(m_vec4, v.m_vec4);
    }

    template<typename TInternalType>
    TInternalType TVector4<TInternalType>::Distance(const TVector4<TInternalType> &v1,
                                                              const TVector4<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        return glm::distance(v1.m_vec4, v2.m_vec4);
    }

    template<typename TInternalType>
    TInternalType TVector4<TInternalType>::Dot(const TVector4<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(m_vec4, v.m_vec4);
    }

    template<typename TInternalType>
    TInternalType TVector4<TInternalType>::Dot(const TVector4<TInternalType> &v1,
                                               const TVector4<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(v1.m_vec4, v2.m_vec4);
    }

    template<typename TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::FaceForward(const TVector4<TInternalType> &in,
                                                                 const TVector4<TInternalType> &normal,
                                                                 const TVector4<TInternalType> &normal_ref) noexcept
    {
        return TVector4<TInternalType>(glm::faceforward(in.m_vec4, normal.m_vec4, normal_ref.m_vec4));
    }

    template<typename TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Lerp(const TVector4<TInternalType> &v1,
                                                          const TVector4<TInternalType> &v2,
                                                          float t) noexcept
    {
        return TVector4<TInternalType>(glm::mix(v1.m_vec4, v2.m_vec4, t));
    }

    template<typename TInternalType>
    float TVector4<TInternalType>::Magnitude() const noexcept
    {
        if constexpr (std::numeric_limits<TInternalType>::is_iec559)
        {
            return static_cast<float>(glm::length(m_vec4));
        }

        glm::tvec4<float> v(m_vec4.x, m_vec4.y, m_vec4.z, m_vec4.w);
        return static_cast<float>(glm::length(v));
    }

    template<typename TInternalType>
    float TVector4<TInternalType>::SquareMagnitude() const noexcept
    {
        return (m_vec4.x * m_vec4.x) + (m_vec4.y * m_vec4.y) + (m_vec4.z * m_vec4.z) + (m_vec4.w * m_vec4.w);
    }

    template<typename TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::Normalize() noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        TInternalType length = glm::length(m_vec4);
        if (length < 0.001F)
        {
            return *this;
        }
        m_vec4 = m_vec4 / length;
        return *this;
    }

    template<typename TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Normalize(const TVector4<TInternalType> &v) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        TInternalType length = glm::length(v.m_vec4);
        if (length < 0.001F)
        {
            return v;
        }
        return TVector4<TInternalType>(v.m_vec4 / length);
    }

    template<typename TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Reflect(const TVector4<TInternalType> &in,
                                                             const TVector4<TInternalType> &normal) noexcept
    {
        return TVector4(glm::reflect(in.m_vec4, normal.m_vec4));
    }

    template<typename TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Refract(const TVector4<TInternalType> &in,
                                                             const TVector4<TInternalType> &normal,
                                                             TInternalType eta) noexcept
    {
        return TVector4<TInternalType>(glm::refract(in.m_vec4, normal.m_vec4, eta));
    }

    template<typename TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::Scale(const TVector4<TInternalType> &v) noexcept
    {
        m_vec4 *= v.m_vec4;
        return *this;
    }

    template<typename TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Scale(const TVector4<TInternalType> &v1,
                                                           const TVector4<TInternalType> &v2) noexcept
    {
        return TVector4<TInternalType>(v1.m_vec4 * v2.m_vec4);
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::operator+=(const TVector4<TOtherInternalType> &v) noexcept
    {
        m_vec4 += v.m_vec4;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::operator-=(const TVector4<TOtherInternalType> &v) noexcept
    {
        m_vec4 -= v.m_vec4;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::operator*=(TOtherInternalType scalar) noexcept
    {
        m_vec4 *= scalar;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector4<TInternalType>& TVector4<TInternalType>::operator/=(TOtherInternalType scalar) noexcept
    {
        m_vec4 /= scalar;
        return *this;
    }

    template<typename TInternalType>
    constexpr bool TVector4<TInternalType>::operator==(const TVector4<TInternalType> &v) noexcept
    {
        return m_vec4 == v.m_vec4;
    }

    template<typename TInternalType>
    constexpr bool TVector4<TInternalType>::operator!=(const TVector4<TInternalType> &v) noexcept
    {
        return m_vec4 != v.m_vec4;
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator+(const TVector4<TInternalType> &v) noexcept
    {
        return v;
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator-(const TVector4<TInternalType> &v) noexcept
    {
        return TVector4<TInternalType>(-v.m_vec4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator+(const TVector4<TInternalType> &v, TInternalType scalar) noexcept
    {
        return TVector4<TInternalType>(v.m_vec4 + scalar);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator+(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2) noexcept
    {
        return TVector4<TInternalType>(v1.m_vec4 + v2.m_vec4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator+(TInternalType scalar, const TVector4<TInternalType> &v) noexcept
    {
        return TVector4<TInternalType>(scalar + v.m_vec4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator-(const TVector4<TInternalType> &v, TInternalType scalar) noexcept
    {
        return TVector4<TInternalType>(v.m_vec4 - scalar);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator-(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2) noexcept
    {
        return TVector4<TInternalType>(v1.m_vec4 - v2.m_vec4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator-(TInternalType scalar, const TVector4<TInternalType> &v) noexcept
    {
        return TVector4<TInternalType>(scalar - v.m_vec4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator*(const TVector4<TInternalType> &v, TInternalType scalar) noexcept
    {
        return TVector4<TInternalType>(v.m_vec4 * scalar);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator*(TInternalType scalar, const TVector4<TInternalType> &v) noexcept
    {
        return TVector4<TInternalType>(scalar * v.m_vec4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator/(const TVector4<TInternalType> &v, TInternalType scalar) noexcept
    {
        return TVector4<TInternalType>(v.m_vec4 / scalar);
    }

    template<typename TInternalType>
    std::string TVector4<TInternalType>::ToString() const try
    {
        return "[" + std::to_string(m_vec4.x) + ", " + std::to_string(m_vec4.y) + ", " + std::to_string(m_vec4.z)
                + ", " + std::to_string(m_vec4.w) + "]";
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    std::ostream& operator<<(std::ostream &os, const TVector4<TInternalType> &v) try
    {
        return os << "[" << v.m_vec4.x << ", " << v.m_vec4.y << ", " << v.m_vec4.z << ", " << v.m_vec4.w << "]";
    }
    CATCH_RETHROW_EXCEPTIONS
}