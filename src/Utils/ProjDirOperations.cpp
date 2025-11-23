#include "ProjDirOperations.hpp"

#include "ExceptionWithStacktrace.hpp"

#include <cstring>

namespace MG3TR
{
    std::string AddProjDirToPath(const std::string &path)
    {
        const auto root_dir_position = path.find(MG3TR_ROOT_DIR);

        if (root_dir_position != std::string::npos)
        {
            throw ExceptionWithStacktrace("String \"" + path + "\" already contains \"" + MG3TR_ROOT_DIR + "\"!");
        }

        const std::string new_path = MG3TR_ROOT_DIR + path;
        
        return new_path;
    }

    std::string RemoveProjDirFromPath(const std::string &path)
    {
        const auto root_dir_position = path.find(MG3TR_ROOT_DIR);

        if (root_dir_position == std::string::npos)
        {
            throw ExceptionWithStacktrace("String \"" + path + "\" does not contain \"" + MG3TR_ROOT_DIR + "\"!");
        }

        const std::size_t root_dir_length = strlen(MG3TR_ROOT_DIR);
        std::string new_path = path;

        new_path.erase(root_dir_position, root_dir_length);

        return new_path;
    }
}
