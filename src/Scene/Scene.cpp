#include "Scene.hpp"

#include <Constants/GraphicsConstants.hpp>

#include <Components/Camera.hpp>
#include <Components/CameraController.hpp>
#include <Components/MeshRenderer.hpp>
#include <Components/SkyboxFollowCamera.hpp>
#include <Components/TestRotation.hpp>
#include <Components/TestMovement.hpp>

#include <Graphics/Mesh.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Shaders/FragmentNormalShader.hpp>
#include <Graphics/Shaders/TextureAndLightingShader.hpp>
#include <Graphics/Shaders/TextureShader.hpp>

#include <Math/Math.hxx>
#include <Math/Frustum.hpp>
#include <Math/Plane.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector3.hpp>

#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

#include <Window/Input.hpp>

#include <fstream>
#include <memory>
#include <iomanip>
#include <string>

#define CREATE_SCENE_ELEMENTS

#ifdef CREATE_SCENE_ELEMENTS
static std::shared_ptr<MG3TR::Camera> CreateCameraAndAddItToScene(MG3TR::Scene &scene)
{
    auto camera_game_object = MG3TR::GameObject::Create("Camera");
    auto camera_transform = MG3TR::Transform::Create();
    camera_game_object->SetTransform(camera_transform);
    camera_transform->SetGameObject(camera_game_object);
    camera_transform->SetParent(scene.GetRootTransform());

    MG3TR::Vector3 camera_position(0.0F, 3.0F, -5.0F);
    camera_transform->SetWorldPosition(camera_position);

    auto camera = std::make_shared<MG3TR::Camera>(camera_game_object, camera_transform,
                                                  90.0_rad, 4.0F / 3.0F, 0.001F, 300.0F);
    camera_game_object->AddComponent(camera);

    auto camera_controller = std::make_shared<MG3TR::CameraController>(camera_game_object, camera_transform, 2.0F, 5.0F, 12.0F);
    camera_game_object->AddComponent(camera_controller);

    return camera;
}



static std::shared_ptr<MG3TR::GameObject> CreateRotatingCubeAndAddItToScene(MG3TR::Scene &scene,
                                                                            std::shared_ptr<MG3TR::Camera> &camera)
{
    auto rotating_cube_game_object = MG3TR::GameObject::Create("Rotating Cube");
    auto rotating_cube_transform = MG3TR::Transform::Create();
    rotating_cube_game_object->SetTransform(rotating_cube_transform);
    rotating_cube_transform->SetGameObject(rotating_cube_game_object);
    rotating_cube_transform->SetParent(scene.GetRootTransform());
    
    rotating_cube_transform->SetWorldPosition( { 1.0F, 9.0F, 1.0F } );
    rotating_cube_transform->SetWorldRotation(MG3TR::Quaternion( { 0.0F, 90.0_rad, 0.0F } ));
    rotating_cube_transform->SetWorldScale( { 2.0F, 2.0F, 2.0F } );

    auto rotating_cube_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_cube_path);
    auto rotating_cube_shader = std::make_shared<MG3TR::FragmentNormalShader>(camera, rotating_cube_transform);

    auto rotating_cube_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(rotating_cube_game_object, rotating_cube_transform,
                                                                             rotating_cube_mesh, rotating_cube_shader, camera);
    rotating_cube_game_object->AddComponent(rotating_cube_mesh_renderer);

    auto rotating_script = std::make_shared<MG3TR::TestRotation>(rotating_cube_game_object, rotating_cube_transform);
    rotating_cube_game_object->AddComponent(rotating_script);

    return rotating_cube_game_object;
}



