#ifndef M3GTR_SRC_MATH_TMATRIX4X4_HXX_INCLUDED
#define M3GTR_SRC_MATH_TMATRIX4X4_HXX_INCLUDED

#include "TQuaternion.hxx"
#include "TVector3.hxx"
#include "TVector4.hxx"
#include "Utils/ExceptionWithStacktrace.hpp"

#include <Utils/ExceptionWithStacktrace.hpp>

#define GLM_FORCE_XYZW_ONLY 1
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <format>
#include <ostream>
#include <string>

namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    class TMatrix4x4
    {
    private:
        glm::tmat4x4<TInternalType> m_mat4x4;

        TMatrix4x4(const glm::tmat4x4<TInternalType>& mat4x4);

    public:
        TMatrix4x4(const TInternalType value_on_diagonal = static_cast<TInternalType>(0));
        TMatrix4x4(const TInternalType m00, const TInternalType m01, const TInternalType m02, const TInternalType m03,
                   const TInternalType m10, const TInternalType m11, const TInternalType m12, const TInternalType m13,
                   const TInternalType m20, const TInternalType m21, const TInternalType m22, const TInternalType m23,
                   const TInternalType m30, const TInternalType m31, const TInternalType m32, const TInternalType m33);
        TMatrix4x4(const TVector4<TInternalType> &c0, const TVector4<TInternalType> &c1,
                   const TVector4<TInternalType> &c2, const TVector4<TInternalType> &c3);
        TMatrix4x4(const TMatrix4x4<TInternalType> &m);
        TMatrix4x4(TMatrix4x4<TInternalType> &&m);

        TMatrix4x4<TInternalType>& operator=(const TMatrix4x4<TInternalType> &m);
        TMatrix4x4<TInternalType>& operator=(TMatrix4x4<TInternalType> &&m);

        TVector4<TInternalType> operator[](const std::size_t index) const;
        TInternalType& operator[](const std::size_t row, const std::size_t col);
        const TInternalType& operator[](const std::size_t row, const std::size_t col) const;

        TVector4<TInternalType> at(const std::size_t index) const;
        TInternalType& at(const std::size_t row, const std::size_t col);
        const TInternalType& at(const std::size_t row, const std::size_t col) const;

        static std::size_t Size();

        TInternalType* InternalDataPointer();
        const TInternalType* InternalDataPointer() const;

        static TMatrix4x4<TInternalType> LookAt(const TVector3<TInternalType> &eye,
                                                const TVector3<TInternalType> &center,
                                                const TVector3<TInternalType> &up);

        static TMatrix4x4<TInternalType> Perspective(const TInternalType fov, const TInternalType aspect,
                                                     const TInternalType znear, const TInternalType zfar);

        static TMatrix4x4<TInternalType> Orthographic(const TInternalType xmin, const TInternalType xmax,
                                                      const TInternalType ymin, const TInternalType ymax,
                                                      const TInternalType zmin, const TInternalType zmax);

        TMatrix4x4<TInternalType>& Translate(const TVector3<TInternalType> &v);
        static TMatrix4x4<TInternalType> Translate(const TMatrix4x4<TInternalType> &m,
                                                   const TVector3<TInternalType> &v);

        TMatrix4x4<TInternalType>& Scale(const TVector3<TInternalType> &v);
        static TMatrix4x4<TInternalType> Scale(const TMatrix4x4<TInternalType> &m,
                                               const TVector3<TInternalType> &v);

        TMatrix4x4<TInternalType>& Rotate(const TInternalType angle, const TVector3<TInternalType> &axis);
        static TMatrix4x4<TInternalType> Rotate(const TMatrix4x4<TInternalType> &m,
                                                const TInternalType angle,
                                                const TVector3<TInternalType> &axis);

        TMatrix4x4<TInternalType>& Rotate(const TQuaternion<TInternalType> &q);
        static TMatrix4x4<TInternalType> Rotate(const TMatrix4x4<TInternalType> &m,
                                                const TQuaternion<TInternalType> &q);

        TMatrix4x4<TInternalType>& Transpose();
        static TMatrix4x4<TInternalType> Transpose(const TMatrix4x4<TInternalType> &m);

        TMatrix4x4<TInternalType>& Inverse();
        static TMatrix4x4<TInternalType> Inverse(const TMatrix4x4<TInternalType> &m);

        template<TNumericalConcept TOtherInternalType>
        TMatrix4x4<TInternalType>& operator+=(const TMatrix4x4<TOtherInternalType> &m);

        template<TNumericalConcept TOtherInternalType>
        TMatrix4x4<TInternalType>& operator-=(const TMatrix4x4<TOtherInternalType> &m);

        template<TNumericalConcept TOtherInternalType>
        TMatrix4x4<TInternalType>& operator*=(const TMatrix4x4<TOtherInternalType> &m);

        template<TNumericalConcept TOtherInternalType>
        TMatrix4x4<TInternalType>& operator*=(const TOtherInternalType scalar);

        template<TNumericalConcept TOtherInternalType>
        TMatrix4x4<TInternalType>& operator/=(const TOtherInternalType scalar);

        bool operator==(const TMatrix4x4<TInternalType> &m);
        bool operator!=(const TMatrix4x4<TInternalType> &m);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator+(const TMatrix4x4<TInternal> &m);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator-(const TMatrix4x4<TInternal> &m);

        template<TNumericalConcept TInternal, TNumericalConcept TOtherInternalType>
        friend TMatrix4x4<TInternal> operator+(const TMatrix4x4<TInternal> &m,
                                               const TOtherInternalType scalar);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator+(const TMatrix4x4<TInternal> &m1,
                                               const TMatrix4x4<TInternal> &m2);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator+(const TInternal scalar,
                                               const TMatrix4x4<TInternal> &m);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator-(const TMatrix4x4<TInternal> &m,
                                               const TInternal scalar);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator-(const TMatrix4x4<TInternal> &m1,
                                               const TMatrix4x4<TInternal> &m2);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator-(const TInternal scalar,
                                               const TMatrix4x4<TInternal> &m);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator*(const TMatrix4x4<TInternal> &m,
                                               const TInternal scalar);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator*(const TInternal scalar,
                                               const TMatrix4x4<TInternal> &m);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator*(const TMatrix4x4<TInternal> &m,
                                             const TVector4<TInternal> &v);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator*(const TMatrix4x4<TInternal> &m1,
                                               const TMatrix4x4<TInternal> &m2);

        template<TNumericalConcept TInternal>
        friend TMatrix4x4<TInternal> operator/(const TMatrix4x4<TInternal> &m,
                                               const TInternal scalar);

        template<TNumericalConcept TInternal>
        friend TVector4<TInternal> operator/(const TMatrix4x4<TInternal> &m,
                                             const TVector4<TInternal> &v);

        std::string ToString(const std::string &row_indent = "") const;
        template<TNumericalConcept TInternal>
        friend std::ostream& operator<<(std::ostream &os, const TMatrix4x4<TInternal> &m);
    };
}

