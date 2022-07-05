#ifndef MG3TR_SRC_WINDOW_WINDOW_HPP_INCLUDED
#define MG3TR_SRC_WINDOW_WINDOW_HPP_INCLUDED

#include <Scene/Scene.hpp>
#include <Window/Input.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>         // GLFWwindow

#include <chrono>               // std::chrono::system_clock::time_point
#include <memory>               // std::unique_ptr
#include <string>               // std::string

namespace MG3TR
{
    class Window
    {
    private:
        GLFWwindow *m_window;
        std::chrono::system_clock::time_point m_last_update_time_point;

        std::unique_ptr<Scene> m_scene;

    public:
        Window(int height, int width, const std::string &name);
        virtual ~Window() noexcept;

        Window(const Window &) = delete;
        Window& operator=(const Window &) = delete;

        Window(Window &&) = default;
        Window& operator=(Window &&) = default;

        void Initialize();
        void KeepRunning();
    };
}

#endif // MG3TR_SRC_WINDOW_WINDOW_HPP_INCLUDED
