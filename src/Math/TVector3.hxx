#ifndef M3GTR_SRC_MATH_TVECTOR3_HXX_INCLUDED
#define M3GTR_SRC_MATH_TVECTOR3_HXX_INCLUDED

#include "TNumericalConcept.hxx"

#include <Constants/EpsilonConstant.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <format>
#include <limits>
#include <ostream>
#include <string>

namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    class TVector3
    {
    private:
        glm::tvec3<TInternalType> m_vec3;

        TVector3(const glm::tvec3<TInternalType> &v);

    public:
        TVector3();
        TVector3(const TInternalType x, const TInternalType y, const TInternalType z);
        TVector3(const TVector3<TInternalType> &v);
        TVector3(TVector3<TInternalType> &&v);

        TVector3<TInternalType>& operator=(const TVector3<TInternalType> &v);
        TVector3<TInternalType>& operator=(TVector3<TInternalType> &&v);

        TInternalType& operator[](const std::size_t index);
        const TInternalType& operator[](const std::size_t index) const;

        TInternalType& at(const std::size_t index);
        const TInternalType& at(const std::size_t index) const;

        TInternalType& x();
        TInternalType& y();
        TInternalType& z();

        TInternalType x() const;
        TInternalType y() const;
        TInternalType z() const;

        static std::size_t Size();

        TVector3<TInternalType>& Set(const TInternalType x, const TInternalType y, const TInternalType z);

        TInternalType* InternalDataPointer();
        const TInternalType* InternalDataPointer() const;

        TVector3<TInternalType> Cross(const TVector3<TInternalType> &v) const;
        static TVector3<TInternalType> Cross(const TVector3<TInternalType> &v1,
                                             const TVector3<TInternalType> &v2);

        TInternalType Distance(const TVector3<TInternalType> &v) const;
        static TInternalType Distance(const TVector3<TInternalType> &v1,
                                      const TVector3<TInternalType> &v2);

        TInternalType Dot(const TVector3<TInternalType> &v) const;
        static TInternalType Dot(const TVector3<TInternalType> &v1,
                                 const TVector3<TInternalType> &v2);

        static TVector3<TInternalType> FaceForward(const TVector3<TInternalType> &in,
                                                   const TVector3<TInternalType> &normal,
                                                   const TVector3 &normal_ref);

        static TVector3<TInternalType> Lerp(const TVector3<TInternalType> &v1,
                                            const TVector3<TInternalType> &v2,
                                            const float t);

        float Magnitude() const;
        float SquareMagnitude() const;

        TVector3<TInternalType>& Normalize();
        static TVector3<TInternalType> Normalize(const TVector3<TInternalType> &v);

        static TVector3<TInternalType> Reflect(const TVector3<TInternalType> &in,
                                               const TVector3<TInternalType> &normal);
        static TVector3<TInternalType> Refract(const TVector3<TInternalType> &in,
                                               const TVector3<TInternalType> &normal,
                                               const TInternalType eta);

        TVector3<TInternalType>& Scale(const TVector3<TInternalType> &v);
        static TVector3<TInternalType> Scale(const TVector3<TInternalType> &v1,
                                             const TVector3<TInternalType> &v2);
        
        static TVector3<TInternalType> Min(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2);
        
        template<TNumericalConcept... TInternal>
        static TVector3<TInternalType> Min(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2,
                                           const TVector3<TInternal>&&... others);

        static TVector3<TInternalType> Max(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2);
        
        template<TNumericalConcept... TInternal>
        static TVector3<TInternalType> Max(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2,
                                           const TVector3<TInternal>&&... others);

        template<TNumericalConcept TOtherInternalType>
        TVector3<TInternalType>& operator+=(const TVector3<TOtherInternalType> &v);

        template<TNumericalConcept TOtherInternalType>
        TVector3<TInternalType>& operator-=(const TVector3<TOtherInternalType> &v);

        template<TNumericalConcept TOtherInternalType>
        TVector3<TInternalType>& operator*=(const TOtherInternalType scalar);

        template<TNumericalConcept TOtherInternalType>
        TVector3<TInternalType>& operator/=(const TOtherInternalType scalar);

        bool operator==(const TVector3<TInternalType> &v);
        bool operator!=(const TVector3<TInternalType> &v);

        template<TNumericalConcept TInternal>
        friend TVector3<TInternal> operator+(const TVector3<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector3<TInternal> operator-(const TVector3<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator+(const TVector3<TInternal> &v,
                                             const TOtherInternalType scalar);

        template<TNumericalConcept TInternal>
        friend TVector3<TInternal> operator+(const TVector3<TInternal> &v1,
                                             const TVector3<TInternal> &v2);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator+(const TOtherInternalType scalar,
                                             const TVector3<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator-(const TVector3<TInternal> &v,
                                             const TOtherInternalType scalar);

        template<TNumericalConcept TInternal>
        friend TVector3<TInternal> operator-(const TVector3<TInternal> &v1,
                                             const TVector3<TInternal> &v2);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator-(const TOtherInternalType scalar,
                                             const TVector3<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator*(const TVector3<TInternal> &v,
                                             const TOtherInternalType scalar);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator*(const TOtherInternalType scalar,
                                                       const TVector3<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector3<TInternal> operator/(const TVector3<TInternal> &v,
                                             const TOtherInternalType scalar);

        std::string ToString() const;
        template<TNumericalConcept TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TVector3<TInternal> &v);
    };
}

// Implementation
namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>::TVector3(const glm::tvec3<TInternalType> &v)
        : m_vec3(v)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>::TVector3()
        : m_vec3(static_cast<TInternalType>(0), static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {

    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>::TVector3(const TInternalType x, const TInternalType y, const TInternalType z)
        : m_vec3(x, y, z)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>::TVector3(const TVector3<TInternalType> &v)
        : m_vec3(v.m_vec3)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>::TVector3(TVector3<TInternalType> &&v)
        : m_vec3(std::move(v.m_vec3))
    {

    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::operator=(const TVector3<TInternalType> &v)
    {
        m_vec3 = v.m_vec3;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::operator=(TVector3<TInternalType> &&v)
    {
        m_vec3 = std::move(v.m_vec3);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector3<TInternalType>::operator[](const std::size_t index)
    {
        TInternalType& value = m_vec3[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TVector3<TInternalType>::operator[](const std::size_t index) const
    {
        const TInternalType& value = m_vec3[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector3<TInternalType>::at(const std::size_t index)
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid vector3 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }

        TInternalType& value = m_vec3[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TVector3<TInternalType>::at(const std::size_t index) const
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid vector3 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }

        const TInternalType& value = m_vec3[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector3<TInternalType>::x()
    {
        return m_vec3.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector3<TInternalType>::y()
    {
        return m_vec3.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector3<TInternalType>::z()
    {
        return m_vec3.z;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::x() const
    {
        return m_vec3.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::y() const
    {
        return m_vec3.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::z() const
    {
        return m_vec3.z;
    }

    template<TNumericalConcept TInternalType>
    std::size_t TVector3<TInternalType>::Size()
    {
        return static_cast<std::size_t>(3);
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::Set(const TInternalType x, const TInternalType y, const TInternalType z)
    {
        m_vec3.x = x;
        m_vec3.y = y;
        m_vec3.z = z;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType* TVector3<TInternalType>::InternalDataPointer()
    {
        TInternalType* const value = glm::value_ptr(m_vec3);
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType* TVector3<TInternalType>::InternalDataPointer() const
    {
        const TInternalType* const value = glm::value_ptr(m_vec3);
        return value;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Cross(const TVector3<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");

        const auto cross = glm::cross(m_vec3, v.m_vec3);
        const TVector3<TInternalType> vec(cross);
        return cross;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Cross(const TVector3<TInternalType> &v1,
                                                           const TVector3<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Cross' accepts only floating-point inputs");

        const auto cross = glm::cross(v1.m_vec3, v2.m_vec3);
        const TVector3<TInternalType> vec(cross);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::Distance(const TVector3<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");

        const auto distance = glm::distance(m_vec3, v.m_vec3);
        return distance;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::Distance(const TVector3<TInternalType> &v1,
                                                    const TVector3<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");
        
        const auto distance = glm::distance(v1.m_vec3, v2.m_vec3);
        return distance;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::Dot(const TVector3<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        
        const auto dot = glm::distance(m_vec3, v.m_vec3);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector3<TInternalType>::Dot(const TVector3<TInternalType> &v1,
                                               const TVector3<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        
        const auto dot = glm::distance(v1.m_vec3, v2.m_vec3);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::FaceForward(const TVector3<TInternalType> &in,
                                                                 const TVector3<TInternalType> &normal,
                                                                 const TVector3 &normal_ref)
    {
        const auto faceforward = glm::faceforward(in.m_vec3, normal.m_vec3, normal_ref.m_vec3);
        const TVector3<TInternalType> vec(faceforward);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Lerp(const TVector3<TInternalType> &v1,
                                                          const TVector3<TInternalType> &v2,
                                                          const float t)
    {
        const auto mix = glm::mix(v1.m_vec3, v2.m_vec3, t);
        const TVector3<TInternalType> vec(mix);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    float TVector3<TInternalType>::Magnitude() const
    {
        float length = 0;
        const bool is_iec559 = std::numeric_limits<TInternalType>::is_iec559;

        if (is_iec559)
        {
            length = glm::length(m_vec3);
        }
        else
        {
            const glm::tvec3<float> v(m_vec3.x, m_vec3.y, m_vec3.z);
            length = glm::length(v);
        }

        return length;
    }

    template<TNumericalConcept TInternalType>
    float TVector3<TInternalType>::SquareMagnitude() const
    {
        const float sqr_mag = (m_vec3.x * m_vec3.x) + (m_vec3.y * m_vec3.y) + (m_vec3.z * m_vec3.z);
        return sqr_mag;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::Normalize()
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");

        const TInternalType length = glm::length(m_vec3);
        if (length < k_epsilon)
        {
            return *this;
        }

        m_vec3 = m_vec3 / length;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Normalize(const TVector3<TInternalType> &v)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");

        const TInternalType length = glm::length(v.m_vec3);
        if (length < k_epsilon)
        {
            return v;
        }

        return TVector3<TInternalType>(v.m_vec3 / length);
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Reflect(const TVector3<TInternalType> &in,
                                                             const TVector3<TInternalType> &normal)
    {
        const auto reflect = glm::reflect(in.m_vec3, normal.m_vec3);
        const TVector3<TInternalType> vec(reflect);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Refract(const TVector3<TInternalType> &in,
                                                             const TVector3<TInternalType> &normal,
                                                             const TInternalType eta)
    {
        const auto refract = glm::refract(in.m_vec3, normal.m_vec3, eta);
        const TVector3<TInternalType> vec(refract);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::Scale(const TVector3<TInternalType> &v)
    {
        m_vec3 *= v.m_vec3;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Scale(const TVector3<TInternalType> &v1,
                                                           const TVector3<TInternalType> &v2)
    {
        const TVector3<TInternalType> vec(v1.m_vec3 * v2.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Min(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2)
    {
        const TVector3<TInternalType> min = {
            std::min(v1.x(), v2.x()),
            std::min(v1.y(), v2.y()),
            std::min(v1.z(), v2.z()),
        };
        return min;
    }
    
    template<TNumericalConcept TInternalType>
    template<TNumericalConcept... TOtherInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Min(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2,
                                                         const TVector3<TOtherInternalType>&&... others)
    {
        TVector3<TInternalType> min;

        if (sizeof...(others) == 0)
        {
            min = Min(v1, v2);
        }
        else
        {
            const TVector3<TInternalType> first_2_min = Min(v1, v2);
            min = Min(first_2_min, others...);
        }

        return min;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Max(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2)
    {
        const TVector3<TInternalType> max = {
            std::max(v1.x(), v2.x()),
            std::max(v1.y(), v2.y()),
            std::max(v1.z(), v2.z()),
        };
        return max;
    }
    
    template<TNumericalConcept TInternalType>
    template<TNumericalConcept... TOtherInternalType>
    TVector3<TInternalType> TVector3<TInternalType>::Max(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2,
                                                         const TVector3<TOtherInternalType>&&... others)
    {
        TVector3<TInternalType> max;

        if (sizeof...(others) == 0)
        {
            max = Max(v1, v2);
        }
        else
        {
            const TVector3<TInternalType> first_2_max = Max(v1, v2);
            max = Max(first_2_max, others...);
        }

        return max;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::operator+=(const TVector3<TOtherInternalType> &v)
    {
        m_vec3 += v.m_vec3;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::operator-=(const TVector3<TOtherInternalType> &v)
    {
        m_vec3 -= v.m_vec3;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::operator*=(TOtherInternalType scalar)
    {
        m_vec3 *= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector3<TInternalType>& TVector3<TInternalType>::operator/=(TOtherInternalType scalar)
    {
        m_vec3 /= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    bool TVector3<TInternalType>::operator==(const TVector3<TInternalType> &v)
    {
        const bool are_equal = (m_vec3 == v.m_vec3);
        return are_equal;
    }

    template<TNumericalConcept TInternalType>
    bool TVector3<TInternalType>::operator!=(const TVector3<TInternalType> &v)
    {
        const bool are_not_equal = (m_vec3 != v.m_vec3);
        return are_not_equal;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> operator+(const TVector3<TInternalType> &v)
    {
        return v;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> operator-(const TVector3<TInternalType> &v)
    {
        const TVector3<TInternalType> vec(-v.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator+(const TVector3<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector3<TInternalType> vec(v.m_vec3 + scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> operator+(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2)
    {
        const TVector3<TInternalType> vec(v1.m_vec3 + v2.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator+(const TOtherInternalType scalar, const TVector3<TInternalType> &v)
    {
        const TVector3<TInternalType> vec(scalar + v.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator-(const TVector3<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector3<TInternalType> vec(v.m_vec3 - scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector3<TInternalType> operator-(const TVector3<TInternalType> &v1, const TVector3<TInternalType> &v2)
    {
        const TVector3<TInternalType> vec(v1.m_vec3 - v2.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator-(const TOtherInternalType scalar, const TVector3<TInternalType> &v)
    {
        const TVector3<TInternalType> vec(scalar - v.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator*(const TVector3<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector3<TInternalType> vec(v.m_vec3 * scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator*(const TOtherInternalType scalar, const TVector3<TInternalType> &v)
    {
        const TVector3<TInternalType> vec(scalar * v.m_vec3);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector3<TInternalType> operator/(const TVector3<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector3<TInternalType> vec(v.m_vec3 / scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    std::string TVector3<TInternalType>::ToString() const
    {
        const std::string string = std::format("[{}, {}, {}]", m_vec3.x, m_vec3.y, m_vec3.z);
        return string;
    }

    template<TNumericalConcept TInternalType>
    std::ostream& operator<<(std::ostream &os, const TVector3<TInternalType> &v)
    {
        return os << "[" << v.m_vec3.x << ", " << v.m_vec3.y << ", " << v.m_vec3.z << "]";
    }
}

#endif // M3GTR_SRC_MATH_TVECTOR3_HXX_INCLUDED