static std::shared_ptr<MG3TR::GameObject> CreateSecondRotatingCubeAndAddItAsChildToTheFirstCube(std::shared_ptr<MG3TR::Camera> &camera,
                                                                                                std::shared_ptr<MG3TR::GameObject> &rotating_cube_game_object)
{
    auto second_rotating_cube_game_object = MG3TR::GameObject::Create("Second Rotating Cube");
    auto second_rotating_cube_transform = MG3TR::Transform::Create();
    second_rotating_cube_game_object->SetTransform(second_rotating_cube_transform);
    second_rotating_cube_transform->SetGameObject(second_rotating_cube_game_object);
    second_rotating_cube_transform->SetParent(rotating_cube_game_object->GetTransform());
    
    second_rotating_cube_transform->SetLocalPosition( { 0.0F, 2.0F, 0.0F } );
    second_rotating_cube_transform->SetWorldRotation(MG3TR::Quaternion( { 0.0F, 90.0_rad, 0.0F } ));
    second_rotating_cube_transform->SetWorldScale( { 0.5F, 0.5F, 0.5F } );

    auto second_rotating_cube_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_cube_path);
    auto second_rotating_cube_shader = std::make_shared<MG3TR::FragmentNormalShader>(camera, second_rotating_cube_transform);

    auto second_rotating_cube_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(second_rotating_cube_game_object, second_rotating_cube_transform,
                                                                                    second_rotating_cube_mesh, second_rotating_cube_shader, camera);
    second_rotating_cube_game_object->AddComponent(second_rotating_cube_mesh_renderer);

    auto rotating_script = std::make_shared<MG3TR::TestMovement>(second_rotating_cube_game_object, second_rotating_cube_transform);
    second_rotating_cube_game_object->AddComponent(rotating_script);

    return second_rotating_cube_game_object;
}



static std::shared_ptr<MG3TR::GameObject> CreateSkyBox(MG3TR::Scene &scene, std::shared_ptr<MG3TR::Camera> &camera)
{
    auto skybox_game_object = MG3TR::GameObject::Create("Skybox");
    auto skybox_transform = MG3TR::Transform::Create();
    skybox_game_object->SetTransform(skybox_transform);
    skybox_transform->SetGameObject(skybox_game_object);
    skybox_transform->SetParent(scene.GetRootTransform());

    skybox_transform->SetWorldPosition( { 0.0F, 0.0F, 0.0F } );
    skybox_transform->SetWorldRotation(MG3TR::Quaternion( { 0.0F, 180.0_rad, 0.0F } ));
    skybox_transform->SetWorldScale( { 150.0F, 150.0F, 150.0F } );

    auto skybox_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_skybox_path);
    auto skybox_texture = skybox_mesh->GetMaterials().begin()->m_diffuse_texture;
    auto skybox_shader = std::make_shared<MG3TR::TextureShader>(camera, skybox_transform, skybox_texture);

    auto skybox_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(skybox_game_object, skybox_transform, skybox_mesh,
                                                                      skybox_shader, camera, false);
    skybox_game_object->AddComponent(skybox_mesh_renderer);

    auto skybox_follow_camera = std::make_shared<MG3TR::SkyboxFollowCamera>(skybox_game_object, skybox_transform, camera->GetTransform());
    skybox_game_object->AddComponent(skybox_follow_camera);

    return skybox_game_object;
}



static const MG3TR::Vector3 k_light_position(1'000.0F, 1'000.0F, 1'000.0F);

static std::shared_ptr<MG3TR::GameObject> CreateCreeper(MG3TR::Scene &scene, std::shared_ptr<MG3TR::Camera> &camera)
{
    auto creeper_game_object = MG3TR::GameObject::Create("Creeper");
    auto creeper_transform = MG3TR::Transform::Create();
    creeper_game_object->SetTransform(creeper_transform);
    creeper_transform->SetGameObject(creeper_game_object);
    creeper_transform->SetParent(scene.GetRootTransform());

    creeper_transform->SetWorldPosition( { 2.35F, 4.85F, 5.30F } );
    creeper_transform->SetWorldRotation(MG3TR::Quaternion( {0.0F, 180.0_rad, 0.0F} ));
    creeper_transform->SetWorldScale( { 2.0F, 2.0F, 2.0F } );

    auto creeper_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_creeper_path);
    auto creeper_texture = creeper_mesh->GetMaterials().begin()->m_diffuse_texture;
    auto creeper_shader = std::make_shared<MG3TR::TextureAndLightingShader>(camera, creeper_transform,
                                                                            creeper_texture, k_light_position);

    auto creeper_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(creeper_game_object, creeper_transform,
                                                                       creeper_mesh, creeper_shader, camera);
    creeper_game_object->AddComponent(creeper_mesh_renderer);




    auto sphere_game_object = MG3TR::GameObject::Create("Sphere");
    auto sphere_transform = MG3TR::Transform::Create();
    sphere_game_object->SetTransform(sphere_transform);
    sphere_transform->SetGameObject(sphere_game_object);
    sphere_transform->SetParent(creeper_transform);

    sphere_transform->SetWorldPosition(creeper_transform->TransformPointToWorldSpace(creeper_mesh_renderer->GetBoundingSphere().GetCenter()));
    sphere_transform->SetWorldScale(creeper_transform->GetWorldScale() * creeper_mesh_renderer->GetBoundingSphere().GetRadius());

    auto sphere_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_sphere_path);
    auto sphere_shader = std::make_shared<MG3TR::FragmentNormalShader>(camera, sphere_transform);

    auto sphere_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(sphere_game_object, sphere_transform,
                                                                      sphere_mesh, sphere_shader, camera);
    sphere_game_object->AddComponent(sphere_mesh_renderer);

    return creeper_game_object;
}



