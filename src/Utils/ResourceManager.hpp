#ifndef M3GTR_SRC_UTILS_RESOURCEMANAGER_HPP_INCLUDED
#define M3GTR_SRC_UTILS_RESOURCEMANAGER_HPP_INCLUDED

#include <string>

namespace MG3TR
{
    class ResourceManager
    {
    private:
        static ResourceManager m_instance;
        std::string m_resource_directory_path;

        ResourceManager() = default;
        ~ResourceManager() = default;

    public:
        ResourceManager(const ResourceManager &) = delete;
        ResourceManager(ResourceManager &&) = delete;

        ResourceManager& operator=(const ResourceManager &) = delete;
        ResourceManager& operator=(ResourceManager &&) = delete;

        static ResourceManager& GetInstance();

        void SetResourceDirectoryPath(const std::string &path);
        std::string AddResourceDirectoryToPath(const std::string &path);
        std::string RemoveResourceDirectoryFromPath(const std::string &path);
    };
}

#endif // M3GTR_SRC_UTILS_RESOURCEMANAGER_HPP_INCLUDED
