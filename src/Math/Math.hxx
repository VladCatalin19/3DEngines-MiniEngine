#ifndef M3GTR_SRC_MATH_MATH_HXX_INCLUDED
#define M3GTR_SRC_MATH_MATH_HXX_INCLUDED

#include "TNumericalConcept.hxx"

#include <glm/glm.hpp>

#include <algorithm>
#include <concepts>

namespace MG3TR::Math
{
    template<std::floating_point TFloat>
    TFloat DegreesToRadians(const TFloat value);

    template<std::floating_point TFloat>
    TFloat RadiansToDegrees(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Sin(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Cos(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Tan(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Asin(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Acon(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Atan(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Atan2(const TFloat y, const TFloat x);

    template<std::floating_point TFloat>
    TFloat Pow(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Exp(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Log(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Exp2(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Log2(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Sqrt(const TFloat value);

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Abs(const TFloatOrInt value);

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Sign(const TFloatOrInt value);

    template<std::floating_point TFloat>
    TFloat Floor(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Trunc(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Round(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Ceil(const TFloat value);

    template<std::floating_point TFloat>
    TFloat Fract(const TFloat value);

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Mod(const TFloatOrInt x, const TFloatOrInt y);

    template <TNumericalConcept TFloatOrInt>
    TFloatOrInt Min(const TFloatOrInt value1, const TFloatOrInt value2);

    template <TNumericalConcept TFloatOrInt, TNumericalConcept... TFloatOrIntRest>
    TFloatOrInt Min(const TFloatOrInt value1, const TFloatOrInt value2, const TFloatOrIntRest&... values);

    template <TNumericalConcept TFloatOrInt>
    TFloatOrInt Max(const TFloatOrInt value1, const TFloatOrInt value2);

    template <TNumericalConcept TFloatOrInt, TNumericalConcept... TFloatOrIntRest>
    TFloatOrInt Max(const TFloatOrInt value1, const TFloatOrInt value2, const TFloatOrIntRest&... values);

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Clamp(const TFloatOrInt value, const TFloatOrInt min, const TFloatOrInt max);

    template<TNumericalConcept TFloatOrInt, std::floating_point TFloat>
    TFloatOrInt Lerp(const TFloatOrInt v1, const TFloatOrInt v2, const TFloat t);

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Step(const TFloatOrInt edge, const TFloatOrInt value);

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt SmoothStep(const TFloatOrInt edge1, const TFloatOrInt edge2, const TFloatOrInt value);
}

inline float operator""_deg(long double value);
inline float operator""_rad(long double value);

// Implementation
namespace MG3TR::Math
{
    template<std::floating_point TFloat>
    TFloat DegreesToRadians(const TFloat value)
    {
        const TFloat radians = glm::radians(value);
        return radians;
    }

    template<std::floating_point TFloat>
    TFloat RadiansToDegrees(const TFloat value)
    {
        const TFloat degrees = glm::degrees(value);
        return degrees;
    }

    template<std::floating_point TFloat>
    TFloat Sin(const TFloat value)
    {
        const TFloat sin = glm::sin(value);
        return sin;
    }

    template<std::floating_point TFloat>
    TFloat Cos(const TFloat value)
    {
        const TFloat cos = glm::cos(value);
        return cos;
    }

    template<std::floating_point TFloat>
    TFloat Tan(const TFloat value)
    {
        const TFloat tan = glm::tan(value);
        return tan;
    }

    template<std::floating_point TFloat>
    TFloat Asin(const TFloat value)
    {
        const TFloat asin = glm::asin(value);
        return asin;
    }

    template<std::floating_point TFloat>
    TFloat Acon(const TFloat value)
    {
        const TFloat acos = glm::acos(value);
        return acos;
    }

    template<std::floating_point TFloat>
    TFloat Atan(const TFloat value)
    {
        const TFloat atan = glm::atan(value);
        return atan;
    }

    template<std::floating_point TFloat>
    TFloat Atan2(const TFloat y, const TFloat x)
    {
        const TFloat atan2 = glm::atan(y, x);
        return atan2;
    }

    template<std::floating_point TFloat>
    TFloat Pow(const TFloat value)
    {
        const TFloat pow = glm::pow(value);
        return pow;
    }

    template<std::floating_point TFloat>
    TFloat Exp(const TFloat value)
    {
        const TFloat exp = glm::exp(value);
        return exp;
    }

    template<std::floating_point TFloat>
    TFloat Log(const TFloat value)
    {
        const TFloat log = glm::log(value);
        return log;
    }

    template<std::floating_point TFloat>
    TFloat Exp2(const TFloat value)
    {
        const TFloat exp2 = glm::exp2(value);
        return exp2;
    }

    template<std::floating_point TFloat>
    TFloat Log2(const TFloat value)
    {
        const TFloat log2 = glm::log2(value);
        return log2;
    }

    template<std::floating_point TFloat>
    TFloat Sqrt(const TFloat value)
    {
        const TFloat sqrt = glm::sqrt(value);
        return sqrt;
    }

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Abs(const TFloatOrInt value)
    {
        const TFloatOrInt abs = glm::abs(value);
        return abs;
    }

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Sign(const TFloatOrInt value)
    {
        const TFloatOrInt sign = glm::sign(value);
        return sign;
    }

    template<std::floating_point TFloat>
    TFloat Floor(const TFloat value)
    {
        const TFloat floor = glm::floor(value);
        return floor;
    }

    template<std::floating_point TFloat>
    TFloat Trunc(const TFloat value)
    {
        const TFloat trunc = glm::trunc(value);
        return trunc;
    }

    template<std::floating_point TFloat>
    TFloat Round(const TFloat value)
    {
        const TFloat round = glm::round(value);
        return round;
    }

    template<std::floating_point TFloat>
    TFloat Ceil(const TFloat value)
    {
        const TFloat ceil = glm::ceil(value);
        return ceil;
    }

    template<std::floating_point TFloat>
    TFloat Fract(const TFloat value)
    {
        const TFloat fract = glm::fract(value);
        return fract;
    }

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Mod(const TFloatOrInt x, const TFloatOrInt y)
    {
        const TFloatOrInt mod = glm::mod(x, y);
        return mod;
    }

    template <TNumericalConcept TFloatOrInt>
    TFloatOrInt Min(const TFloatOrInt value1, const TFloatOrInt value2)
    {
        const TFloatOrInt min = std::min(value1, value2);

        return min;
    }

    template <TNumericalConcept TFloatOrInt, TNumericalConcept... TFloatOrIntRest>
    TFloatOrInt Min(const TFloatOrInt value1, const TFloatOrInt value2, const TFloatOrIntRest&... values)
    {
        TFloatOrInt min = 0;

        if (sizeof...(values) == 0)
        {
            min = Min(value1, value2);
        }
        else
        {
            if (value1 < value2)
            {
                min = Min(value1, values...);
            }
            else
            {
                min = Min(value2, values...);
            }
        }

        return min;
    }

    template <TNumericalConcept TFloatOrInt>
    TFloatOrInt Max(const TFloatOrInt value1, const TFloatOrInt value2)
    {
        const TFloatOrInt max = std::max(value1, value2);

        return max;
    }

    template <TNumericalConcept TFloatOrInt, TNumericalConcept... TFloatOrIntRest>
    TFloatOrInt Max(const TFloatOrInt value1, const TFloatOrInt value2, const TFloatOrIntRest&... values)
    {
        TFloatOrInt max = 0;

        if (sizeof...(values) == 0)
        {
            max = Max(value1, value2);
        }
        else
        {
            if (value1 > value2)
            {
                max = Max(value1, values...);
            }
            else
            {
                max = Max(value2, values...);
            }
        }

        return max;
    }

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Clamp(const TFloatOrInt value, const TFloatOrInt min, const TFloatOrInt max)
    {
        const TFloatOrInt clamp = glm::clamp(value, min, max);
        return clamp;
    }

    template<TNumericalConcept TFloatOrInt, std::floating_point TFloat>
    TFloatOrInt Lerp(const TFloatOrInt v1, const TFloatOrInt v2, const TFloat t)
    {
        const TFloatOrInt mix = glm::mix(v1, v2, t);
        return mix;
    }

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt Step(const TFloatOrInt edge, const TFloatOrInt value)
    {
        const TFloatOrInt step = glm::step(edge, value);
        return step;
    }

    template<TNumericalConcept TFloatOrInt>
    TFloatOrInt SmoothStep(const TFloatOrInt edge1, const TFloatOrInt edge2, const TFloatOrInt value)
    {
        const TFloatOrInt smoothstep = glm::smoothstep(edge1, edge2, value);
        return smoothstep;
    }
}

inline float operator""_deg(long double value)
{
    return MG3TR::Math::RadiansToDegrees(static_cast<float>(value));
}

inline float operator""_rad(long double value)
{
    return MG3TR::Math::DegreesToRadians(static_cast<float>(value));
}

#endif // M3GTR_SRC_MATH_MATH_HXX_INCLUDED
