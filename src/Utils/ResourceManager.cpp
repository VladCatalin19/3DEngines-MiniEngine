#include "ResourceManager.hpp"

#include "ExceptionWithStacktrace.hpp"

#include <filesystem>

namespace MG3TR
{
    ResourceManager ResourceManager::m_instance;

    ResourceManager& ResourceManager::GetInstance()
    {
        return m_instance;
    }

    void ResourceManager::SetResourceDirectoryPath(const std::string &path)
    {
        m_resource_directory_path = path;
    }

    std::string ResourceManager::AddResourceDirectoryToPath(const std::string &path)
    {
        const auto root_dir_position = path.find(m_resource_directory_path);

        if (root_dir_position != std::string::npos)
        {
            throw ExceptionWithStacktrace("String \"" + path + "\" already contains \"" + m_resource_directory_path + "\"!");
        }

        const std::filesystem::path resource_directory_path = m_resource_directory_path;
        const std::filesystem::path current_path = path;
        const std::filesystem::path new_path = resource_directory_path / current_path;

        const std::string new_path_string = new_path.string();
        
        return new_path;
    }

    std::string ResourceManager::RemoveResourceDirectoryFromPath(const std::string &path)
    {
        const auto root_dir_position = path.find(m_resource_directory_path);

        if (root_dir_position == std::string::npos)
        {
            throw ExceptionWithStacktrace("String \"" + path + "\" does not contain \"" + m_resource_directory_path + "\"!");
        }

        const std::filesystem::path resource_directory_path = m_resource_directory_path;
        const std::filesystem::path current_path = path;
        const std::filesystem::path relative_path = current_path.lexically_relative(resource_directory_path);

        const std::string new_path_string = relative_path.string();
        
        return relative_path;
    }
}
