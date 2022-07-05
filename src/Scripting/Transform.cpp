#include "Transform.hpp"

#include <Components/Component.hpp>
#include <Constants/JSONConstants.hpp>
#include <Constants/MathConstants.hpp>
#include <Math/Matrix4x4.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector4.hpp>
#include <Scripting/GameObject.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS

#include <algorithm>            // std::find
#include <cstddef>              // std::size_t
#include <memory>               // std::move, std::make_shared
#include <stdexcept>            // std::out_of_range
#include <string>               // std::to_string

namespace MG3TR
{
    Transform::Transform() noexcept
        : m_local_position(Vector3Constants::k_zero),
          m_local_rotation(QuaternionConstants::k_identity),
          m_local_scale(Vector3Constants::k_one),
          m_parent(),
          m_game_object(nullptr)
    {
        m_uid = s_number_of_instances;
        ++s_number_of_instances;

        UpdateLocalToWorldAndWorldToLocalVariables();
    }

    [[nodiscard]] std::shared_ptr<Transform> Transform::Create() try
    {
        return std::shared_ptr<Transform>(new Transform());
    }
    CATCH_RETHROW_EXCEPTIONS

    void Transform::SetLocalPosition(const Vector3 &local_position) noexcept
    {
        m_local_position = local_position;
        UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    }
    
    void Transform::SetLocalRotation(const Quaternion &local_rotation) noexcept
    {
        m_local_rotation = local_rotation;
        UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    }
    
    void Transform::SetLocalScale(const Vector3 &local_scale) noexcept
    {
        m_local_scale = local_scale;
        UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    }

    Vector3 Transform::GetWorldPosition() const noexcept
    {
        Vector4 position(m_local_position, 1.0F);
        position = m_local_to_world_model_matrix * position;
        return Vector3(position.x(), position.y(), position.z());
    }

    void Transform::SetWorldPosition(const Vector3 &world_position) noexcept
    {
        Vector4 position(world_position, 1.0F);
        position = m_world_to_local_model_matrix * position;
        SetLocalPosition(Vector3(position.x(), position.y(), position.z()));
    }
    
    Quaternion Transform::GetWorldRotation() const noexcept
    {
        return m_local_to_world_rotation * m_local_rotation;
    }

    void Transform::SetWorldRotation(const Quaternion &world_rotation) noexcept
    {
        SetLocalRotation(world_rotation * m_world_to_local_rotation);
    }
    
    Vector3 Transform::GetWorldScale() const noexcept
    {
        return Vector3::Scale(m_local_to_world_scale, m_local_scale);
    }

    void Transform::SetWorldScale(const Vector3 &world_scale) noexcept
    {
        SetLocalScale(Vector3::Scale(m_world_to_local_scale, world_scale));
    }
    
    Vector3 Transform::GetForwards() const noexcept
    {
        return GetWorldRotation() * Vector3Constants::k_forwards;
    }

    Vector3 Transform::GetRight() const noexcept
    {
        return GetWorldRotation() * Vector3Constants::k_right;
    }

    Vector3 Transform::GetUp() const noexcept
    {
        return GetWorldRotation() * Vector3Constants::k_up;
    }

    Matrix4x4 Transform::GetLocalModelMatrix() const noexcept
    {
        return Matrix4x4(1.0F).Translate(GetLocalPosition())
                              .Rotate(GetLocalRotation())
                              .Scale(GetLocalScale());
    }

    Matrix4x4 Transform::GetWorldModelMatrix() const noexcept
    {
        return Matrix4x4(1.0F).Translate(GetWorldPosition())
                              .Rotate(GetWorldRotation())
                              .Scale(GetWorldScale());
    }

    Vector3 Transform::TransformPointToWorldSpace(const Vector3 &point) const noexcept
    {
        Vector4 position(point, 1.0F);
        position = GetWorldModelMatrix() * position;
        return Vector3(position.x(), position.y(), position.z());
    }

    Vector3 Transform::TransformPointToLocalSpace(const Vector3 &point) const noexcept
    {
        Vector4 position(point, 1.0F);
        position = Matrix4x4::Inverse(GetWorldModelMatrix()) * position;
        return Vector3(position.x(), position.y(), position.z());
    }

    void Transform::SetParent(std::weak_ptr<Transform> parent) noexcept
    {
        if (m_parent.lock() != nullptr)
        {
            m_parent.lock()->RemoveChild(shared_from_this());
        }

        m_parent = parent;

        if (parent.lock() != nullptr)
        {
            parent.lock()->AddChild(shared_from_this());
        }

        UpdateLocalToWorldAndWorldToLocalVariables();
    }

