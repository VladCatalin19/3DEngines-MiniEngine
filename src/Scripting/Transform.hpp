#ifndef MG3TR_SRC_SCRIPTING_TRANSFORM_HPP_INCLUDED
#define MG3TR_SRC_SCRIPTING_TRANSFORM_HPP_INCLUDED

#include <Math/Matrix4x4.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector3.hpp>

#include <Scene/IJsonSerializeable.hpp>
#include <Utils/UIDGenerator.hpp>

#include <cstddef>
#include <memory>
#include <vector>

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

        Transform();

    public:
        [[nodiscard]] static std::shared_ptr<Transform> Create();
        virtual ~Transform() = default;
    
        Transform(const Transform &) = delete;
        Transform(Transform &&) = delete;
        
        Transform& operator=(const Transform &) = delete;
        Transform& operator=(Transform&&) = delete;

        bool operator==(const Transform &other) const;
        bool operator!=(const Transform &other) const;

        Vector3 GetLocalPosition() const;
        void SetLocalPosition(const Vector3 &local_position);

        Quaternion GetLocalRotation() const ;
        void SetLocalRotation(const Quaternion &local_rotation);

        Vector3 GetLocalScale() const;
        void SetLocalScale(const Vector3 &local_scale);

        Vector3 GetWorldPosition() const;
        void SetWorldPosition(const Vector3 &world_position);

        Quaternion GetWorldRotation() const;
        void SetWorldRotation(const Quaternion &world_rotation);

        Vector3 GetWorldScale() const;
        void SetWorldScale(const Vector3 &world_scale);

        Vector3 GetForwards() const;
        Vector3 GetRight() const;
        Vector3 GetUp() const;

        Matrix4x4 GetLocalToWorldMatrix() const;
        Matrix4x4 GetWorldToLocalMatrix() const;

        Matrix4x4 GetLocalModelMatrix() const;
        Matrix4x4 GetWorldModelMatrix() const;

        Vector3 TransformPointToWorldSpace(const Vector3 &point) const;
        Vector3 TransformPointToLocalSpace(const Vector3 &point) const;

        std::weak_ptr<Transform> GetParent() const;
        void SetParent(std::weak_ptr<Transform> parent);

        std::vector<std::shared_ptr<Transform>>& GetChildren();
        const std::vector<std::shared_ptr<Transform>>& GetChildren() const;

        std::shared_ptr<GameObject> GetGameObject() const;
        void SetGameObject(const std::shared_ptr<GameObject> &game_object);

        TUID GetUID() const;

        void AddChild(const std::shared_ptr<Transform> &child);
        void AddChild(const std::shared_ptr<Transform> &child, const std::size_t position);

        void RemoveChild(const std::shared_ptr<Transform> &child);
        void RemoveChild(const std::size_t position);

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        Matrix4x4 CalculateLocalToWorldModelMatrix() const;
        Matrix4x4 CalculateWorldToLocalModelMatrix() const;
        Matrix4x4 CalculateWorldToLocalModelMatrix(const Matrix4x4 &local_to_world) const;

        Quaternion CalculateLocalToWorldRotation() const;
        Quaternion CalculateWorldToLocalRotation() const;
        Quaternion CalculateWorldToLocalRotation(const Quaternion &local_rotation) const;

        Vector3 CalculateLocalToWorldScale() const;
        Vector3 CalculateWorldToLocalScale() const;
        Vector3 CalculateWorldToLocalScale(const Vector3 &local_scale) const;

        void UpdateLocalToWorldAndWorldToLocalVariables();
        void UpdateLocalToWorldAndWorldToLocalVariablesForChildren();
    };
}

#endif // MG3TR_SRC_SCRIPTING_TRANSFORM_HPP_INCLUDED
