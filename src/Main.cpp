#include <Window/Window.hpp>

int main()
{
    MG3TR::Window window(1024, 720, "MG3TR");
    window.Initialize();
    window.KeepRunning();
    return 0;
}
