
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/glm.hpp>                          // glm::tmat4x4, glm::tvec4, glm::tmat4x4, glm::lookAt, glm::translate,
                                                // glm::scale, glm::rotate, glm::transpose, glm::inverse
#include <glm/gtc/type_ptr.hpp>                 // glm::value_ptr
#include <glm/gtx/quaternion.hpp>               // glm::toMat4
#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <memory>               // std::move
#include <ostream>              // std::ostream
#include <stdexcept>            // std::out_of_range
#include <string>               // std::string, std::to_string
#include <utility>              // std::pair

namespace MG3TR
{
    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>::TMatrix4x4(const glm::tmat4x4<TInternalType> &mat4x4) noexcept
        : m_mat4x4(mat4x4)
    {}

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>::TMatrix4x4(TInternalType value_on_diagonal) noexcept
        : m_mat4x4(value_on_diagonal)
    {}

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>::TMatrix4x4(TInternalType m00, TInternalType m01, TInternalType m02, TInternalType m03,
                                                    TInternalType m10, TInternalType m11, TInternalType m12, TInternalType m13,
                                                    TInternalType m20, TInternalType m21, TInternalType m22, TInternalType m23,
                                                    TInternalType m30, TInternalType m31, TInternalType m32, TInternalType m33) noexcept
        : m_mat4x4(m00, m01, m02, m03,
                   m10, m11, m12, m13,
                   m20, m21, m22, m23,
                   m30, m31, m32, m33)
    {}

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>::TMatrix4x4(const TVector4<TInternalType> &c0, const TVector4<TInternalType> &c1,
                                                    const TVector4<TInternalType> &c2, const TVector4<TInternalType> &c3) noexcept
        : m_mat4x4(c0.x(), c0.y(), c0.z(), c0.w(),
                   c1.x(), c1.y(), c1.z(), c1.w(),
                   c2.x(), c2.y(), c2.z(), c2.w(),
                   c3.x(), c3.y(), c3.z(), c3.w())
    {}

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>::TMatrix4x4(const TMatrix4x4<TInternalType> &m) noexcept
        : m_mat4x4(m.m_mat4x4)
    {}

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>::TMatrix4x4(TMatrix4x4<TInternalType> &&m) noexcept
        : m_mat4x4(std::move(m.m_mat4x4))
    {}

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator=(const TMatrix4x4<TInternalType> &m) noexcept
    {
        m_mat4x4 = m.m_mat4x4;
        return *this;
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator=(TMatrix4x4<TInternalType> &&m) noexcept
    {
        m_mat4x4 = std::move(m.m_mat4x4);
        return *this;
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> TMatrix4x4<TInternalType>::operator[](std::size_t index) const noexcept
    {
        glm::tvec4<TInternalType> col = m_mat4x4[index];
        return TVector4<TInternalType>(col.x, col.y, col.z, col.w);
    }

    template<typename TInternalType>
    constexpr TInternalType& TMatrix4x4<TInternalType>::operator[](const std::pair<std::size_t, std::size_t> &position) noexcept
    {
        auto &[row, col] = position;
        glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        return col_vec[row];
    }

    template<typename TInternalType>
    constexpr const TInternalType& TMatrix4x4<TInternalType>::operator[](const std::pair<std::size_t, std::size_t> &position) const noexcept
    {
        auto &[row, col] = position;
        glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        return col_vec[row];
    }

    template<typename TInternalType>
    TVector4<TInternalType> TMatrix4x4<TInternalType>::at(std::size_t index) const try
    {
        if (index >= Size())
        {
            throw std::out_of_range("Index " + std::to_string(index) + " is an invalid matrix4x4 subscript");
        }
        glm::tvec4<TInternalType> col = m_mat4x4[index];
        return TVector4<TInternalType>(col.x, col.y, col.z, col.w);
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    TInternalType& TMatrix4x4<TInternalType>::at(const std::pair<std::size_t, std::size_t> &position) noexcept
    {
        auto &[row, col] = position;
        if ((row >= Size()) || (col >= Size()))
        {
            throw std::out_of_range("Position [" + std::to_string(position.first) + ", "
                                    + std::to_string(position.second)
                                    + "] is an invalid matrix4x4 position");
        }

        glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        return col_vec[row];
    }

    template<typename TInternalType>
    const TInternalType& TMatrix4x4<TInternalType>::at(const std::pair<std::size_t, std::size_t> &position) const noexcept
    {
        auto &[row, col] = position;
        if constexpr ((row >= Size()) || (col >= Size()))
        {
            throw std::out_of_range("Position [" + std::to_string(position.first) + ", "
                                    + std::to_string(position.second)
                                    + "] is an invalid matrix4x4 position");
        }

        glm::tvec4<TInternalType> &col_vec = m_mat4x4[col];
        return col_vec[row];
    }
    
    template<typename TInternalType>
    constexpr std::size_t TMatrix4x4<TInternalType>::Size() noexcept
    {
        return static_cast<std::size_t>(4);
    }

    template<typename TInternalType>
    TInternalType* TMatrix4x4<TInternalType>::InternalDataPointer() noexcept
    {
        return glm::value_ptr(m_mat4x4);
    }

    template<typename TInternalType>
    const TInternalType* TMatrix4x4<TInternalType>::InternalDataPointer() const noexcept
    {
        return glm::value_ptr(m_mat4x4);
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::LookAt(const TVector3<TInternalType> &eye,
                                                                const TVector3<TInternalType> &center,
                                                                const TVector3<TInternalType> &up) noexcept
    {
        return TMatrix4x4<TInternalType>(glm::lookAt(glm::tvec3<TInternalType>(eye.x(), eye.y(), eye.z()),
                                                     glm::tvec3<TInternalType>(center.x(), center.y(), center.z()),
                                                     glm::tvec3<TInternalType>(up.x(), up.y(), up.z())));
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Perspective(TInternalType fov, TInternalType aspect,
                                                                     TInternalType znear, TInternalType zfar) noexcept
    {
        return TMatrix4x4<TInternalType>(glm::perspective(fov, aspect, znear, zfar));
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Orthographic(TInternalType xmin, TInternalType xmax,
                                                                      TInternalType ymin, TInternalType ymax,
                                                                      TInternalType zmin, TInternalType zmax) noexcept
    {
        return TMatrix4x4<TInternalType>(glm::ortho(xmin, xmax, ymin, ymax, zmin, zmax));
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Translate(const TVector3<TInternalType> &v) noexcept
    {
        m_mat4x4 = glm::translate(m_mat4x4, glm::tvec3<TInternalType>(v.x(), v.y(), v.z()));
        return *this;
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Translate(const TMatrix4x4<TInternalType> &m,
                                                                   const TVector3<TInternalType> &v) noexcept
    {
        auto mat4 = glm::translate(m.m_mat4x4, glm::tvec3<TInternalType>(v.x(), v.y(), v.z()));
        return TMatrix4x4<TInternalType>(mat4);
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Scale(const TVector3<TInternalType> &v) noexcept
    {
        m_mat4x4 = glm::scale(m_mat4x4, glm::tvec3<TInternalType>(v.x(), v.y(), v.z()));
        return *this;
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Scale(const TMatrix4x4<TInternalType> &m,
                                                               const TVector3<TInternalType> &v) noexcept
    {
        auto mat4 = glm::scale(m.m_mat4x4, glm::tvec3<TInternalType>(v.x(), v.y(), v.z()));
        return TMatrix4x4<TInternalType>(mat4);
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Rotate(TInternalType angle,
                                                                 const TVector3<TInternalType> &axis) noexcept
    {
        m_mat4x4 = glm::rotate(m_mat4x4, angle, glm::tvec3<TInternalType>(axis.x(), axis.y(), axis.z()));
        return *this;
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Rotate(const TMatrix4x4<TInternalType> &m,
                                                                TInternalType angle,
                                                                const TVector3<TInternalType> &axis) noexcept
    {
        auto mat4 = glm::rotate(m.m_mat4x4, angle, glm::tvec3<TInternalType>(axis.x(), axis.y(), axis.z()));
        return TMatrix4x4<TInternalType>(mat4);
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Rotate(const TQuaternion<TInternalType> &q) noexcept
    {
        glm::quat qu(q.w(), q.x(), q.y(), q.z());
        m_mat4x4 *= glm::toMat4(qu);
        return *this;
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Rotate(const TMatrix4x4<TInternalType> &m,
                                                                const TQuaternion<TInternalType> &q) noexcept
    {
        glm::quat qu(q.w(), q.x(), q.y(), q.z());
        auto mat4 = m.m_mat4x4 * glm::toMat4(qu);
        return TMatrix4x4<TInternalType>(mat4);
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Transpose() noexcept
    {
        m_mat4x4 = glm::transpose(m_mat4x4);
        return *this;
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Transpose(const TMatrix4x4<TInternalType> &m) noexcept
    {
        return TMatrix4x4<TInternalType>(glm::transpose(m.m_mat4x4));
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::Inverse() noexcept
    {
        m_mat4x4 = glm::inverse(m_mat4x4);
        return *this;
    }

    template<typename TInternalType>
    TMatrix4x4<TInternalType> TMatrix4x4<TInternalType>::Inverse(const TMatrix4x4<TInternalType> &m) noexcept
    {
        return TMatrix4x4<TInternalType>(glm::inverse(m.m_mat4x4));
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator+=(const TMatrix4x4<TOtherInternalType> &m) noexcept
    {
        m_mat4x4 += m.m_mat4x4;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator-=(const TMatrix4x4<TOtherInternalType> &m) noexcept
    {
        m_mat4x4 -= m.m_mat4x4;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator*=(const TMatrix4x4<TOtherInternalType> &m) noexcept
    {
        m_mat4x4 *= m.m_mat4x4;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator*=(TOtherInternalType scalar) noexcept
    {
        m_mat4x4 *= scalar;
        return *this;
    }

    template<typename TInternalType>
    template<typename TOtherInternalType>
    constexpr TMatrix4x4<TInternalType>& TMatrix4x4<TInternalType>::operator/=(TOtherInternalType scalar) noexcept
    {
        m_mat4x4 /= scalar;
        return *this;
    }

    template<typename TInternalType>
    constexpr bool TMatrix4x4<TInternalType>::operator==(const TMatrix4x4<TInternalType> &m) noexcept
    {
        return m_mat4x4 == m.m_mat4x4;
    }

    template<typename TInternalType>
    constexpr bool TMatrix4x4<TInternalType>::operator!=(const TMatrix4x4<TInternalType> &m) noexcept
    {
        return m_mat4x4 != m.m_mat4x4;
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator+(const TMatrix4x4<TInternalType> &m) noexcept
    {
        return m;
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator-(const TMatrix4x4<TInternalType> &m) noexcept
    {
        return TMatrix4x4<TInternalType>(-m.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator+(const TMatrix4x4<TInternalType> &m,
                                                  TInternalType scalar) noexcept
    {
        return TMatrix4x4<TInternalType>(m.m_mat4x4 + scalar);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator+(const TMatrix4x4<TInternalType> &m1,
                                                  const TMatrix4x4<TInternalType> &m2) noexcept
    {
        return TMatrix4x4<TInternalType>(m1.m_mat4x4 + m2.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator+(TInternalType scalar,
                                                  const TMatrix4x4<TInternalType> &m) noexcept
    {
        return TMatrix4x4<TInternalType>(scalar + m.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator-(const TMatrix4x4<TInternalType> &m,
                                                  TInternalType scalar) noexcept
    {
        return TMatrix4x4<TInternalType>(m.m_mat4x4 - scalar);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator-(const TMatrix4x4<TInternalType> &m1,
                                                  const TMatrix4x4<TInternalType> &m2) noexcept
    {
        return TMatrix4x4<TInternalType>(m1.m_mat4x4 - m2.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator-(TInternalType scalar,
                                                  const TMatrix4x4<TInternalType> &m) noexcept
    {
        return TMatrix4x4<TInternalType>(scalar - m.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator*(const TMatrix4x4<TInternalType> &m,
                                                  TInternalType scalar) noexcept
    {
        return TMatrix4x4<TInternalType>(m.m_mat4x4 * scalar);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator*(TInternalType scalar,
                                                  const TMatrix4x4<TInternalType> &m) noexcept
    {
        return TMatrix4x4<TInternalType>(scalar * m.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator*(const TMatrix4x4<TInternalType> &m,
                                                const TVector4<TInternalType> &v) noexcept
    {
        glm::tvec4<TInternalType> vec4(v.x(), v.y(), v.z(), v.w());
        //typename glm::tmat4x4<TInternalType>::col_type vec4(v.x(), v.y(), v.z(), v.w());
        glm::tvec4<TInternalType> res = m.m_mat4x4 * vec4;
        return TVector4<TInternalType>(res.x, res.y, res.z, res.w);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator*(const TMatrix4x4<TInternalType> &m1,
                                                  const TMatrix4x4<TInternalType> &m2) noexcept
    {
        return TMatrix4x4<TInternalType>(m1.m_mat4x4 * m2.m_mat4x4);
    }

    template<typename TInternalType>
    constexpr TMatrix4x4<TInternalType> operator/(const TMatrix4x4<TInternalType> &m,
                                                  TInternalType scalar) noexcept
    {
        return TMatrix4x4<TInternalType>(m.m_mat4x4 / scalar);
    }

    template<typename TInternalType>
    constexpr TVector4<TInternalType> operator/(const TMatrix4x4<TInternalType> &m,
                                                const TVector4<TInternalType> &v) noexcept
    {
        glm::tvec4<TInternalType> vec4(v.x(), v.y(), v.z(), v.w());
        glm::tvec4<TInternalType> res = m.m_mat4x4 / vec4;
        return TVector4<TInternalType>(res.x, res.y, res.y, res.w);
    }

    template<typename TInternalType>
    std::string TMatrix4x4<TInternalType>::ToString(const std::string &row_indent) const try
    {
        std::string result;
        for (std::size_t index = 0; index < Size(); ++index)
        {
            glm::tvec4<TInternalType> vec = m_mat4x4[index];
            result += "[" + std::to_string(vec.x)
                        + ", " + std::to_string(vec.y)
                        + ", " + std::to_string(vec.z)
                        + ", " + std::to_string(vec.w) + "]\n";
            result += row_indent;
        }
        return result;
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TInternalType>
    std::ostream& operator<<(std::ostream &os, const TMatrix4x4<TInternalType> &m) try
    {
        for (std::size_t index = 0; index < m.Size(); ++index)
        {
            glm::tvec4<TInternalType> vec = m.m_mat4x4[index];
            os << "[" << std::to_string(vec.x)
                << ", " + std::to_string(vec.y)
                << ", " + std::to_string(vec.z)
                << ", " + std::to_string(vec.w) << "]\n";
        }
        return os;
    }
    CATCH_RETHROW_EXCEPTIONS
}