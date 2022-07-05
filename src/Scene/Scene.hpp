#ifndef MG3TR_SRC_SCENE_SCENE_HPP_INCLUDED
#define MG3TR_SRC_SCENE_SCENE_HPP_INCLUDED

#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

#include <Window/Input.hpp>

#include <cstddef>              // std::size_t
#include <memory>               // std::shared_ptr
#include <ostream>              // std::ostream
#include <string>               // std::string
#include <vector>               // std::vector

namespace MG3TR
{
    class Camera;

    class Scene
    {
    private:
        std::shared_ptr<Transform> m_root_transform;

    public:
        Scene();
        Scene(const std::string &file_name);
        virtual ~Scene() noexcept = default;

        Scene(const Scene &) = delete;
        Scene& operator=(const Scene &) = delete;

        Scene(Scene &&) = default;
        Scene& operator=(Scene &&) = default;

        std::shared_ptr<Transform>& GetRootTransform() noexcept { return m_root_transform; }
        const std::shared_ptr<Transform>& GetRootTransform() const noexcept { return m_root_transform; }

        void Initialize();

        void Update(const Input &input, float delta_time);

        std::string ToString() const;
        friend std::ostream& operator<<(std::ostream &os, const Scene &scene);

        void LoadFromFile(const std::string &file_name);
        void SaveToFile(const std::string &file_name) const;

        std::shared_ptr<Camera> FindCameraWithUID(TUID uid);
        std::shared_ptr<Transform> FindTransformWithUID(TUID uid);
    };
}

#endif // MG3TR_SRC_SCENE_SCENE_HPP_INCLUDED
