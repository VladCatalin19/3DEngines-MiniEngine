#ifndef MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED
#define MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED

#include <Scene/ILateBindable.hpp>
#include <Serialisation/ISerialisable.hpp>
#include <Utils/UIDGenerator.hpp>

#include <memory>

namespace MG3TR
{
    class GameObject;
    class Transform;
    class Input;

    class Component : public ISerialisable, public ILateBindable
    {
    private:
        std::weak_ptr<GameObject> m_game_object;
        std::weak_ptr<Transform> m_transform;

        static inline UIDGenerator s_uid_generator;
        TUID m_uid;

    public:
        Component();
        Component(const std::weak_ptr<GameObject>& game_object, const std::weak_ptr<Transform>& transform);
        virtual ~Component() = default;

        Component(const Component &) = delete;
        Component(Component &&) = default;
        
        Component& operator=(const Component &) = delete;
        Component& operator=(Component &&) = default;

        std::weak_ptr<GameObject> GetGameObject() const;
        void SetGameObject(const std::weak_ptr<GameObject> &game_object);

        std::weak_ptr<Transform> GetTransform() const;
        void SetTransform(const std::weak_ptr<Transform> &transform);

        TUID GetUID() const;

    protected:
        void SetUID(TUID uid);

    public:
        virtual void Initialize();

        virtual void ParseInput([[maybe_unused]] const Input &input);

        virtual void FrameStart([[maybe_unused]] const float delta_time);
        virtual void FrameUpdate([[maybe_unused]] const float delta_time);
        virtual void FrameEnd([[maybe_unused]] const float delta_time);

        virtual void LateBind([[maybe_unused]] Scene &scene) override;
    };
}

#endif // MG3TR_SRC_COMPONENTS_COMPONENT_HPP_INCLUDED
