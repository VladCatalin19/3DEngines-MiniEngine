#ifndef M3GTR_SRC_UTILS_NULLPOINTEREXCEPTION_HPP_INCLUDED
#define M3GTR_SRC_UTILS_NULLPOINTEREXCEPTION_HPP_INCLUDED

#include <exception>            // std::exception
#include <string>               // std::string

namespace MG3TR
{
    class NullPointerException : public std::exception
    {
    private:
        std::string m_what;

    public:
        NullPointerException(const std::string &variable_name)
            : m_what(variable_name + " is null")
        {}
        virtual ~NullPointerException() noexcept = default;

        virtual const char* what() const noexcept override { return m_what.c_str(); }
    };
}

#endif // M3GTR_SRC_UTILS_NULLPOINTEREXCEPTION_HPP_INCLUDED