#ifndef M3GTR_SRC_MATH_TVECTOR2_HXX_INCLUDED
#define M3GTR_SRC_MATH_TVECTOR2_HXX_INCLUDED

#include "TNumericalConcept.hxx"

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
    class TVector2
    {
    private:
        glm::tvec2<TInternalType> m_vec2;

        TVector2(const glm::tvec2<TInternalType> &v);

    public:
        TVector2();
        TVector2(const TInternalType x, const TInternalType y);
        TVector2(const TVector2<TInternalType> &v);
        TVector2(TVector2<TInternalType> &&v);

        TVector2<TInternalType>& operator=(const TVector2<TInternalType> &v);
        TVector2<TInternalType>& operator=(TVector2<TInternalType> &&v);

        TInternalType& operator[](const std::size_t index);
        const TInternalType& operator[](const std::size_t index) const;

        TInternalType& at(const std::size_t index);
        const TInternalType& at(const std::size_t index) const;

        TInternalType& x();
        TInternalType& y();

        TInternalType x() const;
        TInternalType y() const;

        static std::size_t Size();
        
        TVector2<TInternalType>& Set(const TInternalType x, const TInternalType y);

        TInternalType* InternalDataPointer();
        const TInternalType* InternalDataPointer() const;

        TInternalType Distance(const TVector2<TInternalType> &v) const;
        static TInternalType Distance(const TVector2<TInternalType> &v1,
                                      const TVector2<TInternalType> &v2);

        TInternalType Dot(const TVector2<TInternalType> &v) const;
        static TInternalType Dot(const TVector2<TInternalType> &v1,
                                 const TVector2<TInternalType> &v2);

        static TVector2<TInternalType> FaceForward(const TVector2<TInternalType> &in,
                                                   const TVector2<TInternalType> &normal,
                                                   const TVector2<TInternalType> &normal_ref);

        static TVector2<TInternalType> Lerp(const TVector2<TInternalType> &v1,
                                            const TVector2<TInternalType> &v2,
                                            const float t);

        float Magnitude() const;
        float SquareMagnitude() const;

        TVector2<TInternalType>& Normalize();
        static TVector2<TInternalType> Normalize(const TVector2<TInternalType> &v);

        static TVector2<TInternalType> Reflect(const TVector2<TInternalType> &in,
                                               const TVector2<TInternalType> &normal);
        static TVector2<TInternalType> Refract(const TVector2<TInternalType> &in,
                                               const TVector2<TInternalType> &normal,
                                               const TInternalType eta);

        TVector2<TInternalType>& Scale(const TVector2<TInternalType> &v);
        static TVector2<TInternalType> Scale(const TVector2<TInternalType> &v1,
                                             const TVector2<TInternalType> &v2);

        template<TNumericalConcept TOtherInternalType>
        TVector2<TInternalType>& operator+=(const TVector2<TOtherInternalType> &v);

        template<TNumericalConcept TOtherInternalType>
        TVector2<TInternalType>& operator-=(const TVector2<TOtherInternalType> &v);

        template<TNumericalConcept TOtherInternalType>
        TVector2<TInternalType>& operator*=(const TOtherInternalType scalar);

        template<TNumericalConcept TOtherInternalType>
        TVector2<TInternalType>& operator/=(const TOtherInternalType scalar);

        bool operator==(const TVector2<TInternalType> &v);
        bool operator!=(const TVector2<TInternalType> &v);

        template<TNumericalConcept TInternal>
        friend TVector2<TInternal> operator+(const TVector2<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TVector2<TInternal> operator-(const TVector2<TInternal> &v);


        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator+(const TVector2<TInternal> &v,
                                             const TOtherInternalType scalar);

        template<TNumericalConcept TInternal>
        friend TVector2<TInternal> operator+(const TVector2<TInternal> &v1,
                                             const TVector2<TInternal> &v2);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator+(const TOtherInternalType scalar,
                                             const TVector2<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator-(const TVector2<TInternal> &v,
                                             const TOtherInternalType scalar);

        template<TNumericalConcept TInternal>
        friend TVector2<TInternal> operator-(const TVector2<TInternal> &v1,
                                             const TVector2<TInternal> &v2);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator-(const TOtherInternalType scalar,
                                             const TVector2<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator*(const TVector2<TInternal> &v,
                                             const TOtherInternalType scalar);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator*(const TOtherInternalType scalar,
                                             const TVector2<TInternal> &v);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TVector2<TInternal> operator/(const TVector2<TInternal> &v,
                                             const TOtherInternalType scalar);

        std::string ToString() const;
        template <TNumericalConcept TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TVector2<TInternal> &v);
    };
}

// Implementation.
namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>::TVector2(const glm::tvec2<TInternalType> &v)
        : m_vec2(v)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>::TVector2()
        : m_vec2(static_cast<TInternalType>(0), static_cast<TInternalType>(0))
    {

    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>::TVector2(const TInternalType x, const TInternalType y)
        : m_vec2(x, y)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>::TVector2(const TVector2<TInternalType> &v)
        : m_vec2(v.m_vec2)
    {

    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>::TVector2(TVector2<TInternalType> &&v)
        : m_vec2(std::move(v.m_vec2))
    {

    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::operator=(const TVector2<TInternalType> &v)
    {
        m_vec2 = v.m_vec2;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::operator=(TVector2<TInternalType> &&v)
    {
        m_vec2 = std::move(v.m_vec2);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector2<TInternalType>::operator[](const std::size_t index)
    {
        TInternalType& value = m_vec2[index];
        return value;
    }
    template<TNumericalConcept TInternalType>
    const TInternalType& TVector2<TInternalType>::operator[](const std::size_t index) const
    {
        const TInternalType& value = m_vec2[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector2<TInternalType>::at(const std::size_t index)
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid vector2 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }

        TInternalType& value = m_vec2[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TVector2<TInternalType>::at(const std::size_t index) const
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid vector2 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }

        const TInternalType& value = m_vec2[index];
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector2<TInternalType>::x()
    {
        return m_vec2.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TVector2<TInternalType>::y()
    {
        return m_vec2.y;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector2<TInternalType>::x() const
    {
        return m_vec2.x;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector2<TInternalType>::y() const
    {
        return m_vec2.y;
    }

    template<TNumericalConcept TInternalType>
    std::size_t TVector2<TInternalType>::Size()
    {
        return static_cast<std::size_t>(2);
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::Set(const TInternalType x, const TInternalType y)
    {
        m_vec2.x = x;
        m_vec2.y = y;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TInternalType* TVector2<TInternalType>::InternalDataPointer()
    {
        TInternalType* const value = glm::value_ptr(m_vec2);
        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType* TVector2<TInternalType>::InternalDataPointer() const
    {
        const TInternalType* const value = glm::value_ptr(m_vec2);
        return value;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector2<TInternalType>::Distance(const TVector2<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");

        const TInternalType distance = glm::distance(m_vec2, v.m_vec2);
        return distance;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector2<TInternalType>::Distance(const TVector2<TInternalType> &v1,
                                                    const TVector2<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Distance' accepts only floating-point inputs");

        const TInternalType distance = glm::distance(v1.m_vec2, v2.m_vec2);
        return distance;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector2<TInternalType>::Dot(const TVector2<TInternalType> &v) const
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");

        const TInternalType dot = glm::dot(m_vec2, v.m_vec2);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TInternalType TVector2<TInternalType>::Dot(const TVector2<TInternalType> &v1,
                                               const TVector2<TInternalType> &v2)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Dot' accepts only floating-point inputs");
        
        const TInternalType dot = glm::dot(v1.m_vec2, v2.m_vec2);
        return dot;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::FaceForward(const TVector2<TInternalType> &in,
                                                                 const TVector2<TInternalType> &normal,
                                                                 const TVector2<TInternalType> &normal_ref)
    {
        const auto faceforward = glm::faceforward(in.m_vec2, normal.m_vec2, normal_ref.m_vec2);
        const TVector2<TInternalType> v2(faceforward);

        return v2;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Lerp(const TVector2<TInternalType> &v1,
                                                          const TVector2<TInternalType> &v2,
                                                          const float t)
    {
        const auto mix = glm::mix(v1.m_vec2, v2.m_vec2, t);
        const TVector2<TInternalType> v(mix);
        return v;
    }

    template<TNumericalConcept TInternalType>
    float TVector2<TInternalType>::Magnitude() const
    {
        float length = 0;
        const bool is_iec559 = std::numeric_limits<TInternalType>::is_iec559;

        if (is_iec559)
        {
            length = glm::length(m_vec2);
        }
        else
        {
            const glm::tvec2<float> v(m_vec2.x, m_vec2.y);
            length = glm::length(v);
        }
        
        if (std::numeric_limits<TInternalType>::is_iec559)
        {
            return static_cast<float>(glm::length(m_vec2));
        }

        return length;
    }

    template<TNumericalConcept TInternalType>
    float TVector2<TInternalType>::SquareMagnitude() const
    {
        const float sqr_mag = (m_vec2.x * m_vec2.x) + (m_vec2.y * m_vec2.y);
        return sqr_mag;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::Normalize()
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");

        const TInternalType length = glm::length(m_vec2);
        if (length < k_epsilon)
        {
            return *this;
        }
        m_vec2 /= length;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Normalize(const TVector2<TInternalType> &v)
    {
        static_assert(std::numeric_limits<TInternalType>::is_iec559, "'Normalize' accepts only floating-point inputs");

        const TInternalType length = glm::length(v.m_vec2);
        if (length < k_epsilon)
        {
            return v;
        }

        const TVector2<TInternalType> vec(v.m_vec2 / length);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Reflect(const TVector2<TInternalType> &in,
                                                             const TVector2<TInternalType> &normal)
    {
        const auto reflect = glm::reflect(in.m_vec2, normal.m_vec2);
        const TVector2<TInternalType> v(reflect);
        return v;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>TVector2<TInternalType>:: Refract(const TVector2<TInternalType> &in,
                                                             const TVector2<TInternalType> &normal,
                                                             const TInternalType eta)
    {
        const auto refract = glm::refract(in.m_vec2, normal.m_vec2, eta);
        const TVector2<TInternalType> vec(refract);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::Scale(const TVector2<TInternalType> &v)
    {
        m_vec2 *= v.m_vec2;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> TVector2<TInternalType>::Scale(const TVector2<TInternalType> &v1,
                                                           const TVector2<TInternalType> &v2)
    {
        const TVector2<TInternalType> vec(v1.m_vec2 * v2.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::operator+=(const TVector2<TOtherInternalType> &v)
    {
        m_vec2 += v.m_vec2;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::operator-=(const TVector2<TOtherInternalType> &v)
    {
        m_vec2 -= v.m_vec2;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::operator*=(TOtherInternalType scalar)
    {
        m_vec2 *= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TVector2<TInternalType>& TVector2<TInternalType>::operator/=(TOtherInternalType scalar)
    {
        m_vec2 /= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    bool TVector2<TInternalType>::operator==(const TVector2<TInternalType> &v)
    {
        const bool are_equal = (m_vec2 == v.m_vec2);
        return are_equal;
    }

    template<TNumericalConcept TInternalType>
    bool TVector2<TInternalType>::operator!=(const TVector2<TInternalType> &v)
    {
        const bool are_not_equal = (m_vec2 != v.m_vec2);
        return are_not_equal;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> operator+(const TVector2<TInternalType> &v)
    {
        return v;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> operator-(const TVector2<TInternalType> &v)
    {
        const TVector2<TInternalType> vec(-v.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator+(const TVector2<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector2<TInternalType> vec(v.m_vec2 + scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> operator+(const TVector2<TInternalType> &v1, const TVector2<TInternalType> &v2)
    {
        const TVector2<TInternalType> vec(v1.m_vec2 + v2.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator+(const TOtherInternalType scalar, const TVector2<TInternalType> &v)
    {
        const TVector2<TInternalType> vec(scalar + v.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator-(const TVector2<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector2<TInternalType> vec(v.m_vec2 - scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    TVector2<TInternalType> operator-(const TVector2<TInternalType> &v1, const TVector2<TInternalType> &v2)
    {
        const TVector2<TInternalType> vec(v1.m_vec2 - v2.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator-(TOtherInternalType scalar, const TVector2<TInternalType> &v)
    {
        const TVector2<TInternalType> vec(scalar - v.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator*(const TVector2<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector2<TInternalType> vec(v.m_vec2 * scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator*(const TOtherInternalType scalar, const TVector2<TInternalType> &v)
    {
        const TVector2<TInternalType> vec(scalar * v.m_vec2);
        return vec;
    }

    template<TNumericalConcept TInternalType, TNumericalConcept TOtherInternalType>
    TVector2<TInternalType> operator/(const TVector2<TInternalType> &v, const TOtherInternalType scalar)
    {
        const TVector2<TInternalType> vec(v.m_vec2 / scalar);
        return vec;
    }

    template<TNumericalConcept TInternalType>
    std::string TVector2<TInternalType>::ToString() const
    {
        const std::string string = std::format("[{}, {}]", m_vec2.x, m_vec2.y);
        return string;
    }

    template<TNumericalConcept TInternalType>
    std::ostream& operator<<(std::ostream &os, const TVector2<TInternalType> &v)
    {
        return os << "[" << v.m_vec2.x << ", " << v.m_vec2.y << "]";
    }
}

#endif // M3GTR_SRC_MATH_TVECTOR2_HXX_INCLUDED
