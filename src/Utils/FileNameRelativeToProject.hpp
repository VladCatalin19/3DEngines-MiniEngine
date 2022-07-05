#ifndef MG3TR_SRC_UTILS_FILENAMERELATIVETOPROJECT_HPP_INCLUDED
#define MG3TR_SRC_UTILS_FILENAMERELATIVETOPROJECT_HPP_INCLUDED

#include <Constants/UtilsConstants.hpp>     // MG3TR::UtilsConstants

namespace MG3TR
{
    constexpr unsigned StringLength(const char *string) noexcept
    {
        unsigned length = 0U;

        for (const char *string_pointer = string; *string_pointer != '\0'; ++string_pointer)
        {
            ++length;
        }

        return length;
    }

    constexpr inline bool IsTheSameString(const char *string1, const char *string2, unsigned length) noexcept
    {
        for (unsigned index = 0U; (index < length) && (string1[index] != '\0') && (string2[index] != '\0'); ++index)
        {
            if (string1[index] != string2[index])
            {
                return false;
            }
        }
        return true;
    }

    constexpr const char* GetFileNameAndExtensionRelativeToProjectDirectory(const char *path) noexcept
    {
        constexpr unsigned project_name_length = StringLength(MG3TR::UtilsConstants::k_project_directory_name);
        const char *project_name = nullptr;

        for (const char *path_pointer = path; *path_pointer != '\0'; ++path_pointer)
        {
            if (IsTheSameString(path_pointer, MG3TR::UtilsConstants::k_project_directory_name, project_name_length))
            {
                project_name = path_pointer;
            }
        }

        bool project_name_not_found = (project_name == nullptr);
        if (project_name_not_found)
        {
            return path;
        }

        return project_name;
    }
}

#define FILENAME_RELATIVE_TO_PROJECT MG3TR::GetFileNameAndExtensionRelativeToProjectDirectory(__FILE__)

#endif // MG3TR_SRC_UTILS_FILENAMERELATIVETOPROJECT_HPP_INCLUDED
