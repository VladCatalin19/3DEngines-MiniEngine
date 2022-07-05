#ifndef MG3TR_SRC_SCRIPTING_GAMEOBJECT_HPP_INCLUDED
#define MG3TR_SRC_SCRIPTING_GAMEOBJECT_HPP_INCLUDED

#include <Components/Component.hpp>
#include <Scripting/Transform.hpp>
#include <Scene/IJsonSerializeable.hpp>
#include <Utils/UIDGenerator.hpp>

#include <cstddef>              // std::size_t
#include <memory>               // std::enable_shared_from_this, std::shared_ptr, std::weak_ptr
#include <vector>               // std::vector
#include <string>               // std::string

namespace MG3TR
{
    class GameObject : public IJsonSerializeable, public std::enable_shared_from_this<GameObject>
    {
    private:
        std::string m_name;
        std::weak_ptr<Transform> m_transform;
        std::vector<std::shared_ptr<Component>> m_components;

        static inline UIDGenerator s_uid_generator;
        TUID m_uid;

        GameObject(const std::string &name);

    public:
        [[nodiscard]] static std::shared_ptr<GameObject> Create(const std::string &name = "");
        virtual ~GameObject() noexcept = default;

        GameObject(const GameObject &) = delete;
        GameObject& operator=(const GameObject &) = delete;

        GameObject(GameObject &&) noexcept = delete;
        GameObject& operator=(GameObject&&) noexcept = delete;

        bool operator==(const GameObject &other) const noexcept { return m_uid == other.m_uid; }
        bool operator!=(const GameObject &other) const noexcept { return m_uid != other.m_uid; }

        const std::string& GetName() const noexcept { return m_name; }
        void SetName(const std::string &name) { m_name = name; }

        std::weak_ptr<Transform> GetTransform() const noexcept { return m_transform; }
        void SetTransform(const std::shared_ptr<Transform> &transform) { m_transform = transform; }

        std::vector<std::shared_ptr<Component>>& GetComponents() noexcept { return m_components; }
        const std::vector<std::shared_ptr<Component>>& GetComponents() const noexcept { return m_components; }

        void AddComponent(const std::shared_ptr<Component> &component);
        void AddComponent(const std::shared_ptr<Component> &component, std::size_t position);
        void RemoveComponent(const std::shared_ptr<Component> &component);
        void RemoveComponent(std::size_t position);

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_SCRIPTING_GAMEOBJECT_HPP_INCLUDED
