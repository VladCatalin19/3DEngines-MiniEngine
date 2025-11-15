#include "Scene.hpp"

#include <Components/Camera.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>
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

static std::string CalculateIndentation(const unsigned indent)
{
    std::string result;

    for (unsigned current_indent = 0U; current_indent < indent; ++current_indent)
    {
        result += "|...";
    }
    return result;
}

static std::string TransformToString(const MG3TR::Transform &transform, const unsigned indent = 0U)
{
    std::string result;
    const bool has_transform_name = (transform.GetGameObject() != nullptr);
    const std::string name = has_transform_name ? transform.GetGameObject()->GetName() : "";

    result += CalculateIndentation(indent) + "Transform: " + name + "\n";
    result += CalculateIndentation(indent + 1) + "Local Position: " + transform.GetLocalPosition().ToString() + "\n";
    result += CalculateIndentation(indent + 1) + "Local Rotation: " + transform.GetLocalRotation().EulerAngles().ToString() + "\n";
    result += CalculateIndentation(indent + 1) + "Local Scale:    " + transform.GetLocalScale().ToString() + "\n";
    result += CalculateIndentation(indent + 1) + "|\n";
    result += CalculateIndentation(indent + 1) + "World Position: " + transform.GetWorldPosition().ToString() + "\n";
    result += CalculateIndentation(indent + 1) + "World Rotation: " + transform.GetWorldRotation().EulerAngles().ToString() + "\n";
    result += CalculateIndentation(indent + 1) + "World Scale:    " + transform.GetWorldScale().ToString() + "\n";
    result += CalculateIndentation(indent + 1) + "|\n";

    if (transform.GetGameObject() != nullptr)
    {
        result += CalculateIndentation(indent + 1) + "Components:\n";

        for (auto &component : transform.GetGameObject()->GetComponents())
        {
            result += CalculateIndentation(indent + 2) + " UID: " + std::to_string(component->GetUID()) + "\n";
        }
    }

    result += CalculateIndentation(indent + 1) + "Children:\n";

    if (transform.GetChildren().size() == 0U)
    {
        result += CalculateIndentation(indent + 2) + " None\n";
        result += CalculateIndentation(indent + 2) + "|\n";
    }
    else
    {
        for (auto &child : transform.GetChildren())
        {
            result += TransformToString(*child, indent + 2);
        }
    }

    return result;
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

    std::string Scene::ToString() const
    {
        return TransformToString(*m_root_transform);
    }
    
    void Scene::LoadFromFile(const std::string &file_name)
    {
        std::ifstream stream(file_name);
        nlohmann::json json;
        (void)(stream >> json);

        m_root_transform = Transform::Create();

        m_root_transform->Deserialize(json);
        m_root_transform->LateBindAfterDeserialization(*this);
    }
    
    void Scene::SaveToFile(const std::string &file_name) const
    {
        std::ofstream stream(file_name);
        (void)(stream << std::setw(4) << m_root_transform->Serialize() << std::endl);
    }

    std::ostream& operator<<(std::ostream &os, const MG3TR::Scene &scene)
    {
        return os << scene.ToString();
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
