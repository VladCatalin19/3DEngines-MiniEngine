#ifndef MG3TR_SRC_SCENE_ILATEBINDABLE_HPP_INCLUDED
#define MG3TR_SRC_SCENE_ILATEBINDABLE_HPP_INCLUDED

namespace MG3TR
{
    class Scene;

    class ILateBindable
    {
    public:
        virtual ~ILateBindable() = default;
        virtual void LateBind(Scene &scene) = 0;
    };
}

#endif // MG3TR_SRC_SCENE_ILATEBINDABLE_HPP_INCLUDED
