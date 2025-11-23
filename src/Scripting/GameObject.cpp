#include "GameObject.hpp"

#include <Constants/ComponentConstants.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Serialisation/IDeserialiser.hpp>
#include <Serialisation/ISerialiser.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>
#include <Utils/TryCathRethrowStacktrace.hpp>

#include <format>

namespace MG3TR
{
    GameObject::GameObject(const std::string &name)
        : m_name(name),
          m_uid(s_uid_generator.GetNextUID())
    {

    }

    [[nodiscard]] std::shared_ptr<GameObject> GameObject::Create(const std::string &name)
    {
        auto ptr = std::shared_ptr<GameObject>(new GameObject(name));
        return ptr;
    }

    bool GameObject::operator==(const GameObject &other) const
    {
        const bool are_equal = (m_uid == other.m_uid);
        return are_equal;
    }

    bool GameObject::operator!=(const GameObject &other) const
    {
        const bool are_not_equal = (m_uid != other.m_uid);
        return are_not_equal;
    }

    const std::string& GameObject::GetName() const
    {
        return m_name;
    }

    void GameObject::SetName(const std::string &name)
    {
        m_name = name;
    }

    std::weak_ptr<Transform> GameObject::GetTransform() const
    {
        return m_transform;
    }

    void GameObject::SetTransform(const std::shared_ptr<Transform> &transform)
    {
        m_transform = transform;
    }

    std::vector<std::shared_ptr<Component>>& GameObject::GetComponents()
    {
        return m_components;
    }

    const std::vector<std::shared_ptr<Component>>& GameObject::GetComponents() const
    {
        return m_components;
    }

    void GameObject::AddComponent(const std::shared_ptr<Component> &component)
    {
        const auto component_in_vector_iterator = std::find(m_components.cbegin(), m_components.cend(), component);
        const bool is_component_added = (component_in_vector_iterator != m_components.cend());
        if (is_component_added)
        {
            throw ExceptionWithStacktrace("Could not add component to current object because component"
                                          " has already been added previously.");
        }
        m_components.push_back(component);
    }
    
    void GameObject::AddComponent(const std::shared_ptr<Component> &component, const std::size_t position)
    {
        const auto component_in_vector_iterator = std::find(m_components.cbegin(), m_components.cend(), component);
        const bool is_component_added = (component_in_vector_iterator != m_components.cend());
        if (is_component_added)
        {
            throw ExceptionWithStacktrace("Could not add component to current object because component"
                                          " has already been added previously.");
        }

        const std::size_t components_size = m_components.size();
        if (position >= components_size)
        {
            const std::string error = std::format("Cannot add component at position {} because current object has {} elements.",
                                                  position, components_size);
            throw ExceptionWithStacktrace(error);
        }

        (void)m_components.insert(m_components.begin() + position, std::move(component));
    }

    void GameObject::RemoveComponent(const std::shared_ptr<Component> &component)
    {
        const auto component_in_vector_iterator = std::find(m_components.cbegin(), m_components.cend(), component);
        const bool is_component_added = (component_in_vector_iterator != m_components.cend());
        if (!is_component_added)
        {
            throw ExceptionWithStacktrace("Could not find component to remove.");
        }
        (void)m_components.erase(component_in_vector_iterator);
    }
    
    void GameObject::RemoveComponent(std::size_t position)
    {
        const std::size_t components_size = m_components.size();
        if (position >= components_size)
        {
            const std::string error = std::format("Cannot remove component at position {} because current object has {} elements.",
                                                  position, components_size);
            throw ExceptionWithStacktrace(error);
        }
        (void)m_components.erase(m_components.begin() + position);
    }

    void GameObject::Serialise(ISerialiser &serialiser)
    {
        namespace Constants = GameObjectSerialisationConstants;

        serialiser.SerialiseUnsigned(Constants::k_uid_attribute, m_uid);
        serialiser.SerialiseString(Constants::k_name_attribute, m_name);

        const std::size_t component_count = m_components.size();

        if (component_count > 0U)
        {
            serialiser.BeginSerialisingArray(Constants::k_components_attribute, component_count);

            for (const auto &component : m_components)
            {
                serialiser.BeginSerialisingChild(ComponentSerialisationConstants::k_parent_node);

                component->Serialise(serialiser);

                serialiser.EndSerialisingLastChild();
                serialiser.EndSerialisingCurrentArrayElement();
            }

            serialiser.EndSerialisingLastArray();
        }
    }

    void GameObject::Deserialise(IDeserialiser &deserialiser)
    {
        namespace Constants = GameObjectSerialisationConstants;

        m_uid = deserialiser.DeserialiseUnsigned(Constants::k_uid_attribute);
        m_name = deserialiser.DeserialiseString(Constants::k_name_attribute);

        const bool has_components = deserialiser.ContainsField(Constants::k_components_attribute);
        if (has_components)
        {
            const std::size_t component_count = deserialiser.BeginDeserialisingArray(Constants::k_components_attribute);
            m_components.reserve(component_count);

            for (std::size_t i = 0; i < component_count; ++i)
            {
                deserialiser.BeginDeserialisingChild(ComponentSerialisationConstants::k_parent_node);

                const auto component_type = static_cast<ComponentType>(deserialiser.DeserialiseUnsigned(ComponentSerialisationConstants::k_type_attribute));
                ComponentConstants::TComponentConstructor component_constructor;
                TRY_CATCH_RETHROW_STACKTRACE(component_constructor = ComponentConstants::k_component_to_constructor.at(component_type));

                auto component = component_constructor(shared_from_this(), m_transform.lock());

                component->Deserialise(deserialiser);
                m_components.push_back(component);

                deserialiser.EndDeserialisingLastChild();
                deserialiser.EndDeserialisingCurrentArrayElement();
            }

            deserialiser.EndDeserialisingLastArray();
        }
    }

    void GameObject::LateBind(Scene &scene)
    {
        for (auto &component : m_components)
        {
            component->LateBind(scene);
        }
    }
}
