#ifndef MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED

#include <Utils/UIDGenerator.hpp>
#include <Scene/IJsonSerializeable.hpp>
#include <Window/Input.hpp>

#include <memory>               // std::weak_ptr

namespace MG3TR
{
    class GameObject;
    class Transform;

    class Component : public IJsonSerializeable
    {
    private:
        std::weak_ptr<GameObject> m_game_object;
        std::weak_ptr<Transform> m_transform;

        static inline UIDGenerator s_uid_generator;
        TUID m_uid;
    
    public:
        Component() noexcept;
        Component(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept;
        virtual ~Component() noexcept = default;

        Component(const Component &) = delete;
        Component& operator=(const Component &) = delete;

        Component(Component &&) noexcept = default;
        Component& operator=(Component &&) noexcept = default;

        std::weak_ptr<GameObject> GetGameObject() const noexcept { return m_game_object; }
        void SetGameObject(const std::weak_ptr<GameObject> &game_object) noexcept { m_game_object = game_object; }

        std::weak_ptr<Transform> GetTransform() const noexcept { return m_transform; }
        void SetTransform(const std::weak_ptr<Transform> &transform) noexcept { m_transform = transform; }

        TUID GetUID() const noexcept { return m_uid; }

    protected:
        void SetUID(TUID uid) noexcept { m_uid = uid; }

    public:
        virtual void Initialize() {}

        virtual void ParseInput([[maybe_unused]] const Input &input) {}

        virtual void FrameStart([[maybe_unused]] float delta_time) {}
        virtual void FrameUpdate([[maybe_unused]] float delta_time) {}
        virtual void FrameEnd([[maybe_unused]] float delta_time) {}

        virtual nlohmann::json Serialize() const = 0;
        virtual void Deserialize(const nlohmann::json &json) = 0;
        virtual void LateBindAfterDeserialization(Scene &scene) = 0;
    };
}

#endif // MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED
