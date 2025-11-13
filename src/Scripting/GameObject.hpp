#ifndef MG3TR_SRC_SCRIPTING_GAMEOBJECT_HPP_INCLUDED
#define MG3TR_SRC_SCRIPTING_GAMEOBJECT_HPP_INCLUDED

#include <Components/Component.hpp>
#include <Scripting/Transform.hpp>
#include <Scene/IJsonSerializeable.hpp>
#include <Utils/UIDGenerator.hpp>

#include <cstddef>
#include <memory>
#include <vector>
#include <string>

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
        virtual ~GameObject() = default;

        GameObject(const GameObject &) = delete;
        GameObject(GameObject &&) = delete;
        
        GameObject& operator=(const GameObject &) = delete;
        GameObject& operator=(GameObject&&) = delete;

        bool operator==(const GameObject &other) const;
        bool operator!=(const GameObject &other) const;

        const std::string& GetName() const;
        void SetName(const std::string &name);

        std::weak_ptr<Transform> GetTransform() const;
        void SetTransform(const std::shared_ptr<Transform> &transform);

        std::vector<std::shared_ptr<Component>>& GetComponents();
        const std::vector<std::shared_ptr<Component>>& GetComponents() const;

        void AddComponent(const std::shared_ptr<Component> &component);
        void AddComponent(const std::shared_ptr<Component> &component, const std::size_t position);
        void RemoveComponent(const std::shared_ptr<Component> &component);
        void RemoveComponent(const std::size_t position);

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;
    };
}

#endif // MG3TR_SRC_SCRIPTING_GAMEOBJECT_HPP_INCLUDED
