#include "ExceptionWithStacktrace.hpp"

namespace MG3TR
{
    ExceptionWithStacktrace::ExceptionWithStacktrace(const std::string &message, const std::stacktrace &stacktrace)
        : m_message(message)
    {
        m_message += "\n" + std::to_string(stacktrace);
    }

    const char* ExceptionWithStacktrace::what() const noexcept
    {
        const char* const ptr = m_message.c_str();
        return ptr;
    }
}
