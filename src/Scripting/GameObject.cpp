#include "GameObject.hpp"
#include "Utils/ExceptionWithStacktrace.hpp"

#include <Components/Camera.hpp>
#include <Components/CameraController.hpp>
#include <Components/MeshRenderer.hpp>
#include <Components/SkyboxFollowCamera.hpp>
#include <Components/TestMovement.hpp>
#include <Components/TestRotation.hpp>
#include <Constants/JSONConstants.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

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

    nlohmann::json GameObject::Serialize() const
    {
        namespace Constants = GameObjectJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = m_uid;
        json[Constants::k_parent_node][Constants::k_name_attribute] = m_name;

        if (m_components.size() > 0U)
        {
            std::vector<nlohmann::json> components_json;
            components_json.reserve(m_components.size());

            for (const auto &component : m_components)
            {
                components_json.push_back(component->Serialize());
            }

            json[Constants::k_parent_node][Constants::k_components_attribute] = components_json;
        }

        return json;
    }

    void GameObject::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = GameObjectJSONConstants;

        const nlohmann::json game_object_json = json.at(Constants::k_parent_node);
        m_uid = game_object_json.at(Constants::k_uid_attribute);
        m_name = static_cast<std::string>(game_object_json.at(Constants::k_name_attribute));

        if (game_object_json.contains(Constants::k_components_attribute))
        {
            m_components.reserve(game_object_json.size());

            for (const auto &component_json : game_object_json[Constants::k_components_attribute])
            {
                std::shared_ptr<Component> component = nullptr;

                if (component_json.contains(CameraJSONConstants::k_parent_node))
                {
                    component = std::make_shared<Camera>(shared_from_this(), m_transform.lock());
                }
                else if (component_json.contains(CameraControllerJSONConstants::k_parent_node))
                {
                    component = std::make_shared<CameraController>(shared_from_this(), m_transform.lock());
                }
                else if (component_json.contains(MeshRendererJSONConstants::k_parent_node))
                {
                    component = std::make_shared<MeshRenderer>(shared_from_this(), m_transform.lock());
                }
                else if (component_json.contains(SkyboxFollowCameraJSONConstants::k_parent_node))
                {
                    component = std::make_shared<SkyboxFollowCamera>(shared_from_this(), m_transform.lock());
                }
                else if (component_json.contains(TestMovementJSONConstants::k_parent_node))
                {
                    component = std::make_shared<TestMovement>(shared_from_this(), m_transform.lock());
                }
                else if (component_json.contains(TestMRotationJSONConstants::k_parent_node))
                {
                    component = std::make_shared<TestRotation>(shared_from_this(), m_transform.lock());
                }
                else
                {
                    throw ExceptionWithStacktrace("Invalid component to deserialize.");
                }
                
                component->Deserialize(component_json);
                m_components.push_back(component);
            }
        }
    }

    void GameObject::LateBindAfterDeserialization(Scene &scene)
    {
        for (auto &component : m_components)
        {
            component->LateBindAfterDeserialization(scene);
        }
    }
}
