#ifndef MG3TR_SRC_SCRIPTING_TRANSFORM_HPP_INCLUDED
#define MG3TR_SRC_SCRIPTING_TRANSFORM_HPP_INCLUDED

#include <Math/Matrix4x4.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector3.hpp>

#include <Constants/MathConstants.hpp>

#include <Scene/IJsonSerializeable.hpp>
#include <Utils/UIDGenerator.hpp>

#include <cstdint>              // std::uint32_t
#include <cstddef>              // std::size_t
#include <memory>               // std::enable_shared_from_this, std::shared_ptr, std::weak_ptr
#include <vector>               // std::vector

namespace MG3TR
{
    class GameObject;

    class Transform : public IJsonSerializeable, public std::enable_shared_from_this<Transform>
    {
    private:
        Vector3 m_local_position;
        Quaternion m_local_rotation;
        Vector3 m_local_scale;

        Matrix4x4 m_local_to_world_model_matrix;
        Matrix4x4 m_world_to_local_model_matrix;

        Quaternion m_local_to_world_rotation;
        Quaternion m_world_to_local_rotation;

        Vector3 m_local_to_world_scale;
        Vector3 m_world_to_local_scale;

        std::weak_ptr<Transform> m_parent;
        std::vector<std::shared_ptr<Transform>> m_children;

        std::shared_ptr<GameObject> m_game_object;

        static inline UIDGenerator s_uid_generator;
        TUID m_uid;

        Transform() noexcept;

    public:
        [[nodiscard]] static std::shared_ptr<Transform> Create();
        virtual ~Transform() noexcept = default;
    
        Transform(const Transform &) = delete;
        Transform& operator=(const Transform &) = delete;

        Transform(Transform &&) noexcept = delete;
        Transform& operator=(Transform&&) noexcept = delete;

        bool operator==(const Transform &other) const noexcept { return m_uid == other.m_uid; }
        bool operator!=(const Transform &other) const noexcept { return m_uid != other.m_uid; }

        Vector3 GetLocalPosition() const noexcept { return m_local_position; }
        void SetLocalPosition(const Vector3 &local_position) noexcept;

        Quaternion GetLocalRotation() const noexcept { return m_local_rotation; }
        void SetLocalRotation(const Quaternion &local_rotation) noexcept;

        Vector3 GetLocalScale() const noexcept { return m_local_scale; }
        void SetLocalScale(const Vector3 &local_scale) noexcept;

        Vector3 GetWorldPosition() const noexcept;
        void SetWorldPosition(const Vector3 &world_position) noexcept;

        Quaternion GetWorldRotation() const noexcept;
        void SetWorldRotation(const Quaternion &world_rotation) noexcept;

        Vector3 GetWorldScale() const noexcept;
        void SetWorldScale(const Vector3 &world_scale) noexcept;

        Vector3 GetForwards() const noexcept;
        Vector3 GetRight() const noexcept;
        Vector3 GetUp() const noexcept;

        Matrix4x4 GetLocalToWorldMatrix() const noexcept { return m_local_to_world_model_matrix; }
        Matrix4x4 GetWorldToLocalMatrix() const noexcept { return m_world_to_local_model_matrix; }

        Matrix4x4 GetLocalModelMatrix() const noexcept;
        Matrix4x4 GetWorldModelMatrix() const noexcept;

        Vector3 TransformPointToWorldSpace(const Vector3 &point) const noexcept;
        Vector3 TransformPointToLocalSpace(const Vector3 &point) const noexcept;

        std::weak_ptr<Transform> GetParent() const noexcept { return m_parent; }
        void SetParent(std::weak_ptr<Transform> parent) noexcept;

        std::vector<std::shared_ptr<Transform>>& GetChildren() noexcept { return m_children; }
        const std::vector<std::shared_ptr<Transform>>& GetChildren() const noexcept { return m_children; }

        std::shared_ptr<GameObject> GetGameObject() const noexcept { return m_game_object; }
        void SetGameObject(const std::shared_ptr<GameObject> &game_object) { m_game_object = game_object; }

        TUID GetUID() const { return m_uid; }

        void AddChild(const std::shared_ptr<Transform> &child);
        void AddChild(const std::shared_ptr<Transform> &child, std::size_t position);

        void RemoveChild(const std::shared_ptr<Transform> &child);
        void RemoveChild(std::size_t position);

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        Matrix4x4 CalculateLocalToWorldModelMatrix() const noexcept;
        Matrix4x4 CalculateWorldToLocalModelMatrix() const noexcept;
        Matrix4x4 CalculateWorldToLocalModelMatrix(const Matrix4x4 &local_to_world) const noexcept;

        Quaternion CalculateLocalToWorldRotation() const noexcept;
        Quaternion CalculateWorldToLocalRotation() const noexcept;
        Quaternion CalculateWorldToLocalRotation(const Quaternion &local_rotation) const noexcept;

        Vector3 CalculateLocalToWorldScale() const noexcept;
        Vector3 CalculateWorldToLocalScale() const noexcept;
        Vector3 CalculateWorldToLocalScale(const Vector3 &local_scale) const noexcept;

        void UpdateLocalToWorldAndWorldToLocalVariables() noexcept;
        void UpdateLocalToWorldAndWorldToLocalVariablesForChildren() noexcept;
    };
}

#endif // MG3TR_SRC_SCRIPTING_TRANSFORM_HPP_INCLUDED
