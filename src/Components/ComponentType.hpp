#ifndef MG3TR_SRC_COMPONENT_COMPONENTTYPE_HPP_INCLUDED
#define MG3TR_SRC_COMPONENT_COMPONENTTYPE_HPP_INCLUDED

namespace MG3TR
{
    enum class ComponentType : unsigned char
    {
        Camera = 0,
        CameraController = 1,
        MeshRenderer = 2,
        SkyboxFollowCamera = 3,
        TestMovement = 4,
        TestRotation = 5
    };
}

#endif // MG3TR_SRC_COMPONENT_COMPONENTTYPE_HPP_INCLUDED
