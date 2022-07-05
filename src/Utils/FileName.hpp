#ifndef MG3TR_SRC_UTILS_FILENAME_HPP_INCLUDED
#define MG3TR_SRC_UTILS_FILENAME_HPP_INCLUDED

namespace MG3TR
{
    constexpr inline bool IsPathSeparator(char c) noexcept
    {
        return (c == '/') || (c == '\\');
    }

    constexpr const char* GetFileNameAndExtension(const char *path) noexcept
    {
        const char *last_path_separator = nullptr;

        for (const char *path_pointer = path; *path_pointer != '\0'; ++path_pointer)
        {
            if (IsPathSeparator(*path_pointer) && (*(path_pointer + 1) != '\0'))
            {
                last_path_separator = path_pointer;
            }
        }

        bool no_separator_found = (last_path_separator == nullptr);
        if (no_separator_found)
        {
            return path;
        }

        return last_path_separator + 1;
    }
}

#define FILENAME MG3TR::GetFileNameAndExtension(__FILE__)

#endif // MG3TR_SRC_UTILS_FILENAME_HPP_INCLUDED
