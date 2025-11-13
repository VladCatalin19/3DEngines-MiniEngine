#ifndef M3GTR_SRC_UTILS_EXCEPTIONWITHSTACKTRACE_HPP_INCLUDED
#define M3GTR_SRC_UTILS_EXCEPTIONWITHSTACKTRACE_HPP_INCLUDED

#include <stacktrace>

namespace MG3TR
{
    class ExceptionWithStacktrace : public std::exception
    {
    private:
        std::string m_message;

    public:
        ExceptionWithStacktrace(const std::string &message, const std::stacktrace &stacktrace = std::stacktrace::current());
        virtual ~ExceptionWithStacktrace() = default;

        ExceptionWithStacktrace(const ExceptionWithStacktrace &) = default;
        ExceptionWithStacktrace(ExceptionWithStacktrace &&) = default;

        ExceptionWithStacktrace& operator=(const ExceptionWithStacktrace &) = default;
        ExceptionWithStacktrace& operator=(ExceptionWithStacktrace &&) = default;

        virtual const char* what() const noexcept override;
    };
}

#endif // M3GTR_SRC_UTILS_EXCEPTIONWITHSTACKTRACE_HPP_INCLUDED
