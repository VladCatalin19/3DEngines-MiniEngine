#ifndef MG3TR_SRC_SCENE_SCENE_HPP_INCLUDED
#define MG3TR_SRC_SCENE_SCENE_HPP_INCLUDED

#include <Utils/TUID.hpp>

#include <memory>
#include <ostream>
#include <string>

namespace MG3TR
{
    class Camera;
    class Input;
    class Transform;

    class Scene
    {
    private:
        std::shared_ptr<Transform> m_root_transform;

    public:
        Scene();
        Scene(const std::string &file_name);
        virtual ~Scene() = default;

        Scene(const Scene &) = delete;
        Scene(Scene &&) = default;
        
        Scene& operator=(const Scene &) = delete;
        Scene& operator=(Scene &&) = default;

        std::shared_ptr<Transform>& GetRootTransform();
        const std::shared_ptr<Transform>& GetRootTransform() const;

        void Initialize();
        void Update(const Input &input, const float delta_time);
        void LoadFromFile(const std::string &file_name);
        void SaveToFile(const std::string &file_name) const;

        std::shared_ptr<Camera> FindCameraWithUID(const TUID uid);
        std::shared_ptr<Transform> FindTransformWithUID(const TUID uid);
    };
}

#endif // MG3TR_SRC_SCENE_SCENE_HPP_INCLUDED
