#ifndef M3GTR_SRC_UTILS_TRACES_HPP_INCLUDED
#define M3GTR_SRC_UTILS_TRACES_HPP_INCLUDED

#include <string>                           // std::string std::to_string

#include "FileNameRelativeToProject.hpp"    // FILENAME_RELATIVE_TO_PROJECT

#define FILE_TRACE (std::string(FILENAME_RELATIVE_TO_PROJECT) + ":" + std::to_string(__LINE__))
#define IN_FUNC_FILE_TRACE ("in " + std::string(__func__) + " " + FILE_TRACE)

#endif // M3GTR_SRC_UTILS_TRACES_HPP_INCLUDED
