#include "Component.hpp"

#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

namespace MG3TR
{
    Component::Component() noexcept
        : m_game_object(),
          m_transform(),
          m_uid(s_uid_generator.GetNextUID())
    {}
    
    Component::Component(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform) noexcept
        : m_game_object(game_object),
          m_transform(transform),
          m_uid(s_uid_generator.GetNextUID())
    {}
}