static std::shared_ptr<MG3TR::GameObject> CreateMap(MG3TR::Scene &scene, std::shared_ptr<MG3TR::Camera> &camera)
{
    auto map_game_object = MG3TR::GameObject::Create("Map");
    auto map_transform = MG3TR::Transform::Create();
    map_game_object->SetTransform(map_transform);
    map_transform->SetGameObject(map_game_object);
    map_transform->SetParent(scene.GetRootTransform());

    map_transform->SetWorldPosition( { 0.0F, 0.0F, 0.0F } );
    map_transform->SetWorldRotation(MG3TR::Quaternion( { 0.0F, 90.0_rad, 0.0F } ));
    map_transform->SetWorldScale( { 30.0F, 30.0F, 30.0F } );

    auto map_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_map_path);
    auto map_texture = map_mesh->GetMaterials().begin()->m_diffuse_texture;
    auto map_shader = std::make_shared<MG3TR::TextureAndLightingShader>(camera, map_transform, map_texture, k_light_position);

    auto map_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(map_game_object, map_transform, map_mesh, map_shader, camera);
    map_game_object->AddComponent(map_mesh_renderer);

    return map_game_object;
}



static std::shared_ptr<MG3TR::GameObject> CreatePlanet(MG3TR::Scene &scene, std::shared_ptr<MG3TR::Camera> &camera)
{
    auto planet_game_object = MG3TR::GameObject::Create("Planet");
    auto planet_transform = MG3TR::Transform::Create();
    planet_game_object->SetTransform(planet_transform);
    planet_transform->SetGameObject(planet_game_object);
    planet_transform->SetParent(scene.GetRootTransform());
    
    planet_transform->SetWorldPosition( { 10.0F, 10.0F, 0.0F } );
    planet_transform->SetWorldRotation(MG3TR::Quaternion( { 0.0F, 0.0F, 0.0F } ));
    planet_transform->SetWorldScale( { 1.0F, 1.0F, 1.0F } );

    auto planet_mesh = std::make_shared<MG3TR::Mesh>(MG3TR::SceneConstants::k_sphere_path);
    auto planet_texture = planet_mesh->GetMaterials().begin()->m_diffuse_texture;
    auto planet_shader = std::make_shared<MG3TR::TextureAndLightingShader>(camera, planet_transform,
                                                                           planet_texture, k_light_position);

    auto planet_mesh_renderer = std::make_shared<MG3TR::MeshRenderer>(planet_game_object, planet_transform,
                                                                      planet_mesh, planet_shader, camera);
    planet_game_object->AddComponent(planet_mesh_renderer);

    return planet_game_object;
}
#endif


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
#        ifdef CREATE_SCENE_ELEMENTS
            auto camera = CreateCameraAndAddItToScene(*this);
            auto rotating_cube_game_object = CreateRotatingCubeAndAddItToScene(*this, camera);
            (void)CreateSecondRotatingCubeAndAddItAsChildToTheFirstCube(camera, rotating_cube_game_object);
            (void)CreateCreeper(*this, camera);
            (void)CreateMap(*this, camera);
            (void)CreateSkyBox(*this, camera);
            (void)CreatePlanet(*this, camera);
#        endif

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