// Implementation
namespace MG3TR::MathInternal
{
    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>::TMatrix4x4(const glm::tmat4x4<TInternalType> &mat4x4)
        : m_mat4x4(mat4x4)
    {

    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>::TMatrix4x4(const TInternalType value_on_diagonal)
        : m_mat4x4(value_on_diagonal)
    {

    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>::TMatrix4x4(const TInternalType m00, const TInternalType m01, const TInternalType m02, const TInternalType m03,
                                          const TInternalType m10, const TInternalType m11, const TInternalType m12, const TInternalType m13,
                                          const TInternalType m20, const TInternalType m21, const TInternalType m22, const TInternalType m23,
                                          const TInternalType m30, const TInternalType m31, const TInternalType m32, const TInternalType m33)
        : m_mat4x4(m00, m01, m02, m03,
                   m10, m11, m12, m13,
                   m20, m21, m22, m23,
                   m30, m31, m32, m33)
    {

    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>::TMatrix4x4(const TVector4<TInternalType> &c0, const TVector4<TInternalType> &c1,
                                          const TVector4<TInternalType> &c2, const TVector4<TInternalType> &c3)
        : m_mat4x4(c0.x(), c0.y(), c0.z(), c0.w(),
                   c1.x(), c1.y(), c1.z(), c1.w(),
                   c2.x(), c2.y(), c2.z(), c2.w(),
                   c3.x(), c3.y(), c3.z(), c3.w())
    {

    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>::TMatrix4x4(const TMatrix4x4<TInternalType> &m)
        : m_mat4x4(m.m_mat4x4)
    {

    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>::TMatrix4x4(TMatrix4x4<TInternalType> &&m)
        : m_mat4x4(std::move(m.m_mat4x4))
    {

    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator=(const TMatrix4x4<TInternalType> &m)
    {
        m_mat4x4 = m.m_mat4x4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator=(TMatrix4x4<TInternalType> &&m)
    {
        m_mat4x4 = std::move(m.m_mat4x4);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TMatrix4x4<TInternalType>::operator[](const std::size_t index) const
    {
        const glm::tvec4<TInternalType> col = m_mat4x4[index];
        const auto v = TVector4<TInternalType>(col.x, col.y, col.z, col.w);

        return v;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TMatrix4x4<TInternalType>::operator[](const std::size_t row, const std::size_t col)
    {
        glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        TInternalType &value = col_vec[row];

        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TMatrix4x4<TInternalType>::operator[](const std::size_t row, const std::size_t col) const
    {
        const glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        const TInternalType &value = col_vec[row];
        
        return value;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> TMatrix4x4<TInternalType>::at(const std::size_t index) const
    {
        const std::size_t size = Size();

        if (index >= size)
        {
            const std::string error = std::format("Index {} is an invalid matrix4x4 subscript.", index);
            throw ExceptionWithStacktrace(error);
        }
        const glm::tvec4<TInternalType> col = m_mat4x4[index];
        const auto v = TVector4<TInternalType>(col.x, col.y, col.z, col.w);

        return v;
    }

    template<TNumericalConcept TInternalType>
    TInternalType& TMatrix4x4<TInternalType>::at(const std::size_t row, const std::size_t col)
    {
        const std::size_t size = Size();

        if ((row >= size) || (col >= size))
        {
            const std::string error = std::format("Position [{}, {}] is an invalid matrix4x4 position.", row, col);
            throw ExceptionWithStacktrace(error);
        }

        glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        TInternalType &value = col_vec[row];

        return value;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType& TMatrix4x4<TInternalType>::at(const std::size_t row, const std::size_t col) const
    {
        const std::size_t size = Size();

        if ((row >= size) || (col >= size))
        {
            const std::string error = std::format("Position [{}, {}] is an invalid matrix4x4 position.", row, col);
            throw ExceptionWithStacktrace(error);
        }

        const glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        const TInternalType &value = col_vec[row];
        
        return value;
    }
    
    template<TNumericalConcept TInternalType>
    std::size_t TMatrix4x4<TInternalType>::Size()
    {
        return static_cast<std::size_t>(4);
    }

    template<TNumericalConcept TInternalType>
    TInternalType* TMatrix4x4<TInternalType>::InternalDataPointer()
    {
        TInternalType * const ptr = glm::value_ptr(m_mat4x4);
        return ptr;
    }

    template<TNumericalConcept TInternalType>
    const TInternalType* TMatrix4x4<TInternalType>::InternalDataPointer() const
    {
        const TInternalType * const ptr = glm::value_ptr(m_mat4x4);
        return ptr;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::LookAt(const TVector3<TInternalType> &eye,
                                                                const TVector3<TInternalType> &center,
                                                                const TVector3<TInternalType> &up)
    {
        const auto look_at = glm::lookAt(glm::tvec3<TInternalType>(eye.x(), eye.y(), eye.z()),
                                         glm::tvec3<TInternalType>(center.x(), center.y(), center.z()),
                                         glm::tvec3<TInternalType>(up.x(), up.y(), up.z()));
        const TMatrix4x4<TInternalType> mat(look_at);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Perspective(const TInternalType fov, const TInternalType aspect,
                                                                     const TInternalType znear, const TInternalType zfar)
    {
        const auto perspective = glm::perspective(fov, aspect, znear, zfar);
        const TMatrix4x4<TInternalType> mat(perspective);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Orthographic(const TInternalType xmin, const TInternalType xmax,
                                                                      const TInternalType ymin, const TInternalType ymax,
                                                                      const TInternalType zmin, const TInternalType zmax)
    {
        const auto ortho = glm::ortho(xmin, xmax, ymin, ymax, zmin, zmax);
        const TMatrix4x4<TInternalType> mat(ortho);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Translate(const TVector3<TInternalType> &v)
    {
        const auto translation = glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        m_mat4x4 = glm::translate(m_mat4x4, translation);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Translate(const TMatrix4x4<TInternalType> &m,
                                                                   const TVector3<TInternalType> &v)
    {
        const auto translation = glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        const auto mat4 = glm::translate(m.m_mat4x4, translation);
        const TMatrix4x4<TInternalType> mat(mat4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Scale(const TVector3<TInternalType> &v)
    {
        const auto scale = glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        m_mat4x4 = glm::scale(m_mat4x4, scale);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Scale(const TMatrix4x4<TInternalType> &m,
                                                               const TVector3<TInternalType> &v)
    {
        const auto scale = glm::tvec3<TInternalType>(v.x(), v.y(), v.z());
        const auto mat4 = glm::scale(m.m_mat4x4, scale);
        const TMatrix4x4<TInternalType> mat(mat4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Rotate(const TInternalType angle,
                                                                 const TVector3<TInternalType> &axis)
    {
        const auto rotate = glm::tvec3<TInternalType>(axis.x(), axis.y(), axis.z());
        m_mat4x4 = glm::rotate(m_mat4x4, angle, rotate);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Rotate(const TMatrix4x4<TInternalType> &m,
                                                                const TInternalType angle,
                                                                const TVector3<TInternalType> &axis)
    {
        const auto rotate = glm::tvec3<TInternalType>(axis.x(), axis.y(), axis.z());
        const auto mat4 = glm::rotate(m.m_mat4x4, angle, rotate);
        const TMatrix4x4<TInternalType> mat(mat4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Rotate(const TQuaternion<TInternalType> &q)
    {
        const glm::quat qu(q.w(), q.x(), q.y(), q.z());
        const auto mat = glm::toMat4(qu);
        m_mat4x4 *= mat;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Rotate(const TMatrix4x4<TInternalType> &m,
                                                                const TQuaternion<TInternalType> &q)
    {
        const glm::quat qu(q.w(), q.x(), q.y(), q.z());
        const auto mat4 = m.m_mat4x4 * glm::toMat4(qu);
        const TMatrix4x4<TInternalType> mat(mat4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Transpose()
    {
        m_mat4x4 = glm::transpose(m_mat4x4);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Transpose(const TMatrix4x4<TInternalType> &m)
    {
        const auto transpose = glm::transpose(m.m_mat4x4);
        const TMatrix4x4<TInternalType> mat(transpose); 
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Inverse()
    {
        m_mat4x4 = glm::inverse(m_mat4x4);
        return *this;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Inverse(const TMatrix4x4<TInternalType> &m)
    {
        const auto inverse = glm::inverse(m.m_mat4x4);
        TMatrix4x4<TInternalType> mat(inverse);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator+=(const TMatrix4x4<TOtherInternalType> &m)
    {
        m_mat4x4 += m.m_mat4x4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator-=(const TMatrix4x4<TOtherInternalType> &m)
    {
        m_mat4x4 -= m.m_mat4x4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator*=(const TMatrix4x4<TOtherInternalType> &m)
    {
        m_mat4x4 *= m.m_mat4x4;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator*=(TOtherInternalType scalar)
    {
        m_mat4x4 *= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    template<TNumericalConcept TOtherInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator/=(TOtherInternalType scalar)
    {
        m_mat4x4 /= scalar;
        return *this;
    }

    template<TNumericalConcept TInternalType>
    bool TMatrix4x4<TInternalType>::operator==(const TMatrix4x4<TInternalType> &m)
    {
        const bool are_equal = (m_mat4x4 == m.m_mat4x4);
        return are_equal;
    }

    template<TNumericalConcept TInternalType>
    bool TMatrix4x4<TInternalType>::operator!=(const TMatrix4x4<TInternalType> &m)
    {
        const bool are_not_equal = (m_mat4x4 != m.m_mat4x4);
        return are_not_equal;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator+(const TMatrix4x4<TInternalType> &m)
    {
        return m;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator-(const TMatrix4x4<TInternalType> &m)
    {
        const TMatrix4x4<TInternalType> mat(-m.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator+(const TMatrix4x4<TInternalType> &m,
                                        const TInternalType scalar)
    {
        const TMatrix4x4<TInternalType> mat(m.m_mat4x4 + scalar);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator+(const TMatrix4x4<TInternalType> &m1,
                                        const TMatrix4x4<TInternalType> &m2)
    {
        const TMatrix4x4<TInternalType> mat(m1.m_mat4x4 + m2.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator+(const TInternalType scalar,
                                        const TMatrix4x4<TInternalType> &m)
    {
        const TMatrix4x4<TInternalType> mat(scalar + m.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator-(const TMatrix4x4<TInternalType> &m,
                                        const TInternalType scalar)
    {
        const TMatrix4x4<TInternalType> mat(m.m_mat4x4 - scalar);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator-(const TMatrix4x4<TInternalType> &m1,
                                        const TMatrix4x4<TInternalType> &m2)
    {
        const TMatrix4x4<TInternalType> mat(m1.m_mat4x4 - m2.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator-(const TInternalType scalar,
                                        const TMatrix4x4<TInternalType> &m)
    {
        const TMatrix4x4<TInternalType> mat(scalar - m.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator*(const TMatrix4x4<TInternalType> &m,
                                        const TInternalType scalar)
    {
        const TMatrix4x4<TInternalType> mat(m.m_mat4x4 * scalar);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator*(const TInternalType scalar,
                                        const TMatrix4x4<TInternalType> &m)
    {
        const TMatrix4x4<TInternalType> mat(scalar * m.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator*(const TMatrix4x4<TInternalType> &m,
                                      const TVector4<TInternalType> &v)
    {
        const glm::tvec4<TInternalType> vec4(v.x(), v.y(), v.z(), v.w());
        const glm::tvec4<TInternalType> res = m.m_mat4x4 * vec4;
        const TVector4<TInternalType> res4(res.x, res.y, res.z, res.w);
        return res4;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator*(const TMatrix4x4<TInternalType> &m1,
                                        const TMatrix4x4<TInternalType> &m2)
    {
        const TMatrix4x4<TInternalType> mat(m1.m_mat4x4 * m2.m_mat4x4);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TMatrix4x4<TInternalType> operator/(const TMatrix4x4<TInternalType> &m,
                                        const TInternalType scalar)
    {
        const TMatrix4x4<TInternalType> mat(m.m_mat4x4 / scalar);
        return mat;
    }

    template<TNumericalConcept TInternalType>
    TVector4<TInternalType> operator/(const TMatrix4x4<TInternalType> &m,
                                      const TVector4<TInternalType> &v)
    {
        const glm::tvec4<TInternalType> vec4(v.x(), v.y(), v.z(), v.w());
        const glm::tvec4<TInternalType> res = m.m_mat4x4 / vec4;
        const TVector4<TInternalType> res4(res.x, res.y, res.z, res.w);
        return res4;
    }

    template<TNumericalConcept TInternalType>
    std::string TMatrix4x4<TInternalType>::ToString(const std::string &row_indent) const
    {
        const std::size_t size = Size();
        std::string result;

        for (std::size_t index = 0; index < size; ++index)
        {
            const glm::tvec4<TInternalType> vec = m_mat4x4[index];
            const std::string temp = std::format("[{}, {}, {}]\n", vec.x, vec.y, vec.z);

            result += temp;
            result += row_indent;
        }
        return result;
    }

    template<TNumericalConcept TInternalType>
    std::ostream& operator<<(std::ostream &os, const TMatrix4x4<TInternalType> &m)
    {
        for (std::size_t index = 0; index < m.Size(); ++index)
        {
            glm::tvec4<TInternalType> vec = m.m_mat4x4[index];
            os << "[" << vec.x
               << ", " + vec.y
               << ", " + vec.z
               << ", " + vec.w << "]\n";
        }
        return os;
    }
}

#endif // M3GTR_SRC_MATH_TMATRIX4X4_HXX_INCLUDED