    void Transform::AddChild(const std::shared_ptr<Transform> &child) try
    {
        auto child_already_in_children_iterator = std::find(m_children.cbegin(), m_children.cend(), child);
        bool is_child_added = (child_already_in_children_iterator != m_children.cend());

        if (is_child_added)
        {
            throw std::range_error("Could not add child to current transform because child"
                                   " has already been added previously.");
        }

        m_children.push_back(child);
    }
    CATCH_RETHROW_EXCEPTIONS
    
    void Transform::AddChild(const std::shared_ptr<Transform> &child, std::size_t position) try
    {
        auto child_already_in_children_iterator = std::find(m_children.cbegin(), m_children.cend(), child);
        bool is_child_added = (child_already_in_children_iterator != m_children.cend());

        if (is_child_added)
        {
            throw std::range_error("Could not add child to current transform because child"
                                   " has already been added previously.");
        }

        if (position > m_children.size())
        {
            throw std::out_of_range("Could not add child at index " + std::to_string(position) + ".");
        }

        (void)m_children.insert(m_children.begin() + position, child);
    }
    CATCH_RETHROW_EXCEPTIONS

    void Transform::RemoveChild(const std::shared_ptr<Transform> &child) try
    {
        auto child_already_in_children_iterator = std::find(m_children.cbegin(), m_children.cend(), child);
        bool is_child_added = (child_already_in_children_iterator != m_children.cend());

        if (!is_child_added)
        {
            throw std::range_error("Could not find child to remove.");
        }

        (void)m_children.erase(child_already_in_children_iterator);
    }
    CATCH_RETHROW_EXCEPTIONS

    void Transform::RemoveChild(std::size_t position) try
    {
        if (position >= m_children.size())
        {
            throw std::out_of_range("Cannot remove child at " + std::to_string(position)
                                    + " bause current transform has " + std::to_string(m_children.size())
                                    + " children.");
        }
        (void)m_children.erase(m_children.begin() + position);
    }
    CATCH_RETHROW_EXCEPTIONS

    Matrix4x4 Transform::CalculateLocalToWorldModelMatrix() const noexcept
    {
        Matrix4x4 local_matrix(1.0F);
        auto parent = m_parent;

        while (parent.lock() != nullptr)
        {
            Matrix4x4 parent_local_matrix = parent.lock()->GetLocalModelMatrix();
            local_matrix = parent_local_matrix * local_matrix;
            parent = parent.lock()->m_parent;
        }

        return local_matrix;
    }

    Matrix4x4 Transform::CalculateWorldToLocalModelMatrix() const noexcept
    {
        return Matrix4x4::Inverse(CalculateLocalToWorldModelMatrix());
    }

    Matrix4x4 Transform::CalculateWorldToLocalModelMatrix(const Matrix4x4 &local_to_world) const noexcept
    {
        return Matrix4x4::Inverse(local_to_world);
    }
    
    Quaternion Transform::CalculateLocalToWorldRotation() const noexcept
    {
        Quaternion q = QuaternionConstants::k_identity;
        
        auto parent = m_parent;

        while (parent.lock() != nullptr)
        {
            Quaternion parent_rotation = parent.lock()->GetLocalRotation();
            q *= parent_rotation;
            parent = parent.lock()->m_parent;
        }

        return q;
    }
    
    Quaternion Transform::CalculateWorldToLocalRotation() const noexcept
    {
        return Quaternion::Inverse(CalculateLocalToWorldRotation());
    }

    Quaternion Transform::CalculateWorldToLocalRotation(const Quaternion &local_rotation) const noexcept
    {
        return Quaternion::Inverse(local_rotation);
    }
    
    Vector3 Transform::CalculateLocalToWorldScale() const noexcept
    {
        Vector3 scale = Vector3Constants::k_one;

        auto parent = m_parent;

        while (parent.lock() != nullptr)
        {
            Vector3 parent_scale = parent.lock()->GetLocalScale();
            scale.Scale(parent_scale);
            parent = parent.lock()->m_parent;
        }

        return scale;
    }
    
    Vector3 Transform::CalculateWorldToLocalScale() const noexcept
    {
        Vector3 scale = CalculateLocalToWorldScale();
        return Vector3(1.0F / scale.x(), 1.0F / scale.y(), 1.0F / scale.z());
    }

    Vector3 Transform::CalculateWorldToLocalScale(const Vector3 &local_scale) const noexcept
    {
        return Vector3(1.0F / local_scale.x(), 1.0F / local_scale.y(), 1.0F / local_scale.z());
    }

