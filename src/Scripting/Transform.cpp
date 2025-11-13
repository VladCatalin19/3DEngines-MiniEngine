#include "Transform.hpp"

#include <Constants/JSONConstants.hpp>
#include <Constants/MathConstants.hpp>
#include <Math/Vector4.hpp>
#include <Scripting/GameObject.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

namespace MG3TR
{
    Transform::Transform()
        : m_local_position(Vector3Constants::k_zero),
          m_local_rotation(QuaternionConstants::k_identity),
          m_local_scale(Vector3Constants::k_one),
          m_parent(),
          m_game_object(nullptr),
          m_uid(s_uid_generator.GetNextUID())
    {
        UpdateLocalToWorldAndWorldToLocalVariables();
    }

    [[nodiscard]] std::shared_ptr<Transform> Transform::Create()
    {
        auto ptr = std::shared_ptr<Transform>(new Transform());
        return ptr;
    }

    bool Transform::operator==(const Transform &other) const
    {
        const bool are_equal = (m_uid == other.m_uid);
        return are_equal;
    }

    bool Transform::operator!=(const Transform &other) const
    {
        const bool are_not_equal = (m_uid != other.m_uid);
        return are_not_equal;
    }

    Vector3 Transform::GetLocalPosition() const
    {
        return m_local_position;
    }

    void Transform::SetLocalPosition(const Vector3 &local_position)
    {
        m_local_position = local_position;
        UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    }

    Quaternion Transform::GetLocalRotation() const
    {
        return m_local_rotation;
    }
    
    void Transform::SetLocalRotation(const Quaternion &local_rotation)
    {
        m_local_rotation = local_rotation;
        UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    }

    Vector3 Transform::GetLocalScale() const
    {
        return m_local_scale;
    }
    
    void Transform::SetLocalScale(const Vector3 &local_scale)
    {
        m_local_scale = local_scale;
        UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    }

    Vector3 Transform::GetWorldPosition() const
    {
        Vector4 position(m_local_position, 1.0F);
        position = m_local_to_world_model_matrix * position;
        const Vector3 world_position(position.x(), position.y(), position.z());

        return world_position;
    }

    void Transform::SetWorldPosition(const Vector3 &world_position)
    {
        Vector4 position(world_position, 1.0F);
        position = m_world_to_local_model_matrix * position;
        const Vector3 local_position(position.x(), position.y(), position.z());
        SetLocalPosition(local_position);
    }
    
    Quaternion Transform::GetWorldRotation() const
    {
        const auto world_rotation = m_local_to_world_rotation * m_local_rotation;
        return world_rotation;
    }

    void Transform::SetWorldRotation(const Quaternion &world_rotation)
    {
        const auto local_rotation = world_rotation * m_world_to_local_rotation;
        SetLocalRotation(local_rotation);
    }
    
    Vector3 Transform::GetWorldScale() const
    {
        const auto world_scale = Vector3::Scale(m_local_to_world_scale, m_local_scale);
        return world_scale;
    }

    void Transform::SetWorldScale(const Vector3 &world_scale)
    {
        const auto local_scale = Vector3::Scale(m_world_to_local_scale, world_scale);
        SetLocalScale(local_scale);
    }
    
    Vector3 Transform::GetForwards() const
    {
        const auto forwads = GetWorldRotation() * Vector3Constants::k_forwards;
        return forwads;
    }

    Vector3 Transform::GetRight() const
    {
        const auto right = GetWorldRotation() * Vector3Constants::k_right;
        return right;
    }

    Vector3 Transform::GetUp() const
    {
        const auto up = GetWorldRotation() * Vector3Constants::k_up;
        return up;
    }

    Matrix4x4 Transform::GetLocalToWorldMatrix() const
    {
        return m_local_to_world_model_matrix;
    }

    Matrix4x4 Transform::GetWorldToLocalMatrix() const
    {
        return m_world_to_local_model_matrix;
    }

