#include "Component.hpp"

#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>
#include <Window/Input.hpp>

namespace MG3TR
{
    Component::Component()
        : m_game_object(),
          m_transform(),
          m_uid(s_uid_generator.GetNextUID())
    {

    }
    
    Component::Component(const std::weak_ptr<GameObject>& game_object, const std::weak_ptr<Transform>& transform)
        : m_game_object(game_object),
          m_transform(transform),
          m_uid(s_uid_generator.GetNextUID())
    {
        
    }
    
    std::weak_ptr<GameObject> Component::GetGameObject() const
    {
        return m_game_object;
    }

    void Component::SetGameObject(const std::weak_ptr<GameObject>& game_object)
    {
        m_game_object = game_object;
    }

    std::weak_ptr<Transform> Component::GetTransform() const
    {
        return m_transform;
    }

    void Component::SetTransform(const std::weak_ptr<Transform>& transform)
    {
        m_transform = transform;
    }

    TUID Component::GetUID() const
    {
        return m_uid;
    }

    void Component::SetUID(TUID uid)
    {
        m_uid = uid;
    }

    void Component::Initialize()
    {

    }

    void Component::ParseInput([[maybe_unused]] const Input& input)
    {

    }

    void Component::FrameStart([[maybe_unused]] const float delta_time)
    {

    }

    void Component::FrameUpdate([[maybe_unused]] const float delta_time)
    {

    }

    void Component::FrameEnd([[maybe_unused]] const float delta_time)
    {
        
    }
}
