#include "Window.hpp"

#include "Input.hpp"
#include "MouseButton.hpp"

#include <GLFW/glfw3.h>

#include <Constants/InputConstants.hpp>
#include <Graphics/API/GraphicsAPISingleton.hpp>
#include <Scene/Scene.hpp>
#include <Utils/ExceptionWithStacktrace.hpp>

#include <iostream>

static MG3TR::Input s_input;

static void GLFWErrorCallback([[maybe_unused]] const int error_code, const char * const error_description)
{
    (void)(std::cerr << "GLFW error: " << error_description << std::endl);
}

static void InitGLFW()
{
    (void)(glfwSetErrorCallback(GLFWErrorCallback));

    const int return_value = glfwInit();
    const bool GLFW_init_successfully = (return_value == GLFW_TRUE);
    if (!GLFW_init_successfully)
    {
        throw MG3TR::ExceptionWithStacktrace("Could not initialize GLFW.");
    }
}

static void GLFWKeyCallback([[maybe_unused]] GLFWwindow* const window, const int key,
                            [[maybe_unused]] const int scancode, const int action,
                            [[maybe_unused]] const int mods)
{
    const MG3TR::Key key_code = MG3TR::InputConstants::k_glfw_keys_to_input_keys.at(key);

    // if action is GLFW_RELEASE, the condition will be false and this behaviour is desired.
    const bool state = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));
    s_input.UpdateKeyState(key_code, state);
}

static void GLFWMouseButtonCallback([[maybe_unused]] GLFWwindow* const window, const int button, const int action,
                                    [[maybe_unused]] const int mods)
{
    const MG3TR::MouseButton button_code = MG3TR::InputConstants::k_glfw_mouse_buttons_to_input_mouse_buttons.at(button);

    // if action is GLFW_RELEASE, the condition will be false and this behaviour is desired.
    const bool state = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));
    s_input.UpdateMouseButtonState(button_code, state);
}

static void GLFWScrollCallback([[maybe_unused]] GLFWwindow* const window, [[maybe_unused]] const double xoffset, double const yoffset)
{
    s_input.UpdateScrollOffset(static_cast<float>(yoffset));
}

static void SetGLFWCallbacks(GLFWwindow *const window)
{
    // The documentation says if the functions return nullptr, they failed to set respective
    // callback, but, as I tested, they always return nullptr, even when they set
    // the callback properly. Will leave as is for now.
    (void)glfwSetKeyCallback(window, GLFWKeyCallback);
    (void)glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);
    (void)glfwSetScrollCallback(window, GLFWScrollCallback);
}

static GLFWwindow* OpenNewWindow(const int height, const int width, const std::string &name)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* const window = glfwCreateWindow(height, width, name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        throw MG3TR::ExceptionWithStacktrace("Could not create window.");
    }

    glfwMakeContextCurrent(window);

    return window;
}

static void CloseWindow(GLFWwindow *window)
{
    glfwDestroyWindow(window);
}

static void TerminateGLFW()
{
    glfwTerminate();
}



namespace MG3TR
{
    Window::Window(const int height, const int width, const std::string &name)
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();
        
        InitGLFW();
        m_window = OpenNewWindow(height, width, name);
        SetGLFWCallbacks(m_window);

        api.Initialise(reinterpret_cast<void *>(glfwGetProcAddress));

        if (glfwRawMouseMotionSupported())
        {
            glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }

        m_scene = std::make_unique<Scene>();
    }
    
    Window::~Window()
    {
        CloseWindow(m_window);
        TerminateGLFW();
    }

    void Window::Initialize()
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        api.SetDepthTest(true);
        api.SetBackFaceCulling(true);

        //m_scene->LoadFromFile("res/Scenes/test2.json");
        m_scene->Initialize();
        //std::cout << m_scene->ToString() << '\n';

        m_last_update_time_point = std::chrono::system_clock::now();
    }

    void Window::KeepRunning()
    {
        auto& api = GraphicsAPISingleton::GetInstance().GetGraphicsAPI();

        while (!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();

            api.ClearScreen();
            
            double xpos, ypos;
            glfwGetCursorPos(m_window, &xpos, &ypos);

            s_input.UpdateMousePosition({ static_cast<float>(xpos), static_cast<float>(ypos) });

            const auto current_time_point = std::chrono::system_clock::now();
            const auto time_points_difference = current_time_point - m_last_update_time_point;
            const float delta_time_seconds = static_cast<std::chrono::duration<float>>(time_points_difference).count();

            m_scene->Update(s_input, delta_time_seconds);

            m_last_update_time_point = current_time_point;

            glfwSwapBuffers(m_window);
        }

        //m_scene->SaveToFile("res/Scenes/test2.json");
        //Scene scene("res/Scenes/test1.json");
    }
}
