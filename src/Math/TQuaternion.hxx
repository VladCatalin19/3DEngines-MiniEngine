#ifndef M3GTR_SRC_MATH_TQUATERNION_HXX_INCLUDED
#define M3GTR_SRC_MATH_TQUATERNION_HXX_INCLUDED

#include "TVector3.hxx"
#include "Utils/ExceptionWithStacktrace.hpp"

#include <Utils/ExceptionWithStacktrace.hpp>

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

#include <format>
#include <ostream>
#include <string>

namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    class TQuaternion
    {
    private:
        glm::tquat<TInternalType> m_quat;

        TQuaternion(const glm::tquat<TInternalType> &quat);

    public:
        TQuaternion();
        TQuaternion(const TInternalType s, const TVector3<TInternalType> &v);
        TQuaternion(const TInternalType w, TInternalType x, TInternalType y, TInternalType z);
        // from and to must be normalized
        TQuaternion(const TVector3<TInternalType> &from, const TVector3<TInternalType> &to);
        TQuaternion(const TVector3<TInternalType> &euler_angles);
        static TQuaternion<TInternalType> FromAngleAxis(const TInternalType angle,
                                                        const TVector3<TInternalType> &axis);
        TQuaternion(const TQuaternion<TInternalType> &q);
        TQuaternion(TQuaternion<TInternalType> &&q);

        TQuaternion<TInternalType>& operator=(const TQuaternion<TInternalType> &q);
        TQuaternion<TInternalType>& operator=(TQuaternion<TInternalType> &&q);

        TInternalType& operator[](const std::size_t index);
        const TInternalType& operator[](const std::size_t index) const;

        TInternalType& at(const std::size_t index);
        const TInternalType& at(const std::size_t index) const;

        TInternalType& w();
        TInternalType& x();
        TInternalType& y();
        TInternalType& z();

        TInternalType w() const;
        TInternalType x() const;
        TInternalType y() const;
        TInternalType z() const;

        static std::size_t Size();

        TQuaternion<TInternalType>& Set(const TInternalType w, const TInternalType x, const TInternalType y, const TInternalType z);

        TInternalType Angle() const;
        static TInternalType Angle(const TQuaternion<TInternalType> &q);

        TVector3<TInternalType> Axis() const;
        static TVector3<TInternalType> Axis(const TQuaternion<TInternalType> &q);

        TQuaternion<TInternalType>& Conjugate();
        static TQuaternion<TInternalType> Conjugate(const TQuaternion<TInternalType> &q);

        TQuaternion<TInternalType> Cross(const TQuaternion<TInternalType> &q) const;
        static TQuaternion<TInternalType> Cross(const TQuaternion<TInternalType> &q1,
                                                const TQuaternion<TInternalType> &q2);

        TInternalType Dot(const TQuaternion<TInternalType> &q) const;
        static TInternalType Dot(const TQuaternion<TInternalType> &q1,
                                 const TQuaternion<TInternalType> &q2);

        TVector3<TInternalType> EulerAngles() const;
        static TVector3<TInternalType> EulerAngles(const TQuaternion<TInternalType> &q);

        TQuaternion<TInternalType>& Inverse();
        static TQuaternion<TInternalType> Inverse(const TQuaternion<TInternalType> &q);

        static TQuaternion<TInternalType> Lerp(const TQuaternion<TInternalType> &q1,
                                               const TQuaternion<TInternalType> &q2,
                                               const float t);

        TQuaternion<TInternalType>& Normalize();
        static TQuaternion<TInternalType> Normalize(const TQuaternion<TInternalType> &q);

        static TQuaternion<TInternalType> Slerp(const TQuaternion<TInternalType> &q1,
                                                const TQuaternion<TInternalType> &q2,
                                                const float t);

        TQuaternion<TInternalType>& operator*=(const TQuaternion<TInternalType> &q);
        TQuaternion<TInternalType>& operator*=(const TVector3<TInternalType> &v);

        template<TNumericalConcept TInternal>
        friend TQuaternion<TInternal> operator*(const TQuaternion<TInternal> &q1,
                                                const TQuaternion<TInternal> &q2);
        template<TNumericalConcept TInternal>
        friend TVector3<TInternal> operator*(const TQuaternion<TInternal> &q,
                                             const TVector3<TInternal> &v);

        std::string ToString() const;
        template<TNumericalConcept TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TQuaternion<TInternal> &q);
    };
}

