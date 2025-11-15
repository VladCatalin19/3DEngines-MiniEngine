#include <Window/Window.hpp>

#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Graphics/API/OpenGLAPI.hpp>

#include <memory>

int main()
{
    auto opengl_api = std::make_unique<MG3TR::OpenGLAPI>();
    auto& api_instance = MG3TR::GraphicsAPISingleton::GetInstance();

    api_instance.SetGraphicsAPI(std::move(opengl_api));

    MG3TR::Window window(1024, 720, "MG3TR");
    window.Initialize();
    window.KeepRunning();
    
    return 0;
}
