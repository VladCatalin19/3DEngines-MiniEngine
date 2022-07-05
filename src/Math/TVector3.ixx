
#include <glm/glm.hpp>                          // glm::tvec3, std::numeric_limits, glm::cross, glm::distance,
                                                // glm::dot, glm::faceforward, glm::mix, glm::length,
                                                // glm::normalize, glm::reflect, glm::refract
#include <glm/gtc/type_ptr.hpp>                 // glm::value_ptr
#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <memory>               // std::move
#include <ostream>              // std::ostream
#include <stdexcept>            // std::out_of_range
#include <string>               // std::string, std::to_string

namespace MG3TR
{
    template<typename TInternalType>
    constexpr TVector3<TInternalType>::TVector3(const glm::tvec3<TInternalType> &v)
        : m_vec3(v)
    {}

    template<typename TInternalType>
    constexpr TVector3<TInternalType>::TVector3() noexcept
        : m_vec3(static_cast<TInternalType>(0), static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {}

    template<typename TInternalType>
    constexpr TVector3<TInternalType>::TVector3(TInternalType x, TInternalType y, TInternalType z) noexcept
        : m_vec3(x, y, z)
    {}

    template<typename TInternalType>
    constexpr TVector3<TInternalType>::TVector3(const TVector3<TInternalType> &v) noexcept
        : m_vec3(v.m_vec3)
    {}

    template<typename TInternalType>
    constexpr TVector3<TInternalType>::TVector3(TVector3<TInternalType> &&v) noexcept
        : m_vec3(std::move(v.m_vec3))
    {}

    template<typename TInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::operator=(const TVector3<TInternalType> &v) noexcept
    {
        m_vec3 = v.m_vec3;
        return *this;
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::operator=(TVector3<TInternalType> &&v) noexcept
    {
        m_vec3 = std::move(v.m_vec3);
        return *this;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector3<TInternalType>::operator[](std::size_t index) noexcept
    {
        return m_vec3[index];
    }

    template<typename TInternalType>
    constexpr const TInternalType& TVector3<TInternalType>::operator[](std::size_t index) const noexcept
    {
        return m_vec3[index];
    }

    template<typename TInternalType>
    TInternalType& TVector3<TInternalType>::at(std::size_t index) try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid vector3 subscript");
        }
        return m_vec3[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    const TInternalType& TVector3<TInternalType>::at(std::size_t index) const try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid vector3 subscript");
        }
        return m_vec3[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    constexpr TInternalType& TVector3<TInternalType>::x() noexcept
    {
        return m_vec3.x;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector3<TInternalType>::y() noexcept
    {
        return m_vec3.y;
    }

    template<typename TInternalType>
    constexpr TInternalType& TVector3<TInternalType>::z() noexcept
    {
        return m_vec3.z;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector3<TInternalType>::x() const noexcept
    {
        return m_vec3.x;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector3<TInternalType>::y() const noexcept
    {
        return m_vec3.y;
    }

    template<typename TInternalType>
    constexpr TInternalType TVector3<TInternalType>::z() const noexcept
    {
        return m_vec3.z;
    }

    template<typename TInternalType>
    constexpr std::size_t TVector3<TInternalType>::Size() noexcept
    {
        return static_cast<std::size_t>(3);
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::Set(TInternalType x, TInternalType y, TInternalType z) noexcept
    {
        m_vec3.x = x;
        m_vec3.y = y;
        m_vec3.z = z;
        return *this;
    }

    template<typename TInternalType>
    TInternalType* TVector3<TInternalType>::InternalDataPointer() noexcept
    {
        return glm::value_ptr(m_vec3);
    }

    template<typename TInternalType>
    const TInternalType* TVector3<TInternalType>::InternalDataPointer() const noexcept
    {
        return glm::value_ptr(m_vec3);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Cross(const TVector3<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");
        return TVector3<TInternalType>(glm::cross(m_vec3, v.m_vec3));
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Cross(const TVector3<TInternalType> &v1,
                                                           const TVector3<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");
        return TVector3<TInternalType>(glm::cross(v1.m_vec3, v2.m_vec3));
    }

    template<typename TInternalType>
    TInternalType TVector3<TInternalType>::Distance(const TVector3<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        return glm::distance(m_vec3, v.m_vec3);
    }

    template<typename TInternalType>
    TInternalType TVector3<TInternalType>::Distance(const TVector3<TInternalType> &v1,
                                                    const TVector3<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        return glm::distance(v1.m_vec3, v2.m_vec3);
    }

    template<typename TInternalType>
    TInternalType TVector3<TInternalType>::Dot(const TVector3<TInternalType> &v) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(m_vec3, v.m_vec3);
    }

    template<typename TInternalType>
    TInternalType TVector3<TInternalType>::Dot(const TVector3<TInternalType> &v1,
                                               const TVector3<TInternalType> &v2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(v1.m_vec3, v2.m_vec3);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::FaceForward(const TVector3<TInternalType> &in,
                                                                 const TVector3<TInternalType> &normal,
                                                                 const TVector3 &normal_ref) noexcept
    {
        return TVector3<TInternalType>(glm::faceforward(in.m_vec3, normal.m_vec3, normal_ref.vec3));
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Lerp(const TVector3<TInternalType> &v1,
                                                          const TVector3<TInternalType> &v2,
                                                          float t) noexcept
    {
        return TVector3<TInternalType>(glm::mix(v1.m_vec3, v2.m_vec3, t));
    }

    template<typename TInternalType>
    float TVector3<TInternalType>::Magnitude() const noexcept
    {
        if constexpr (std::numeric_limits<TInternalType>::is_iec559)
        {
            return static_cast<float>(glm::length(m_vec3));
        }

        glm::tvec3<float> v(m_vec3.x, m_vec3.y, m_vec3.z);
        return static_cast<float>(glm::length(v));
    }

    template<typename TInternalType>
    float TVector3<TInternalType>::SquareMagnitude() const noexcept
    {
        return (m_vec3.x * m_vec3.x) + (m_vec3.y * m_vec3.y) + (m_vec3.z * m_vec3.z);
    }

    template<typename TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::Normalize() noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        TInternalType length = glm::length(m_vec3);
        if (length < 0.001F)
        {
            return *this;
        }
        m_vec3 = m_vec3 / length;
        return *this;
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Normalize(const TVector3<TInternalType> &v) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        TInternalType length = glm::length(v.m_vec3);
        if (length < 0.001F)
        {
            return v;
        }
        return TVector3<TInternalType>(v.m_vec3 / length);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Reflect(const TVector3<TInternalType> &in,
                                                             const TVector3<TInternalType> &normal) noexcept
    {
        return TVector3<TInternalType>(glm::reflect(in.m_vec3, normal.m_vec3));
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Refract(const TVector3<TInternalType> &in,
                                                             const TVector3<TInternalType> &normal,
                                                             TInternalType eta) noexcept
    {
        return TVector3<TInternalType>(glm::refract(in.m_vec3, normal.m_vec3, eta));
    }

    template<typename TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::Scale(const TVector3<TInternalType> &v) noexcept
    {
        m_vec3 *= v.m_vec3;
        return *this;
    }

    template<typename TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Scale(const TVector3<TInternalType> &v1,
                                                           const TVector3<TInternalType> &v2) noexcept
    {
        return TVector3<TInternalType>(v1.m_vec3 * v2.m_vec3);
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::operator+=(const TVector3<TOtherInternalType> &v) noexcept
    {
        m_vec3 += v.m_vec3;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::operator-=(const TVector3<TOtherInternalType> &v) noexcept
    {
        m_vec3 -= v.m_vec3;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::operator*=(TOtherInternalType scalar) noexcept
    {
        m_vec3 *= scalar;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TVector3<TInternalType>& TVector3<TInternalType>::operator/=(TOtherInternalType scalar) noexcept
    {
        m_vec3 /= scalar;
        return *this;
    }

    template<typename TInternalType>
    constexpr bool TVector3<TInternalType>::operator==(const TVector3<TInternalType> &v) noexcept
    {
        return m_vec3 == v.m_vec3;
    }

    template<typename TInternalType>
    constexpr bool TVector3<TInternalType>::operator!=(const TVector3<TInternalType> &v) noexcept
    {
        return m_vec3 != v.m_vec3;
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType> operator+(const TVector3<TInternalType> &v) noexcept
    {
        return v;
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType> operator-(const TVector3<TInternalType> &v) noexcept
    {
        return TVector3<TInternalType>(-v.m_vec3);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator+(const TVector3<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector3<TInternalType>(v.m_vec3 + scalar);
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType> operator+(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2) noexcept
    {
        return TVector3<TInternalType>(v1.m_vec3 + v2.m_vec3);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator+(TOtherInternalType scalar, const TVector3<TInternalType> &v) noexcept
    {
        return TVector3<TInternalType>(scalar + v.m_vec3);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator-(const TVector3<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector3<TInternalType>(v.m_vec3 - scalar);
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType> operator-(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2) noexcept
    {
        return TVector3<TInternalType>(v1.m_vec3 - v2.m_vec3);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator-(TOtherInternalType scalar, const TVector3<TInternalType> &v) noexcept
    {
        return TVector3<TInternalType>(scalar - v.m_vec3);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator*(const TVector3<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector3<TInternalType>(v.m_vec3 * scalar);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator*(TOtherInternalType scalar, const TVector3<TInternalType> &v) noexcept
    {
        return TVector3<TInternalType>(scalar * v.m_vec3);
    }

    template<typename TInternalType, typename TOtherInternalType>
    constexpr TVector3<TInternalType> operator/(const TVector3<TInternalType> &v, TOtherInternalType scalar) noexcept
    {
        return TVector3<TInternalType>(v.m_vec3 / scalar);
    }

    template<typename TInternalType>
    std::string TVector3<TInternalType>::ToString() const try
    {
        return "[" + std::to_string(m_vec3.x) + ", " + std::to_string(m_vec3.y) + ", " + std::to_string(m_vec3.z) + "]";
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    std::ostream& operator<<(std::ostream &os, const TVector3<TInternalType> &v) try
    {
        return os << "[" << v.m_vec3.x << ", " << v.m_vec3.y << ", " << v.m_vec3.z << "]";
    }
    CATCH_RETHROW_EXCEPTIONS
}