    Matrix4x4 Transform::GetLocalModelMatrix() const
    {
        const auto local_position = GetLocalPosition();
        const auto local_rotation = GetLocalRotation();
        const auto local_scale = GetLocalScale();

        auto mat = Matrix4x4(1.0F);
        (void)mat.Translate(local_position);
        (void)mat.Rotate(local_rotation);
        (void)mat.Scale(local_scale);

        return mat;
    }

    Matrix4x4 Transform::GetWorldModelMatrix() const
    {
        const auto world_position = GetWorldPosition();
        const auto world_rotation = GetWorldRotation();
        const auto world_scale = GetWorldScale();

        auto mat = Matrix4x4(1.0F);
        (void)mat.Translate(world_position);
        (void)mat.Rotate(world_rotation);
        (void)mat.Scale(world_scale);

        return mat;
    }

    Vector3 Transform::TransformPointToWorldSpace(const Vector3 &point) const
    {
        Vector4 position(point, 1.0F);
        position = GetWorldModelMatrix() * position;
        const Vector3 world_space_position(position.x(), position.y(), position.z());

        return world_space_position;
    }

    Vector3 Transform::TransformPointToLocalSpace(const Vector3 &point) const
    {
        Vector4 position(point, 1.0F);
        position = Matrix4x4::Inverse(GetWorldModelMatrix()) * position;
        const  Vector3 local_space_position(position.x(), position.y(), position.z());

        return local_space_position;
    }

    std::weak_ptr<Transform> Transform::GetParent() const
    {
        return m_parent;
    }

    void Transform::SetParent(std::weak_ptr<Transform> parent)
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

    std::vector<std::shared_ptr<Transform>>& Transform::GetChildren()
    {
        return m_children;
    }

    const std::vector<std::shared_ptr<Transform>>& Transform::GetChildren() const
    {
        return m_children;
    }

    std::shared_ptr<GameObject> Transform::GetGameObject() const
    {
        return m_game_object;
    }

    void Transform::SetGameObject(const std::shared_ptr<GameObject> &game_object)
    {
        m_game_object = game_object;
    }

    TUID Transform::GetUID() const
    {
        return m_uid;
    }

    void Transform::AddChild(const std::shared_ptr<Transform> &child)
    {
        const auto child_already_in_children_iterator = std::find(m_children.cbegin(), m_children.cend(), child);
        const bool is_child_added = (child_already_in_children_iterator != m_children.cend());

        if (is_child_added)
        {
            throw ExceptionWithStacktrace("Could not add child to current transform because child"
                                          " has already been added previously.");
        }

        m_children.push_back(child);
    }
    
    void Transform::AddChild(const std::shared_ptr<Transform> &child, const std::size_t position)
    {
        const auto child_already_in_children_iterator = std::find(m_children.cbegin(), m_children.cend(), child);
        const bool is_child_added = (child_already_in_children_iterator != m_children.cend());

        if (is_child_added)
        {
            throw ExceptionWithStacktrace("Could not add child to current transform because child"
                                          " has already been added previously.");
        }

        const std::size_t children_size = m_children.size();
        if (position > children_size)
        {
            const std::string string = std::format("Could not add child at index {}.", position);
            throw ExceptionWithStacktrace(string);
        }

        (void)m_children.insert(m_children.begin() + position, child);
    }

    void Transform::RemoveChild(const std::shared_ptr<Transform> &child)
    {
        const auto child_already_in_children_iterator = std::find(m_children.cbegin(), m_children.cend(), child);
        const bool is_child_added = (child_already_in_children_iterator != m_children.cend());

        if (!is_child_added)
        {
            throw ExceptionWithStacktrace("Could not find child to remove.");
        }

        (void)m_children.erase(child_already_in_children_iterator);
    }

