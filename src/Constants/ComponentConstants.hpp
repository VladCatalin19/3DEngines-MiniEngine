#ifndef MG3TR_SRC_CONSTANTS_COMPONENTCONSTANTS_HPP_INCLUDED
#define MG3TR_SRC_CONSTANTS_COMPONENTCONSTANTS_HPP_INCLUDED

#include <Components/ComponentType.hpp>
#include <Components/Camera.hpp>
#include <Components/CameraController.hpp>
#include <Components/MeshRenderer.hpp>
#include <Components/SkyboxFollowCamera.hpp>
#include <Components/TestMovement.hpp>
#include <Components/TestRotation.hpp>

#include <functional>
#include <typeindex>
#include <unordered_map>

namespace MG3TR::ComponentConstants
{
    const std::unordered_map<std::type_index, ComponentType> k_type_to_component = {
        { std::type_index(typeid(Camera)),             ComponentType::Camera },
        { std::type_index(typeid(CameraController)),   ComponentType::CameraController },
        { std::type_index(typeid(MeshRenderer)),       ComponentType::MeshRenderer },
        { std::type_index(typeid(SkyboxFollowCamera)), ComponentType::SkyboxFollowCamera },
        { std::type_index(typeid(TestMovement)),       ComponentType::TestMovement },
        { std::type_index(typeid(TestRotation)),       ComponentType::TestRotation }
    };

    using TComponentConstructor = std::function<std::shared_ptr<Component>(const std::weak_ptr<GameObject>&, const std::weak_ptr<Transform>&)>;

    template<typename ComponentType>
    std::shared_ptr<ComponentType> Construct(const std::weak_ptr<GameObject> &game_object, const std::weak_ptr<Transform> &transform)
    {
        auto component = std::make_shared<ComponentType>(game_object, transform);
        return component;
    }

    const std::unordered_map<ComponentType, TComponentConstructor> k_component_to_constructor = {
        { ComponentType::Camera,             TComponentConstructor(&Construct<Camera>) },
        { ComponentType::CameraController,   TComponentConstructor(&Construct<CameraController>) },
        { ComponentType::MeshRenderer,       TComponentConstructor(&Construct<MeshRenderer>) },
        { ComponentType::SkyboxFollowCamera, TComponentConstructor(&Construct<SkyboxFollowCamera>) },
        { ComponentType::TestMovement,       TComponentConstructor(&Construct<TestMovement>) },
        { ComponentType::TestRotation,       TComponentConstructor(&Construct<TestRotation>) }
    };
}

#endif // MG3TR_SRC_CONSTANTS_COMPONENTCONSTANTS_HPP_INCLUDED
