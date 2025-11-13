#ifndef M3GTR_SRC_MATH_TVECTOR4_HXX_INCLUDED
#define M3GTR_SRC_MATH_TVECTOR4_HXX_INCLUDED

#include "TVector3.hxx"

#include <Constants/EpsilonConstant.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <format>
#include <ostream>
#include <string>

namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    class TVector4
    {
    private:
        glm::tvec4<TInternalType> m_vec4;

        TVector4(const glm::tvec4<TInternalType> &v);

    public:
        TVector4();
        TVector4(const TInternalType x, const TInternalType y, const TInternalType z, const TInternalType w);
        TVector4(const TVector3<TInternalType> &v, TInternalType w);
        TVector4(const TVector4<TInternalType> &v);
        TVector4(TVector4<TInternalType> &&v);

        TVector4<TInternalType>& operator=(const TVector4<TInternalType> &v);
        TVector4<TInternalType>& operator=(TVector4<TInternalType> &&v);

        TInternalType& operator[](const std::size_t index);
        const TInternalType& operator[](const std::size_t index) const;

        TInternalType& at(const std::size_t index);
        const TInternalType& at(const std::size_t index) const;

        TInternalType& x();
        TInternalType& y();
        TInternalType& z();
        TInternalType& w();

        TInternalType x() const;
        TInternalType y() const;
        TInternalType z() const;
        TInternalType w() const;

        static std::size_t Size();

        TVector4<TInternalType>& Set(const TInternalType x, const TInternalType y, const TInternalType z, const TInternalType w);

        TInternalType* InternalDataPointer();
        const TInternalType* InternalDataPointer() const;

        TInternalType Distance(const TVector4<TInternalType> &v) const;
        static TInternalType Distance(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2);

        TInternalType Dot(const TVector4<TInternalType> &v) const;
        static TInternalType Dot(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2);

        static TVector4<TInternalType> FaceForward(const TVector4<TInternalType> &in,
                                                   const TVector4<TInternalType> &normal,
                                                   const TVector4<TInternalType> &normal_ref);

        static TVector4<TInternalType> Lerp(const TVector4<TInternalType> &v1,
                                            const TVector4<TInternalType> &v2,
                                            const float t);

        float Magnitude() const;
        float SquareMagnitude() const;

        TVector4<TInternalType>& Normalize();
        static TVector4<TInternalType> Normalize(const TVector4<TInternalType> &v);

        static TVector4<TInternalType> Reflect(const TVector4<TInternalType> &in,
                                               const TVector4<TInternalType> &normal);
        static TVector4<TInternalType> Refract(const TVector4<TInternalType> &in,
                                               const TVector4<TInternalType> &normal,
                                               const TInternalType eta);

        TVector4<TInternalType>& Scale(const TVector4<TInternalType> &v);
        static TVector4<TInternalType> Scale(const TVector4<TInternalType> &v1,
                                             const TVector4<TInternalType> &v2);

        template<TNumericalConcept TOtherInternalType>
        TVector4<TInternalType>& operator+=(const TVector4<TOtherInternalType> &v);

        template<TNumericalConcept TOtherInternalType>
        TVector4<TInternalType>& operator-=(const TVector4<TOtherInternalType> &v);

        template<TNumericalConcept TOtherInternalType>
        TVector4<TInternalType>& operator*=(const TOtherInternalType scalar);

        template<TNumericalConcept TOtherInternalType>
        TVector4<TInternalType>& operator/=(const TOtherInternalType scalar);

        bool operator==(const TVector4<TInternalType> &v);

        bool operator!=(const TVector4<TInternalType> &v);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator+(const TVector4<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator-(const TVector4<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator+(const TVector4<TInternal> &v, const TInternal scalar);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator+(const TVector4<TInternal> &v1, const TVector4<TInternal> &v2);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator+(const TInternal scalar, const TVector4<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator-(const TVector4<TInternal> &v, const TInternal scalar);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator-(const TVector4<TInternal> &v1, const TVector4<TInternal> &v2);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator-(const TInternal scalar, const TVector4<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator*(const TVector4<TInternal> &v, const TInternal scalar);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator*(const TInternal scalar, const TVector4<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator/(const TVector4<TInternal> &v, TInternal scalar);

        std::string ToString() const;
        template<TNumericalConcept TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TVector4<TInternal> &v);
    };
}

// Implementation
namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>::TVector4(const glm::tvec4<TInternalType> &v)
        : m_vec4(v)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>::TVector4()
        : m_vec4(static_cast<TInternalType>(0), static_cast<TInternalType>(0),
                 static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {

    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>::TVector4(const TInternalType x, const TInternalType y, const TInternalType z, const TInternalType w)
        : m_vec4(x, y, z, w)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>::TVector4(const TVector3<TInternalType> &v, const TInternalType w)
        : m_vec4(v.x(), v.y(), v.z(), w)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>::TVector4(const TVector4<TInternalType> &v)
        : m_vec4(v.m_vec4)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>::TVector4(TVector4<TInternalType> &&v)
        : m_vec4(std::move(v.m_vec4))
    {

    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::operator=(const TVector4<TInternalType> &v)
    {
        m_vec4 = v.m_vec4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::operator=(TVector4<TInternalType> &&v)
    {
        m_vec4 = std::move(v.m_vec4);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector4<TInternalType>::operator[](const std::size_t index)
    {
        TInternalType& value = m_vec4[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TVector4<TInternalType>::operator[](const std::size_t index) const
    {
        const TInternalType& value = m_vec4[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector4<TInternalType>::at(const std::size_t index)
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid vector4 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }
        
        TInternalType& value = m_vec4[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TVector4<TInternalType>::at(const std::size_t index) const
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid vector4 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }
        
        const TInternalType& value = m_vec4[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector4<TInternalType>::x()
    {
        return m_vec4.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector4<TInternalType>::y()
    {
        return m_vec4.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector4<TInternalType>::z()
    {
        return m_vec4.z;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector4<TInternalType>::w()
    {
        return m_vec4.w;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::x() const
    {
        return m_vec4.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::y() const
    {
        return m_vec4.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::z() const
    {
        return m_vec4.z;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::w() const
    {
        return m_vec4.w;
    }

    template<TNumericalConcept TInternalType>
    std::size_t TVector4<TInternalType>::Size()
    {
        return static_cast<std::size_t>(4);
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::Set(const TInternalType x, const TInternalType y,
                                                          const TInternalType z, const TInternalType w)
    {
        m_vec4.x = x;
        m_vec4.y = y;
        m_vec4.z = z;
        m_vec4.w = w;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType* TVector4<TInternalType>::InternalDataPointer()
    {
        TInternalType* const value = glm::value_ptr(m_vec4);
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType* TVector4<TInternalType>::InternalDataPointer() const
    {
        const TInternalType* const value = glm::value_ptr(m_vec4);
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::Distance(const TVector4<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");

        const auto distance = glm::distance(m_vec4, v.m_vec4);
        return distance;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::Distance(const TVector4<TInternalType> &v1,
                                                    const TVector4<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");

        const auto distance = glm::distance(v1.m_vec4, v2.m_vec4);
        return distance;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::Dot(const TVector4<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        
        const auto dot = glm::dot(m_vec4, v.m_vec4);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector4<TInternalType>::Dot(const TVector4<TInternalType> &v1,
                                               const TVector4<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        
        const auto dot = glm::dot(v1.m_vec4, v2.m_vec4);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::FaceForward(const TVector4<TInternalType> &in,
                                                                 const TVector4<TInternalType> &normal,
                                                                 const TVector4<TInternalType> &normal_ref)
    {
        const auto faceforward = glm::faceforward(in.m_vec4, normal.m_vec4, normal_ref.m_vec4);
        const TVector4<TInternalType> vec(faceforward);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Lerp(const TVector4<TInternalType> &v1,
                                                          const TVector4<TInternalType> &v2,
                                                          const float t)
    {
        const auto mix = glm::mix(v1.m_vec4, v2.m_vec4, t);
        const TVector4<TInternalType> vec(mix);
        return mix;
    }

    template<TNumericalConcept TInternalType>
    float TVector4<TInternalType>::Magnitude() const
    {
        float length = 0;
        const bool is_iec559 = std::numeric_limits<TInternalType>::is_iec559;
        
        if (is_iec559)
        {
            length = glm::length(m_vec4);
        }
        else
        {
            const glm::tvec4<float> v(m_vec4.x, m_vec4.y, m_vec4.z, m_vec4.w);
            length = glm::length(v);

        }

        return length;
    }

    template<TNumericalConcept TInternalType>
    float TVector4<TInternalType>::SquareMagnitude() const
    {
        const float sqr_mag = (m_vec4.x * m_vec4.x) + (m_vec4.y * m_vec4.y) + (m_vec4.z * m_vec4.z) + (m_vec4.w * m_vec4.w);
        return sqr_mag;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::Normalize()
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");

        const TInternalType length = glm::length(m_vec4);
        if (length < k_epsilon)
        {
            return *this;
        }

        m_vec4 = m_vec4 / length;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Normalize(const TVector4<TInternalType> &v)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");

        const TInternalType length = glm::length(v.m_vec4);
        if (length < k_epsilon)
        {
            return v;
        }

        return TVector4<TInternalType>(v.m_vec4 / length);
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Reflect(const TVector4<TInternalType> &in,
                                                             const TVector4<TInternalType> &normal)
    {
        const auto reflect = glm::reflect(in.m_vec4, normal.m_vec4);
        const TVector4<TInternalType> vec(reflect);
        return reflect;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Refract(const TVector4<TInternalType> &in,
                                                             const TVector4<TInternalType> &normal,
                                                             const TInternalType eta)
    {
        const auto refract = glm::refract(in.m_vec4, normal.m_vec4, eta);
        const TVector4<TInternalType> vec(refract);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::Scale(const TVector4<TInternalType> &v)
    {
        m_vec4 *= v.m_vec4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TVector4<TInternalType>::Scale(const TVector4<TInternalType> &v1,
                                                           const TVector4<TInternalType> &v2)
    {
        const TVector4<TInternalType> vec(v1.m_vec4 * v2.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::operator+=(const TVector4<TOtherInternalType> &v)
    {
        m_vec4 += v.m_vec4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::operator-=(const TVector4<TOtherInternalType> &v)
    {
        m_vec4 -= v.m_vec4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::operator*=(TOtherInternalType scalar)
    {
        m_vec4 *= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector4<TInternalType>& TVector4<TInternalType>::operator/=(TOtherInternalType scalar)
    {
        m_vec4 /= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    bool TVector4<TInternalType>::operator==(const TVector4<TInternalType> &v)
    {
        const bool are_equal = (m_vec4 == v.m_vec4);
        return are_equal;
    }

    template<TNumericalConcept TInternalType>
    bool TVector4<TInternalType>::operator!=(const TVector4<TInternalType> &v)
    {
        const bool are_not_equal = (m_vec4 != v.m_vec4);
        return are_not_equal;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator+(const TVector4<TInternalType> &v)
    {
        return v;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator-(const TVector4<TInternalType> &v)
    {
        const TVector4<TInternalType> vec(-v.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator+(const TVector4<TInternalType> &v, const TInternalType scalar)
    {
        const TVector4<TInternalType> vec(v.m_vec4 + scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator+(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2)
    {
        const TVector4<TInternalType> vec(v1.m_vec4 + v2.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator+(TInternalType scalar, const TVector4<TInternalType> &v)
    {
        const TVector4<TInternalType> vec(scalar + v.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator-(const TVector4<TInternalType> &v, const TInternalType scalar)
    {
        const TVector4<TInternalType> vec(v.m_vec4 - scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator-(const TVector4<TInternalType> &v1, const TVector4<TInternalType> &v2)
    {
        const TVector4<TInternalType> vec(v1.m_vec4 - v2.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator-(const TInternalType scalar, const TVector4<TInternalType> &v)
    {
        const TVector4<TInternalType> vec(scalar - v.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator*(const TVector4<TInternalType> &v, const TInternalType scalar)
    {
        const TVector4<TInternalType> vec(v.m_vec4 * scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator*(const TInternalType scalar, const TVector4<TInternalType> &v)
    {
        const TVector4<TInternalType> vec(scalar * v.m_vec4);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator/(const TVector4<TInternalType> &v, const TInternalType scalar)
    {
        const TVector4<TInternalType> vec(v.m_vec4 / scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    std::string TVector4<TInternalType>::ToString() const
    {
        const std::string string = std::format("[{}, {}, {}, {}]", m_vec4.x, m_vec4.y, m_vec4.z, m_vec4.w);
        return string;
    }

    template<TNumericalConcept TInternalType>
    std::ostream& operator<<(std::ostream &os, const TVector4<TInternalType> &v)
    {
        return os << "[" << v.m_vec4.x << ", " << v.m_vec4.y << ", " << v.m_vec4.z << ", " << v.m_vec4.w << "]";
    }
}

#endif // M3GTR_SRC_MATH_TVECTOR4_HXX_INCLUDED
