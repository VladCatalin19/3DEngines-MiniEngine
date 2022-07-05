
#include "glm/ext/quaternion_common.hpp"
#include <glm/glm.hpp>                          // glm::tvec3, std::numeric_limits, 
#include <glm/gtc/quaternion.hpp>               // glm::tquat, glm::angleAxis, glm::angle, glm::axis,
                                                // glm::cross, glm::dot, glm::inverse, glm::lerp,
                                                // glm::normalize,  glm::slerp
#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <memory>               // std::move
#include <ostream>              // std::ostream
#include <stdexcept>            // std::out_of_range
#include <string>               // std::string, std::to_string

namespace MG3TR
{
    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(const glm::tquat<TInternalType> &quat) noexcept
        : m_quat(quat)
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion() noexcept
        : m_quat(static_cast<TInternalType>(1), static_cast<TInternalType>(0),
                 static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(TInternalType s, const TVector3<TInternalType> &v) noexcept
        : m_quat(s, v.x(), v.y(), v.z())
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(TInternalType w, TInternalType x,
                                                      TInternalType y, TInternalType z) noexcept
        : m_quat(w, x, y, z)
    {}

    // from and to must be normalized
    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(const TVector3<TInternalType> &from,
                                                      const TVector3<TInternalType> &to) noexcept
        : m_quat(glm::tvec3<TInternalType>(from.x(), from.y(), from.z()),
                 glm::tvec3<TInternalType>(to.x(), to.y(), to.z()))
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(const TVector3<TInternalType> &euler_angles) noexcept
        : m_quat(glm::tvec3<TInternalType>(euler_angles.x(), euler_angles.y(), euler_angles.z()))
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType> TQuaternion<TInternalType>::FromAngleAxis(TInternalType angle,
                                                                                   const TVector3<TInternalType> &axis) noexcept
    {
        return TQuaternion<TInternalType>(glm::angleAxis(angle, axis));
    }

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(const TQuaternion<TInternalType> &q) noexcept
        : m_quat(q.m_quat)
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>::TQuaternion(TQuaternion<TInternalType> &&q) noexcept
        : m_quat(std::move(q.m_quat))
    {}

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator=(const TQuaternion<TInternalType> &q) noexcept
    {
        m_quat = q.m_quat;
        return *this;
    }

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator=(TQuaternion<TInternalType> &&q) noexcept
    {
        m_quat = std::move(q.m_quat);
        return *this;
    }

    template<typename TInternalType>
    constexpr TInternalType& TQuaternion<TInternalType>::operator[](std::size_t index) noexcept
    {
        return m_quat[index];
    }

    template<typename TInternalType>
    constexpr const TInternalType& TQuaternion<TInternalType>::operator[](std::size_t index) const noexcept
    {
        return m_quat[index];
    }

    template<typename TInternalType>
    TInternalType& TQuaternion<TInternalType>::at(std::size_t index) try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid quaternion subscript");
        }
        return m_quat[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    const TInternalType& TQuaternion<TInternalType>::at(std::size_t index) const try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid quaternion subscript");
        }
        return m_quat[index];
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    constexpr TInternalType& TQuaternion<TInternalType>::w() noexcept
    {
        return m_quat.w;
    }

    template<typename TInternalType>
    constexpr TInternalType& TQuaternion<TInternalType>::x() noexcept
    {
        return m_quat.x;
    }

    template<typename TInternalType>
    constexpr TInternalType& TQuaternion<TInternalType>::y() noexcept
    {
        return m_quat.y;
    }

    template<typename TInternalType>
    constexpr TInternalType& TQuaternion<TInternalType>::z() noexcept
    {
        return m_quat.z;
    }

    template<typename TInternalType>
    constexpr TInternalType TQuaternion<TInternalType>::w() const noexcept
    {
        return m_quat.w;
    }

    template<typename TInternalType>
    constexpr TInternalType TQuaternion<TInternalType>::x() const noexcept
    {
        return m_quat.x;
    }

    template<typename TInternalType>
    constexpr TInternalType TQuaternion<TInternalType>::y() const noexcept
    {
        return m_quat.y;
    }

    template<typename TInternalType>
    constexpr TInternalType TQuaternion<TInternalType>::z() const noexcept
    {
        return m_quat.z;
    }

    template<typename TInternalType>
    constexpr std::size_t TQuaternion<TInternalType>::Size() noexcept
    {
        return static_cast<std::size_t>(4);
    }

    template<typename TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Set(TInternalType w, TInternalType x,
                                                                TInternalType y, TInternalType z) noexcept
    {
        m_quat.w = w;
        m_quat.x = x;
        m_quat.y = y;
        m_quat.z = z;
        return *this;
    }

    template<typename TInternalType>
    TInternalType TQuaternion<TInternalType>::Angle() const noexcept
    {
        return glm::angle(m_quat);
    }

