#ifndef M3GTR_SRC_UTILS_TRYCATCHRETHROWSTACKTRACE_HPP_INCLUDED
#define M3GTR_SRC_UTILS_TRYCATCHRETHROWSTACKTRACE_HPP_INCLUDED

#include "ExceptionWithStacktrace.hpp"

#define TRY_CATCH_RETHROW_STACKTRACE(expression)                    \
    do                                                              \
    {                                                               \
        try                                                         \
        {                                                           \
            expression;                                             \
        }                                                           \
        catch (const std::exception &exception)                     \
        {                                                           \
            throw MG3TR::ExceptionWithStacktrace(exception.what()); \
        }                                                           \
        catch (...)                                                 \
        {                                                           \
            throw MG3TR::ExceptionWithStacktrace("Unknown error!"); \
        }                                                           \
    }                                                               \
    while (false)

#endif // M3GTR_SRC_UTILS_TRYCATCHRETHROWSTACKTRACE_HPP_INCLUDED
