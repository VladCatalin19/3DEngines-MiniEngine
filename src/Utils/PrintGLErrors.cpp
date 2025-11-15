#include "PrintGLErrors.hpp"

#include <iostream>

#include <glad/glad.h>
#include <Constants/UtilsConstants.hpp>

// https://codeyarns.com/tech/2015-09-14-how-to-check-error-in-opengl.html
static const char* GetGLErrorString(const GLenum err)
{
    switch (err)
    {
        case GL_NO_ERROR:          return "No error";
        case GL_INVALID_ENUM:      return "Invalid enum";
        case GL_INVALID_VALUE:     return "Invalid value";
        case GL_INVALID_OPERATION: return "Invalid operation";
        case GL_STACK_OVERFLOW:    return "Stack overflow";
        case GL_STACK_UNDERFLOW:   return "Stack underflow";
        case GL_OUT_OF_MEMORY:     return "Out of memory";
    }
    return "Unknown error";
}

namespace MG3TR
{
    void PrintGLErrors(const char* const file, const int line)
    {
        GLenum current_error = glGetError();
        unsigned current_depth = 1U;

        const bool is_initial_error_present = (current_error != GL_NO_ERROR);
        if (is_initial_error_present)
        {
            std::cerr << "OpenGL error: ";
        }

        while ((current_error != GL_NO_ERROR) && (current_depth <= UtilsConstants::k_max_GL_errors_depth_to_print))
        {
            std::cerr << GetGLErrorString(current_error) << " ";

            current_error = glGetError();

            ++current_depth;
            if (current_depth >= UtilsConstants::k_max_GL_errors_depth_to_print)
            {
                std::cerr << std::endl << "OpenGL max error depth reached. Not printing any errors.";
            }
        }

        if (is_initial_error_present)
        {
            std::cerr << "\tin " << file << ":" << line << std::endl;
        }
    }
}
