
#include <glm/glm.hpp>          // glm::*

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

namespace MG3TR
{
    template<typename TFloat>
    constexpr TFloat Math::DegreesToRadians(const TFloat &value) noexcept
    {
        return glm::radians(value);
    }

    template<typename TFloat>
    constexpr TFloat Math::RadiansToDegrees(const TFloat &value) noexcept
    {
        return glm::degrees(value);
    }

    template<typename TFloat>
    TFloat Math::Sin(const TFloat &value) noexcept
    {
        return glm::sin(value);
    }

    template<typename TFloat>
    TFloat Math::Cos(const TFloat &value) noexcept
    {
        return glm::cos(value);
    }

    template<typename TFloat>
    TFloat Math::Tan(const TFloat &value) noexcept
    {
        return glm::tan(value);
    }

    template<typename TFloat>
    TFloat Math::Asin(const TFloat &value) noexcept
    {
        return glm::asin(value);
    }

    template<typename TFloat>
    TFloat Math::Acon(const TFloat &value) noexcept
    {
        return glm::acos(value);
    }

    template<typename TFloat>
    TFloat Math::Atan(const TFloat &value) noexcept
    {
        return glm::atan(value);
    }

    template<typename TFloat>
    TFloat Math::Atan2(const TFloat &y, const TFloat &x) noexcept
    {
        return glm::atan(y, x);
    }

    template<typename TFloat>
    TFloat Math::Pow(const TFloat &value) noexcept
    {
        return glm::pow(value);
    }

    template<typename TFloat>
    TFloat Math::Exp(const TFloat &value) noexcept
    {
        return glm::exp(value);
    }

    template<typename TFloat>
    TFloat Math::Log(const TFloat &value) noexcept
    {
        return glm::log(value);
    }

    template<typename TFloat>
    TFloat Math::Exp2(const TFloat &value) noexcept
    {
        return glm::exp2(value);
    }

    template<typename TFloat>
    TFloat Math::Log2(const TFloat &value) noexcept
    {
        return glm::log2(value);
    }

    template<typename TFloat>
    TFloat Math::Sqrt(const TFloat &value) noexcept
    {
        return glm::sqrt(value);
    }

    template<typename TFloatOrInt>
    TFloatOrInt Math::Abs(const TFloatOrInt &value) noexcept
    {
        return glm::abs(value);
    }

    template<typename TFloatOrInt>
    TFloatOrInt Math::Sign(const TFloatOrInt &value) noexcept
    {
        return glm::sign(value);
    }

    template<typename TFloat>
    TFloat Math::Floor(const TFloat &value) noexcept
    {
        return glm::floor(value);
    }

    template<typename TFloat>
    TFloat Math::Trunc(const TFloat &value) noexcept
    {
        return glm::trunc(value);
    }

    template<typename TFloat>
    TFloat Math::Round(const TFloat &value) noexcept
    {
        return glm::round(value);
    }

    template<typename TFloat>
    TFloat Math::Ceil(const TFloat &value) noexcept
    {
        return glm::ceil(value);
    }

    template<typename TFloat>
    TFloat Math::Fract(const TFloat &value) noexcept
    {
        return glm::fract(value);
    }

    template<typename TFloatOrInt>
    TFloatOrInt Math::Mod(const TFloatOrInt &x, const TFloatOrInt &y) noexcept
    {
        return glm::mod(x, y);
    }

    // https://stackoverflow.com/a/63330289
    template <typename TFloatOrInt0, typename TFloatOrInt1, typename... Tail>
    auto Math::Min(TFloatOrInt0 &&head0, TFloatOrInt1 &&head1, Tail &&... tail) try
    {
        if constexpr (sizeof...(tail) == 0) {
            return (head0 < head1) ? head0 : head1;
        }
        else {
            return Min(Min(head0, head1), tail...);
        }
    }
    CATCH_RETHROW_EXCEPTIONS

    template <typename TFloatOrInt0, typename TFloatOrInt1, typename... Tail>
    auto Math::Max(TFloatOrInt0 &&head0, TFloatOrInt1 &&head1, Tail &&... tail) try
    {
        if constexpr (sizeof...(tail) == 0) {
            return (head0 > head1) ? head0 : head1;
        }
        else {
            return Max(Max(head0, head1), tail...);
        }
    }
    CATCH_RETHROW_EXCEPTIONS

    template<typename TFloatOrInt>
    TFloatOrInt Math::Clamp(const TFloatOrInt &value, const TFloatOrInt &min,
                            const TFloatOrInt &max) noexcept
    {
        return glm::clamp(value, min, max);
    }

    template<typename TFloatOrInt, typename TFloat>
    TFloatOrInt Math::Lerp(const TFloatOrInt &v1, const TFloatOrInt &v2, const TFloat& t) noexcept
    {
        return glm::mix(v1, v2, t);
    }

    template<typename TFloatOrInt>
    TFloatOrInt Math::Step(const TFloatOrInt &edge, const TFloatOrInt &value) noexcept
    {
        return glm::step(edge, value);
    }

    template<typename TFloatOrInt>
    TFloatOrInt Math::SmoothStep(const TFloatOrInt &edge1, const TFloatOrInt &edge2,
                                 const TFloatOrInt &value) noexcept
    {
        return glm::smoothstep(edge1, edge2, value);
    }
}

constexpr float operator"" _deg(long double value) noexcept
{
    return MG3TR::Math::RadiansToDegrees(static_cast<float>(value));
}

constexpr float operator"" _rad(long double value) noexcept
{
    return MG3TR::Math::DegreesToRadians(static_cast<float>(value));
}
