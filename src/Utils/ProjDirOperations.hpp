#ifndef M3GTR_SRC_UTILS_PROJDIROPERATIONS_HPP_INCLUDED
#define M3GTR_SRC_UTILS_PROJDIROPERATIONS_HPP_INCLUDED

#include <string>

namespace MG3TR
{
    std::string AddProjDirToPath(const std::string &path);
    std::string RemoveProjDirFromPath(const std::string &path);
}

#endif // M3GTR_SRC_UTILS_PROJDIROPERATIONS_HPP_INCLUDED
