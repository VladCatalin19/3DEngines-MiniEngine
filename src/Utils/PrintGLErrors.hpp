#ifndef M3GTR_SRC_UTILS_PRINTGLERRORS_HPP_INCLUDED
#define M3GTR_SRC_UTILS_PRINTGLERRORS_HPP_INCLUDED

#include "FileNameRelativeToProject.hpp"    // FILENAME_RELATIVE_TO_PROJECT

namespace MG3TR
{
    void PrintGLErrors(const char *filename_relative_to_project, const char *function, unsigned line) noexcept;
}

#define PRINT_GL_ERRORS_IF_ANY() MG3TR::PrintGLErrors(FILENAME_RELATIVE_TO_PROJECT, __func__, __LINE__)

#endif // M3GTR_SRC_UTILS_PRINTGLERRORS_HPP_INCLUDED
