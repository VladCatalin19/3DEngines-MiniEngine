#include <Constants/GraphicsConstants.hpp>
#include <Components/Camera.hpp>
#include <Components/CameraController.hpp>
#include <Components/MeshRenderer.hpp>
#include <Components/SkyboxFollowCamera.hpp>
#include <Components/TestRotation.hpp>
#include <Components/TestMovement.hpp>

#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/API/OpenGLAPI.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Shaders/FragmentNormalShader.hpp>
#include <Graphics/Shaders/TextureAndLightingShader.hpp>
#include <Graphics/Shaders/TextureShader.hpp>

#include <Math/Math.hxx>
#include <Math/Quaternion.hpp>
#include <Math/Vector3.hpp>

#include <Scene/Scene.hpp>
#include <Scripting/GameObject.hpp>
#include <Scripting/Transform.hpp>

#include <Window/Window.hpp>

#include <memory>

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

int main()
{
    auto opengl_api = std::make_unique<MG3TR::OpenGLAPI>();
    auto& api_instance = MG3TR::GraphicsAPISingleton::GetInstance();

    api_instance.SetGraphicsAPI(std::move(opengl_api));

    MG3TR::Window window(1024, 720, "MG3TR");

    auto scene = std::make_unique<MG3TR::Scene>();
    auto& scene_ref = *scene;

    auto camera = CreateCameraAndAddItToScene(scene_ref);
    auto rotating_cube_game_object = CreateRotatingCubeAndAddItToScene(scene_ref, camera);
    (void)CreateSecondRotatingCubeAndAddItAsChildToTheFirstCube(camera, rotating_cube_game_object);
    (void)CreateCreeper(scene_ref, camera);
    (void)CreateMap(scene_ref, camera);
    (void)CreateSkyBox(scene_ref, camera);
    (void)CreatePlanet(scene_ref, camera);
    //m_scene->LoadFromFile("res/Scenes/test2.json");

    //m_scene->SaveToFile("res/Scenes/test2.json");
    //Scene scene("res/Scenes/test1.json");

    window.SetScene(std::move(scene));

    window.Initialize();
    window.KeepRunning();
    
    return 0;
}