    void Transform::RemoveChild(const std::size_t position)
    {
        const std::size_t children_size = m_children.size();
        if (position >= children_size)
        {
            const std::string string = std::format("Cannot remove child at position {} bause current transform has {} children.",
                                                   position, children_size);
            throw ExceptionWithStacktrace(string);
        }
        (void)m_children.erase(m_children.begin() + position);
    }

    Matrix4x4 Transform::CalculateLocalToWorldModelMatrix() const
    {
        Matrix4x4 local_matrix(1.0F);
        auto parent = m_parent;

        while (parent.lock() != nullptr)
        {
            const Matrix4x4 parent_local_matrix = parent.lock()->GetLocalModelMatrix();
            local_matrix = parent_local_matrix * local_matrix;
            parent = parent.lock()->m_parent;
        }

        return local_matrix;
    }

    Matrix4x4 Transform::CalculateWorldToLocalModelMatrix() const
    {
        const auto local_to_world = CalculateLocalToWorldModelMatrix();
        const auto inverse = Matrix4x4::Inverse(local_to_world);

        return inverse;
    }

    Matrix4x4 Transform::CalculateWorldToLocalModelMatrix(const Matrix4x4 &local_to_world) const
    {
        const auto inverse = Matrix4x4::Inverse(local_to_world);
        return inverse;
    }
    
    Quaternion Transform::CalculateLocalToWorldRotation() const
    {
        Quaternion q = QuaternionConstants::k_identity;
        
        auto parent = m_parent;

        while (parent.lock() != nullptr)
        {
            const Quaternion parent_rotation = parent.lock()->GetLocalRotation();
            q *= parent_rotation;
            parent = parent.lock()->m_parent;
        }

        return q;
    }
    
    Quaternion Transform::CalculateWorldToLocalRotation() const
    {
        const auto local_to_world = CalculateLocalToWorldRotation();
        const auto inverse = Quaternion::Inverse(local_to_world);
        return inverse;
    }

    Quaternion Transform::CalculateWorldToLocalRotation(const Quaternion &local_rotation) const
    {
        const auto inverse = Quaternion::Inverse(local_rotation);
        return inverse;
    }
    
    Vector3 Transform::CalculateLocalToWorldScale() const
    {
        Vector3 scale = Vector3Constants::k_one;

        auto parent = m_parent;

        while (parent.lock() != nullptr)
        {
            const Vector3 parent_scale = parent.lock()->GetLocalScale();
            scale.Scale(parent_scale);
            parent = parent.lock()->m_parent;
        }

        return scale;
    }
    
    Vector3 Transform::CalculateWorldToLocalScale() const
    {
        const Vector3 scale = CalculateLocalToWorldScale();
        const Vector3 inverse(1.0F / scale.x(), 1.0F / scale.y(), 1.0F / scale.z());

        return inverse;
    }

    Vector3 Transform::CalculateWorldToLocalScale(const Vector3 &local_scale) const
    {
        const Vector3 inverse(1.0F / local_scale.x(), 1.0F / local_scale.y(), 1.0F / local_scale.z());
        return inverse;
    }

    void Transform::UpdateLocalToWorldAndWorldToLocalVariables()
    {
        m_local_to_world_model_matrix = CalculateLocalToWorldModelMatrix();
        m_world_to_local_model_matrix = CalculateWorldToLocalModelMatrix(m_local_to_world_model_matrix);

        m_local_to_world_rotation = CalculateLocalToWorldRotation();
        m_world_to_local_rotation = CalculateWorldToLocalRotation(m_local_to_world_rotation);

        m_local_to_world_scale = CalculateLocalToWorldScale();
        m_world_to_local_scale = CalculateWorldToLocalScale(m_local_to_world_scale);
    }

    void Transform::UpdateLocalToWorldAndWorldToLocalVariablesForChildren()
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

    nlohmann::json Transform::Serialize() const
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

    void Transform::Deserialize(const nlohmann::json &json)
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

    void Transform::LateBindAfterDeserialization(Scene &scene)
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
}
