#include "Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Constants/InputConstants.hpp>
#include <Window/Input.hpp>
#include <Window/MouseButton.hpp>

#include <Utils/CatchAndRethrowExceptions.hpp>  // CATCH_RETHROW_EXCEPTIONS
#include <Utils/PrintGLErrors.hpp>              // PRINT_GL_ERRORS_IF_ANY

#include <chrono>           // std::chrono::system_clock
#include <iostream>         // std::cerr, std::cout
#include <memory>           // std::unique_ptr, std::make_unique
#include <stdexcept>        // std::logic_error

static MG3TR::Input s_input;

static void GLFWErrorCallback([[maybe_unused]] int error_code, const char *error_description) try
{
    (void)(std::cerr << "GLFW error: " << error_description << std::endl);
}
CATCH_RETHROW_EXCEPTIONS

static void InitGLFW() try
{
    (void)(glfwSetErrorCallback(GLFWErrorCallback));

    int return_value = glfwInit();
    bool GLFW_init_successfully = (return_value == GLFW_TRUE);
    if (!GLFW_init_successfully)
    {
        throw std::logic_error("Could not initialize GLFW.");
    }
}
CATCH_RETHROW_EXCEPTIONS

static void GLFWKeyCallback([[maybe_unused]] GLFWwindow *window, int key,
                            [[maybe_unused]] int scancode, int action,
                            [[maybe_unused]] int mods) try
{
    MG3TR::Key key_code;
    key_code = MG3TR::InputConstants::k_glfw_keys_to_input_keys.at(key);

    // if action is GLFW_RELEASE, the condition will be false and this behaviour is desired.
    bool state = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));
    s_input.UpdateKeyState(key_code, state);
}
CATCH_RETHROW_EXCEPTIONS

static void GLFWMouseButtonCallback([[maybe_unused]] GLFWwindow* window, int button, int action,
                                    [[maybe_unused]] int mods) try
{
    MG3TR::MouseButton button_code;
    button_code = MG3TR::InputConstants::k_glfw_mouse_buttons_to_input_mouse_buttons.at(button);

    // if action is GLFW_RELEASE, the condition will be false and this behaviour is desired.
    bool state = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));
    s_input.UpdateMouseButtonState(button_code, state);
}
CATCH_RETHROW_EXCEPTIONS

static void GLFWScrollCallback([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double xoffset, double yoffset) try
{
    s_input.UpdateScrollOffset(static_cast<float>(yoffset));
}
CATCH_RETHROW_EXCEPTIONS


static void SetGLFWCallbacks(GLFWwindow *window) noexcept
{
    // The documentation says if there return nullptr, they failed to set respective
    // callback, but, as I tested, they always return nullptr, even when they set
    // the callback properly. Will leave as is for now.
    (void)glfwSetKeyCallback(window, GLFWKeyCallback);
    (void)glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);
    (void)glfwSetScrollCallback(window, GLFWScrollCallback);
}

static GLFWwindow* OpenNewWindow(int height, int width, const std::string &name) try
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(height, width, name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::logic_error("Could not create window.");
    }

    glfwMakeContextCurrent(window);

    return window;
}
CATCH_RETHROW_EXCEPTIONS


static void InitGLAD() try
{
    GLenum ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    bool GLAD_init_successfully = (ret != 0);
    if (!GLAD_init_successfully)
    {
        throw std::logic_error(std::string("Could not initialize GLAD."));
    }
}
CATCH_RETHROW_EXCEPTIONS


static void CloseWindow(GLFWwindow *window) noexcept
{
    glfwDestroyWindow(window);
}

static void TerminateGLFW() noexcept
{
    glfwTerminate();
}

namespace MG3TR
{
    Window::Window(int height, int width, const std::string &name) try
    {
        InitGLFW();
        m_window = OpenNewWindow(height, width, name);
        InitGLAD();
        SetGLFWCallbacks(m_window);

        if (glfwRawMouseMotionSupported())
        {
            glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }

        m_scene = std::make_unique<Scene>();
    }
    CATCH_RETHROW_EXCEPTIONS
    
    Window::~Window() noexcept
    {
        CloseWindow(m_window);
        TerminateGLFW();
    }

    void Window::Initialize() try
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);  
        glCullFace(GL_BACK);

        //m_scene->LoadFromFile("res/Scenes/test2.json");
        m_scene->Initialize();
        //std::cout << m_scene->ToString() << '\n';

        m_last_update_time_point = std::chrono::system_clock::now();
    }
    CATCH_RETHROW_EXCEPTIONS

    void Window::KeepRunning() try
    {
        while(!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();
            PRINT_GL_ERRORS_IF_ANY();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            PRINT_GL_ERRORS_IF_ANY();
            
            double xpos, ypos;
            glfwGetCursorPos(m_window, &xpos, &ypos);

            s_input.UpdateMousePosition({ static_cast<float>(xpos), static_cast<float>(ypos) });

            auto current_time_point = std::chrono::system_clock::now();
            auto time_points_difference = current_time_point - m_last_update_time_point;
            float delta_time_seconds = static_cast<std::chrono::duration<float>>(time_points_difference).count();

            m_scene->Update(s_input, delta_time_seconds);

            m_last_update_time_point = current_time_point;

            glfwSwapBuffers(m_window);
            PRINT_GL_ERRORS_IF_ANY();
        }

        //m_scene->SaveToFile("res/Scenes/test2.json");
        //Scene scene("res/Scenes/test1.json");
    }
    CATCH_RETHROW_EXCEPTIONS
}
