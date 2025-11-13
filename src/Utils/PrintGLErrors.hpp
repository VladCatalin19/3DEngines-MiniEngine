#ifndef M3GTR_SRC_UTILS_PRINTGLERRORS_HPP_INCLUDED
#define M3GTR_SRC_UTILS_PRINTGLERRORS_HPP_INCLUDED

namespace MG3TR
{
    void PrintGLErrors(const char* const file, const int line);
}

#define PRINT_GL_ERRORS_IF_ANY() MG3TR::PrintGLErrors(__FILE__, __LINE__)

#endif // M3GTR_SRC_UTILS_PRINTGLERRORS_HPP_INCLUDED
