#include <glt/window.hpp>
#include <GLFW/glfw3.h>
#include <algorithm>

namespace glt {


Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
    : _window(nullptr)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title, monitor, share);
}

inline void destory(GLFWwindow *window)
{
    if (window != nullptr)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

Window::~Window() { destory(_window); }

Window::Window(Window&& rhs) : Window()
{
    std::swap(_window, rhs._window);
}

Window& Window::operator=(Window&& rhs)
{
    destory(_window);
    std::swap(_window, rhs._window);
    return *this;
}

inline void Window::makeCurrentContext() 
{ 
    glfwMakeContextCurrent(_window);
}

inline void Window::show() { glfwShowWindow(_window); }
inline void Window::hide() { glfwHideWindow(_window); }

} // end namespace glt
