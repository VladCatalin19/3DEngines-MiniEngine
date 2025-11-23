#include "Scene.hpp"

#include <Components/Camera.hpp>
#include <Constants/SerialisationConstants.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>
#include <Serialisation/JSONDeserialiser.hpp>
#include <Serialisation/JSONSerialiser.hpp>
#include <Window/Input.hpp>

#include <fstream>
#include <memory>
#include <iomanip>
#include <string>

static void CallInitialize(MG3TR::Transform &root_transform)
{
    auto game_object = root_transform.GetGameObject();
    if (game_object != nullptr)
    {
        for (auto &component : game_object->GetComponents())
        {
            component->Initialize();
        }
    }

    for (auto &child : root_transform.GetChildren())
    {
        CallInitialize(*child);
    }
}

static void CallParseInput(MG3TR::Transform &root_transform, const MG3TR::Input &input)
{
    auto game_object = root_transform.GetGameObject();
    if (game_object != nullptr)
    {
        for (auto &component : game_object->GetComponents())
        {
            component->ParseInput(input);
        }
    }

    for (auto &child : root_transform.GetChildren())
    {
        CallParseInput(*child, input);
    }
}

static void CallFrameStart(MG3TR::Transform &root_transform, const float delta_time)
{
    auto game_object = root_transform.GetGameObject();
    if (game_object != nullptr)
    {
        for (auto &component : game_object->GetComponents())
        {
            component->FrameStart(delta_time);
        }
    }

    for (auto &child : root_transform.GetChildren())
    {
        CallFrameStart(*child, delta_time);
    }
}

static void CallFrameUpdate(MG3TR::Transform &root_transform, const float delta_time)
{
    auto game_object = root_transform.GetGameObject();
    if (game_object != nullptr)
    {
        for (auto &component : game_object->GetComponents())
        {
            component->FrameUpdate(delta_time);
        }
    }

    for (auto &child : root_transform.GetChildren())
    {
        CallFrameUpdate(*child, delta_time);
    }
}

static void CallFrameEnd(MG3TR::Transform &root_transform, const float delta_time)
{
    auto game_object = root_transform.GetGameObject();
    if (game_object != nullptr)
    {
        for (auto &component : game_object->GetComponents())
        {
            component->FrameEnd(delta_time);
        }
    }

    for (auto &child : root_transform.GetChildren())
    {
        CallFrameEnd(*child, delta_time);
    }
}

static std::shared_ptr<MG3TR::Camera> FindCameraWithUID(const std::shared_ptr<MG3TR::Transform> &transform, MG3TR::TUID uid)
{
    if (transform->GetGameObject() != nullptr)
    {
        for (auto &component : transform->GetGameObject()->GetComponents())
        {
            if (component->GetUID() == uid)
            {
                return std::dynamic_pointer_cast<MG3TR::Camera>(component);
            }
        }
    }

    std::shared_ptr<MG3TR::Camera> found_camera = nullptr;

    for (auto &child : transform->GetChildren())
    {
        auto camera = FindCameraWithUID(child, uid);
        if (camera != nullptr)
        {
            found_camera = camera;
            break;
        }
    }

    return found_camera;
}

static std::shared_ptr<MG3TR::Transform> FindTransformWithUID(const std::shared_ptr<MG3TR::Transform> &transform, MG3TR::TUID uid)
{
    if (transform->GetUID() == uid)
    {
        return transform;
    }

    std::shared_ptr<MG3TR::Transform> found_transform = nullptr;

    for (auto &child : transform->GetChildren())
    {
        auto transf = FindTransformWithUID(child, uid);
        if (transf != nullptr)
        {
            found_transform = transf;
            break;
        }
    }

    return found_transform;
}



namespace MG3TR
{
    Scene::Scene()
    {
        m_root_transform = Transform::Create();
    }

    Scene::Scene(const std::string &file_name)
    {
        LoadFromFile(file_name);
    }

    std::shared_ptr<Transform>& Scene::GetRootTransform()
    {
        return m_root_transform;
    }

    const std::shared_ptr<Transform>& Scene::GetRootTransform() const
    {
        return m_root_transform;
    }

    void Scene::Initialize()
    {
        CallInitialize(*m_root_transform);
    }

    void Scene::Update(const Input &input, const float delta_time)
    {
        CallParseInput(*m_root_transform, input);
        CallFrameStart(*m_root_transform, delta_time);
        CallFrameUpdate(*m_root_transform, delta_time);
        CallFrameEnd(*m_root_transform, delta_time);
    }
    
    void Scene::LoadFromFile(const std::string &file_name)
    {
        std::ifstream stream(file_name);
        nlohmann::json json;
        JSONDeserialiser deserialiser;

        (void)(stream >> json);
        deserialiser.SetJSON(json);

        m_root_transform = Transform::Create();

        deserialiser.BeginDeserialisingChild(TransformSerialisationConstants::k_parent_node);
        m_root_transform->Deserialise(deserialiser);
        deserialiser.EndDeserialisingLastChild();

        m_root_transform->LateBind(*this);

        /*
        m_root_transform->Deserialize(json);
        m_root_transform->LateBindAfterDeserialization(*this);
        */
    }
    
    void Scene::SaveToFile(const std::string &file_name) const
    {
        std::ofstream stream(file_name);
        JSONSerialiser serialiser;

        serialiser.BeginSerialisingChild(TransformSerialisationConstants::k_parent_node);
        m_root_transform->Serialise(serialiser);
        serialiser.EndSerialisingLastChild();

        auto json = serialiser.GetJSON();

        (void)(stream << std::setw(k_serialisation_indent) << json << std::endl);
    }

    std::shared_ptr<Camera> Scene::FindCameraWithUID(const TUID uid)
    {
        auto camera = ::FindCameraWithUID(m_root_transform, uid);
        return camera;
    }

    std::shared_ptr<Transform> Scene::FindTransformWithUID(const TUID uid)
    {
        auto transfrom = ::FindTransformWithUID(m_root_transform, uid);
        return transfrom;
    }
}
