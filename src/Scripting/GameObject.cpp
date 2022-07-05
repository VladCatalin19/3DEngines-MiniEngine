#include "GameObject.hpp"

#include <Components/Camera.hpp>
#include <Components/CameraController.hpp>
#include <Components/MeshRenderer.hpp>
#include <Components/SkyboxFollowCamera.hpp>
#include <Components/TestMovement.hpp>
#include <Components/TestRotation.hpp>
#include <Constants/JSONConstants.hpp>

#include <Components/Component.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <algorithm>            // std::find
#include <cstddef>              // std::size_t
#include <memory>               // std::move, std::make_shared
#include <stdexcept>            // std::out_of_range, std::range_error
#include <string>               // std::string, std::to_string

namespace MG3TR
{
    GameObject::GameObject(const std::string &name)
        : m_name(name),
          m_uid(s_uid_generator.GetNextUID())
    {}

    [[nodiscard]] std::shared_ptr<GameObject> GameObject::Create(const std::string &name) try
    {
        return std::shared_ptr<GameObject>(new GameObject(name));
    }
    CATCH_RETHROW_EXCEPTIONS

    void GameObject::AddComponent(const std::shared_ptr<Component> &component) try
    {
        auto component_in_vector_iterator = std::find(m_components.cbegin(), m_components.cend(), component);
        bool is_component_added = (component_in_vector_iterator != m_components.cend());
        if (is_component_added)
        {
            throw std::range_error("Could not add component to current object because component"
                                   " has already been added previously.");
        }
        m_components.push_back(component);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void GameObject::AddComponent(const std::shared_ptr<Component> &component, std::size_t position) try
    {
        auto component_in_vector_iterator = std::find(m_components.cbegin(), m_components.cend(), component);
        bool is_component_added = (component_in_vector_iterator != m_components.cend());
        if (is_component_added)
        {
            throw std::range_error("Could not add component to current object because component"
                                   " has already been added previously.");
        }

        if (position >= m_components.size())
        {
            throw std::out_of_range("Cannot add component at " + std::to_string(position)
                                    + " bause current object has " + std::to_string(m_components.size())
                                    + " elements.");
        }

        (void)m_components.insert(m_components.begin() + position, std::move(component));
    }
    CATCH_RETHROW_EXCEPTIONS

    void GameObject::RemoveComponent(const std::shared_ptr<Component> &component) try
    {
        auto component_in_vector_iterator = std::find(m_components.cbegin(), m_components.cend(), component);
        bool is_component_added = (component_in_vector_iterator != m_components.cend());
        if (!is_component_added)
        {
            throw std::range_error("Could not find component to remove.");
        }
        (void)m_components.erase(component_in_vector_iterator);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void GameObject::RemoveComponent(std::size_t position) try
    {
        if (position >= m_components.size())
        {
            throw std::out_of_range("Cannot remove component at " + std::to_string(position)
                                    + " bause current object has " + std::to_string(m_components.size())
                                    + " elements.");
        }
        (void)m_components.erase(m_components.begin() + position);
    }
    CATCH_RETHROW_EXCEPTIONS

    nlohmann::json GameObject::Serialize() const try
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
    CATCH_RETHROW_EXCEPTIONS

    void GameObject::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = GameObjectJSONConstants;

        const nlohmann::json game_object_json = json.at(Constants::k_parent_node);
        m_uid = game_object_json.at(Constants::k_uid_attribute);
        m_name = game_object_json.at(Constants::k_name_attribute);

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
                    throw std::logic_error("Invalid component to deserialize.");
                }
                
                component->Deserialize(component_json);
                m_components.push_back(component);
            }
        }
    }
    CATCH_RETHROW_EXCEPTIONS

    void GameObject::LateBindAfterDeserialization(Scene &scene) try
    {
        for (auto &component : m_components)
        {
            component->LateBindAfterDeserialization(scene);
        }
    }
    CATCH_RETHROW_EXCEPTIONS
}
