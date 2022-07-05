#include <Window/Window.hpp>

#include <exception>            // std::rethrow_if_nested
#include <iostream>             // std::cerr, std::endl
#include <stdexcept>            // std::exception

static void PrintNestedException(const std::exception &exception, unsigned level = 0U) noexcept
{
    bool is_last_level = false;
    try
    {
        std::rethrow_if_nested(exception);
        is_last_level = true;
    }
    catch (const std::exception &e)
    {
        PrintNestedException(e, level + 1U);
    }
    std::cerr << (is_last_level ? "" : "    ") << exception.what() << std::endl;
}

int main() try
{
    MG3TR::Window window(1024, 720, "MG3TR");
    window.Initialize();
    window.KeepRunning();
    return 0;
}
catch (const std::exception &e)
{
    std::cout << "Program ended with uncaught exception: ";
    PrintNestedException(e);
    return 1;
}
catch (...)
{
    std::cout << "Program ended with unknown thrown type" << std::endl;
    return 1;
}