// Implementation
namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(const glm::tquat<TInternalType> &quat)
        : m_quat(quat)
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion()
        : m_quat(static_cast<TInternalType>(1), static_cast<TInternalType>(0),
                 static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(const TInternalType s, const TVector3<TInternalType> &v)
        : m_quat(s, v.x(), v.y(), v.z())
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(const TInternalType w, const TInternalType x,
                                            const TInternalType y, const TInternalType z)
        : m_quat(w, x, y, z)
    {

    }

    // from and to must be normalized
    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(const TVector3<TInternalType> &from,
                                            const TVector3<TInternalType> &to)
        : m_quat(glm::tvec3<TInternalType>(from.x(), from.y(), from.z()),
                 glm::tvec3<TInternalType>(to.x(), to.y(), to.z()))
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(const TVector3<TInternalType> &euler_angles)
        : m_quat(glm::tvec3<TInternalType>(euler_angles.x(), euler_angles.y(), euler_angles.z()))
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::FromAngleAxis(const TInternalType angle,
                                                                         const TVector3<TInternalType> &axis)
    {
        const auto angleAxis = glm::angleAxis(angle, axis);
        TQuaternion<TInternalType> q(angleAxis);
        return q;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(const TQuaternion<TInternalType> &q)
        : m_quat(q.m_quat)
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>::TQuaternion(TQuaternion<TInternalType> &&q)
        : m_quat(std::move(q.m_quat))
    {

    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator=(const TQuaternion<TInternalType> &q)
    {
        m_quat = q.m_quat;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator=(TQuaternion<TInternalType> &&q)
    {
        m_quat = std::move(q.m_quat);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TQuaternion<TInternalType>::operator[](const std::size_t index)
    {
        TInternalType& value = m_quat[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TQuaternion<TInternalType>::operator[](const std::size_t index) const
    {
        const TInternalType& value = m_quat[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TQuaternion<TInternalType>::at(const std::size_t index)
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid quaternion subscript.", index);
            throw ExceptionWithStacktrace(error);
        }

        TInternalType& value = m_quat[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TQuaternion<TInternalType>::at(const std::size_t index) const
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid quaternion subscript.", index);
            throw ExceptionWithStacktrace(error);
        }

        const TInternalType& value = m_quat[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TQuaternion<TInternalType>::w()
    {
        return m_quat.w;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TQuaternion<TInternalType>::x()
    {
        return m_quat.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TQuaternion<TInternalType>::y()
    {
        return m_quat.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TQuaternion<TInternalType>::z()
    {
        return m_quat.z;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::w() const
    {
        return m_quat.w;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::x() const
    {
        return m_quat.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::y() const
    {
        return m_quat.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::z() const
    {
        return m_quat.z;
    }

    template<TNumericalConcept TInternalType>
    std::size_t TQuaternion<TInternalType>::Size()
    {
        return static_cast<std::size_t>(4);
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Set(const TInternalType w, const TInternalType x,
                                                                const TInternalType y, const TInternalType z)
    {
        m_quat.w = w;
        m_quat.x = x;
        m_quat.y = y;
        m_quat.z = z;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::Angle() const
    {
        const TInternalType angle = glm::angle(m_quat);
        return angle;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::Angle(const TQuaternion<TInternalType> &q)
    {
        const TInternalType angle = glm::angle(q.m_quat);
        return angle;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::Axis() const
    {
        const auto res = glm::axis(m_quat);
        const TVector3<TInternalType> axis(res.x, res.y, res.z);
        return axis;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::Axis(const TQuaternion<TInternalType> &q)
    {
        const auto res = glm::axis(q.m_quat);
        const TVector3<TInternalType> axis(res.x, res.y, res.z);
        return axis;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Conjugate()
    {
        m_quat = glm::conjugate(m_quat);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Conjugate(const TQuaternion<TInternalType> &q)
    {
        const auto quat = glm::conjugate(q.m_quat);
        const TQuaternion<TInternalType> res(quat);
        return res;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Cross(const TQuaternion<TInternalType> &q) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");

        const auto cross = glm::cross(m_quat, q.m_quat);
        const TQuaternion<TInternalType> res(cross);
        return res;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Cross(const TQuaternion<TInternalType> &q1,
                                                                 const TQuaternion<TInternalType> &q2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");

        const auto cross = glm::cross(q1.m_quat, q2.m_quat);
        const TQuaternion<TInternalType> res(cross);
        return res;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::Dot(const TQuaternion<TInternalType> &q) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        
        const TInternalType dot = glm::dot(m_quat, q.m_quat);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TQuaternion<TInternalType>::Dot(const TQuaternion<TInternalType> &q1,
                                                  const TQuaternion<TInternalType> &q2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");

        const TInternalType dot = glm::dot(q1.m_quat, q2.m_quat);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::EulerAngles() const
    {
        const glm::tvec3<TInternalType> euler_angles = glm::eulerAngles(m_quat);
        const TVector3<TInternalType> v(euler_angles.x, euler_angles.y, euler_angles.z);
        return v;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TQuaternion<TInternalType>::EulerAngles(const TQuaternion<TInternalType> &q)
    {
        const glm::tvec3<TInternalType> euler_angles = glm::eulerAngles(q.m_quat);
        const TVector3<TInternalType> v(euler_angles.x, euler_angles.y, euler_angles.z);
        return v;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Inverse()
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Inverse' accepts only floating-point inputs");
        m_quat = glm::inverse(m_quat);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Inverse(const TQuaternion<TInternalType> &q)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Inverse' accepts only floating-point inputs");
        const TQuaternion<TInternalType> quat(glm::inverse(q.m_quat));
        return quat;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Lerp(const TQuaternion<TInternalType> &q1,
                                                                const TQuaternion<TInternalType> &q2,
                                                                const float t)
    {
        const auto qua = glm::lerp(q1.m_quat, q2.m_quat, t);
        const TQuaternion<TInternalType> quat(qua);
        return quat;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::Normalize()
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        m_quat = glm::normalize(m_quat);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Normalize(const TQuaternion<TInternalType> &q)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");
        
        const auto norm = glm::normalize(q.m_quat);
        const TQuaternion<TInternalType> quat(norm);
        return quat;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> TQuaternion<TInternalType>::Slerp(const TQuaternion<TInternalType> &q1,
                                                                 const TQuaternion<TInternalType> &q2,
                                                                 const float t)
    {
        const auto slerp = glm::slerp(q1.m_quat, q2.m_quat, t);
        const TQuaternion<TInternalType> quat(slerp);
        return quat;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator*=(const TQuaternion<TInternalType> &q)
    {
        m_quat *= q.m_quat;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType>& TQuaternion<TInternalType>::operator*=(const TVector3<TInternalType> &v)
    {
        const auto v3 = glm::tvec3<TInternalType>(v.x(), v.y(), v.z());;
        m_quat *= v3;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TQuaternion<TInternalType> operator*(const TQuaternion<TInternalType> &q1, const TQuaternion<TInternalType> &q2)
    {
        const TQuaternion<TInternalType> quat(q1.m_quat * q2.m_quat);
        return quat;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> operator*(const TQuaternion<TInternalType> &q, const TVector3<TInternalType> &v)
    {
        const auto vec3 = q.m_quat * glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        const TVector3<TInternalType> v3(vec3.x, vec3.y, vec3.z);
        return v3;
    }

    template<TNumericalConcept TInternalType>
    std::string TQuaternion<TInternalType>::ToString() const
    {
        const std::string string = std::format("[{}, {}, {}, {}]", m_quat.w, m_quat.x, m_quat.y, m_quat.z);
        return string;
    }

    template<TNumericalConcept TInternalType>
    std::ostream& operator<<(std::ostream &os, const TQuaternion<TInternalType> &q)
    {
        return os << "[" << q.w() << ", " << q.x() << ", " << q.y() << ", " << q.z() << "]";
    }
}

#endif // M3GTR_SRC_MATH_TQUATERNION_HXX_INCLUDED