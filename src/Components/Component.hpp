#ifndef MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED

#include <Utils/UIDGenerator.hpp>
#include <Scene/IJsonSerializeable.hpp>

#include <memory>

namespace MG3TR
{
    class GameObject;
    class Transform;
    class Input;

    class Component : public IJsonSerializeable
    {
    private:
        std::weak_ptr<GameObject> m_game_object;
        std::weak_ptr<Transform> m_transform;

        static inline UIDGenerator s_uid_generator;
        TUID m_uid;

    public:
        Component();
        Component(const std::weak_ptr<GameObject>& game_object, const std::weak_ptr<Transform>& transform);
        virtual ~Component() = default;

        Component(const Component &) = delete;
        Component(Component &&) = default;
        
        Component& operator=(const Component &) = delete;
        Component& operator=(Component &&) = default;

        std::weak_ptr<GameObject> GetGameObject() const;
        void SetGameObject(const std::weak_ptr<GameObject> &game_object);

        std::weak_ptr<Transform> GetTransform() const;
        void SetTransform(const std::weak_ptr<Transform> &transform);

        TUID GetUID() const;

    protected:
        void SetUID(TUID uid);

    public:
        virtual void Initialize();

        virtual void ParseInput([[maybe_unused]] const Input &input);

        virtual void FrameStart([[maybe_unused]] const float delta_time);
        virtual void FrameUpdate([[maybe_unused]] const float delta_time);
        virtual void FrameEnd([[maybe_unused]] const float delta_time);

        virtual nlohmann::json Serialize() const = 0;
        virtual void Deserialize(const nlohmann::json& json) = 0;
        virtual void LateBindAfterDeserialization(Scene& scene) = 0;
    };
}

#endif // MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED
