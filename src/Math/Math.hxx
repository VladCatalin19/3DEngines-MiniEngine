#ifndef M3GTR_SRC_MATH_MATH_HPP_INCLUDED
#define M3GTR_SRC_MATH_MATH_HPP_INCLUDED

namespace MG3TR
{
    class Math final
    {
    public:
        Math() = delete;
        ~Math() = delete;
        Math(const Math &) = delete;
        Math(Math &&) = delete;
        Math& operator=(const Math &) = delete;
        Math& operator=(Math &&) = delete;

        template<typename TFloat>
        static constexpr TFloat DegreesToRadians(const TFloat &value) noexcept;

        template<typename TFloat>
        static constexpr TFloat RadiansToDegrees(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Sin(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Cos(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Tan(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Asin(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Acon(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Atan(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Atan2(const TFloat &y, const TFloat &x) noexcept;

        template<typename TFloat>
        static TFloat Pow(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Exp(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Log(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Exp2(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Log2(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Sqrt(const TFloat &value) noexcept;

        template<typename TFloatOrInt>
        static TFloatOrInt Abs(const TFloatOrInt &value) noexcept;

        template<typename TFloatOrInt>
        static TFloatOrInt Sign(const TFloatOrInt &value) noexcept;

        template<typename TFloat>
        static TFloat Floor(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Trunc(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Round(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Ceil(const TFloat &value) noexcept;

        template<typename TFloat>
        static TFloat Fract(const TFloat &value) noexcept;

        template<typename TFloatOrInt>
        static TFloatOrInt Mod(const TFloatOrInt &x, const TFloatOrInt &y) noexcept;

        template <typename TFloatOrInt0, typename TFloatOrInt1, typename... Tail>
        static auto Min(TFloatOrInt0 &&head0, TFloatOrInt1 &&head1, Tail &&... tail);

        template <typename TFloatOrInt0, typename TFloatOrInt1, typename... Tail>
        static auto Max(TFloatOrInt0 &&head0, TFloatOrInt1 &&head1, Tail &&... tail);

        template<typename TFloatOrInt>
        static TFloatOrInt Clamp(const TFloatOrInt &value, const TFloatOrInt &min,
                                 const TFloatOrInt &max) noexcept;

        template<typename TFloatOrInt, typename TFloat>
        static TFloatOrInt Lerp(const TFloatOrInt &v1, const TFloatOrInt &v2, const TFloat& t) noexcept;

        template<typename TFloatOrInt>
        static TFloatOrInt Step(const TFloatOrInt &edge, const TFloatOrInt &value) noexcept;

        template<typename TFloatOrInt>
        static TFloatOrInt SmoothStep(const TFloatOrInt &edge1, const TFloatOrInt &edge2,
                                      const TFloatOrInt &value) noexcept;
    };
}

constexpr float operator"" _deg(long double value) noexcept;
constexpr float operator"" _rad(long double value) noexcept;

#include "Math.ixx"

#endif // M3GTR_SRC_MATH_MATH_HPP_INCLUDED