    template<typename TInternalType>
    TInternalType TQuaternion<TInternalType>::Angle(const TQuaternion<TInternalType> &q) noexcept
    {
        return glm::angle(q.m_quat);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::Axis() const noexcept
    {
        auto res = glm::axis(m_quat);
        return TVector3<TInternalType>(res.x, res.y, res.z);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::Axis(const TQuaternion<TInternalType> &q) noexcept
    {
        auto res = glm::axis(q.m_quat);
        return TVector3<TInternalType>(res.x, res.y, res.z);
    }

    template<typename TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Conjugate()
    {
        m_quat = glm::conjugate(m_quat);
        return *this;
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Conjugate(TQuaternion<TInternalType> &q)
    {
        auto quat = glm::conjugate(q.m_quat);
        return TQuaternion<TInternalType>(quat);
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Cross(const TQuaternion<TInternalType> &q) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");
        return TQuaternion<TInternalType>(glm::cross(m_quat, q.m_quat));
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Cross(const TQuaternion<TInternalType> &q1,
                                                                 const TQuaternion<TInternalType> &q2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");
        return TQuaternion<TInternalType>(glm::cross(q1.m_quat, q2.m_quat));
    }

    template<typename TInternalType>
    TInternalType TQuaternion<TInternalType>::Dot(const TQuaternion<TInternalType> &q) const noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(m_quat, q.m_quat);
    }

    template<typename TInternalType>
    TInternalType TQuaternion<TInternalType>::Dot(const TQuaternion<TInternalType> &q1,
                                                  const TQuaternion<TInternalType> &q2) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        return glm::dot(q1.m_quat, q2.m_quat);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::EulerAngles() const noexcept
    {
        glm::tvec3<TInternalType> euler_angles = glm::eulerAngles(m_quat);
        return TVector3<TInternalType>(euler_angles.x, euler_angles.y, euler_angles.z);
    }

    template<typename TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::EulerAngles(const TQuaternion<TInternalType> &q) noexcept
    {
        glm::tvec3<TInternalType> euler_angles = glm::eulerAngles(q.m_quat);
        return TVector3<TInternalType>(euler_angles.x, euler_angles.y, euler_angles.z);
    }

    template<typename TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Inverse() noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Inverse' accepts only floating-point inputs");
        m_quat = glm::inverse(m_quat);
        return *this;
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Inverse(const TQuaternion<TInternalType> &q) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Inverse' accepts only floating-point inputs");
        return TQuaternion<TInternalType>(glm::inverse(q.m_quat));
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Lerp(const TQuaternion<TInternalType> &q1,
                                                                const TQuaternion<TInternalType> &q2,
                                                                float t) noexcept
    {
        return TQuaternion<TInternalType>(glm::lerp(q1.m_quat, q2.m_quat, t));
    }

    template<typename TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Normalize() noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        m_quat = glm::normalize(m_quat);
        return *this;
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Normalize(const TQuaternion<TInternalType> &q) noexcept
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        return TQuaternion<TInternalType>(glm::normalize(q.m_quat));
    }

    template<typename TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Slerp(const TQuaternion<TInternalType> &q1,
                                                                 const TQuaternion<TInternalType> &q2,
                                                                 float t) noexcept
    {
        return TQuaternion<TInternalType>(glm::slerp(q1.m_quat, q2.m_quat, t));
    }

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator*=(const TQuaternion<TInternalType> &q) noexcept
    {
        m_quat *= q.m_quat;
        return *this;
    }

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator*=(const TVector3<TInternalType> &v) noexcept
    {
        m_quat *= glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        return *this;
    }

    template<typename TInternalType>
    constexpr TQuaternion<TInternalType> operator*(const TQuaternion<TInternalType> &q1, const TQuaternion<TInternalType> &q2) noexcept
    {
        return TQuaternion<TInternalType>(q1.m_quat * q2.m_quat);
    }

    template<typename TInternalType>
    constexpr TVector3<TInternalType> operator*(const TQuaternion<TInternalType> &q, const TVector3<TInternalType> &v) noexcept
    {
        auto vec3 = q.m_quat * glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        return TVector3<TInternalType>(vec3.x, vec3.y, vec3.z);
    }

    template<typename TInternalType>
    std::string TQuaternion<TInternalType>::ToString() const try
    {
        return "[" + std::to_string(m_quat.w) + ", " + std::to_string(m_quat.x) + ", "
                + std::to_string(m_quat.y) + ", " + std::to_string(m_quat.z) + "]";
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    std::ostream& operator<<(std::ostream &os, const TQuaternion<TInternalType> &q) try
    {
        return os << "[" << q.w() << ", " << q.x() << ", " << q.y() << ", " << q.z() << "]";
    }
    CATCH_RETHROW_EXCEPTIONS
}