    void Transform::UpdateLocalToWorldAndWorldToLocalVariables() noexcept
    {
        m_local_to_world_model_matrix = CalculateLocalToWorldModelMatrix();
        m_world_to_local_model_matrix = CalculateWorldToLocalModelMatrix(m_local_to_world_model_matrix);

        m_local_to_world_rotation = CalculateLocalToWorldRotation();
        m_world_to_local_rotation = CalculateWorldToLocalRotation(m_local_to_world_rotation);

        m_local_to_world_scale = CalculateLocalToWorldScale();
        m_world_to_local_scale = CalculateWorldToLocalScale(m_local_to_world_scale);
    }

    void Transform::UpdateLocalToWorldAndWorldToLocalVariablesForChildren() noexcept
    {
        for (auto &child : m_children)
        {
            child->m_local_to_world_model_matrix = m_local_to_world_model_matrix * GetLocalModelMatrix();
            child->m_world_to_local_model_matrix = CalculateWorldToLocalModelMatrix(child->m_local_to_world_model_matrix);

            child->m_local_to_world_rotation = m_local_to_world_rotation * GetLocalRotation();
            child->m_world_to_local_rotation = CalculateWorldToLocalRotation(child->m_local_to_world_rotation);

            child->m_local_to_world_scale = Vector3::Scale(m_local_to_world_scale, GetLocalScale());
            child->m_world_to_local_scale = CalculateWorldToLocalScale(child->m_local_to_world_scale);

            child->UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
        }
    }

    nlohmann::json Transform::Serialize() const try
    {
        namespace Constants = TransformJSONConstants;

        nlohmann::json json;
        json[Constants::k_parent_node][Constants::k_uid_attribute] = m_uid;
        json[Constants::k_parent_node][Constants::k_local_position_attribute] = {
            m_local_position.x(), m_local_position.y(), m_local_position.z()
        };
        json[Constants::k_parent_node][Constants::k_local_rotation_attribute] = {
            m_local_rotation.w(), m_local_rotation.x(), m_local_rotation.y(), m_local_rotation.z()
        };
        json[Constants::k_parent_node][Constants::k_local_scale_attribute] = {
            m_local_scale.x(), m_local_scale.y(), m_local_scale.z()
        };

        if (m_children.size() > 0U)
        {
            std::vector<nlohmann::json> children_json;
            children_json.reserve(m_children.size());

            for (const auto &child : m_children)
            {
                children_json.push_back(child->Serialize());
            }

            json[Constants::k_parent_node][Constants::k_game_object_attribute] = children_json;
        }

        if (m_game_object != nullptr)
        {
            const auto &game_object_json = m_game_object->Serialize()[GameObjectJSONConstants::k_parent_node];
            json[Constants::k_parent_node][Constants::k_game_object_attribute] = game_object_json;
        }

        return json;
    }
    CATCH_RETHROW_EXCEPTIONS

    void Transform::Deserialize(const nlohmann::json &json) try
    {
        namespace Constants = TransformJSONConstants;

        const auto &transform_json = json.at(Constants::k_parent_node);
        const auto &local_position_json = transform_json.at(Constants::k_local_position_attribute);
        const auto &local_rotation_json = transform_json.at(Constants::k_local_rotation_attribute);
        const auto &local_scale_json = transform_json.at(Constants::k_local_scale_attribute);
        
        m_uid = transform_json.at(Constants::k_uid_attribute);

        m_local_position.x() = local_position_json.at(0);
        m_local_position.y() = local_position_json.at(1);
        m_local_position.z() = local_position_json.at(2);

        m_local_rotation.w() = local_rotation_json.at(0);
        m_local_rotation.x() = local_rotation_json.at(1);
        m_local_rotation.y() = local_rotation_json.at(2);
        m_local_rotation.z() = local_rotation_json.at(3);

        m_local_scale.x() = local_scale_json.at(0);
        m_local_scale.y() = local_scale_json.at(1);
        m_local_scale.z() = local_scale_json.at(2);

        if (transform_json.contains(Constants::k_children_attribute))
        {
            const nlohmann::json children_json;
            m_children.reserve(children_json.size());

            for (const auto &child_json : transform_json[Constants::k_children_attribute])
            {
                auto child = Transform::Create();
                child->SetParent(shared_from_this());
                child->Deserialize(child_json);
            }
        }

        if (transform_json.contains(Constants::k_game_object_attribute))
        {
            m_game_object = GameObject::Create();
            m_game_object->SetTransform(shared_from_this());
            
            m_game_object->Deserialize(transform_json);
        }
    }
    CATCH_RETHROW_EXCEPTIONS

    void Transform::LateBindAfterDeserialization(Scene &scene) try
    {
        if (m_game_object != nullptr)
        {
            m_game_object->LateBindAfterDeserialization(scene);
        }
        for (auto &child : m_children)
        {
            child->LateBindAfterDeserialization(scene);
        }
    }
    CATCH_RETHROW_EXCEPTIONS
}
