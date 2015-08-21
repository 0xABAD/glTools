#include <glt/window.hpp>
#include <glt/app.hpp>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace glt {

void setupCallbacks(GLFWwindow *window)
{
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCharCallback(window, OnTextInput);
    glfwSetCursorEnterCallback(window, OnCursorEnter);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetMouseButtonCallback(window, OnMouseButtonEvent);
    glfwSetScrollCallback(window, OnScroll);
}

Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
    : _window(nullptr)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLT_OPEN_GL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLT_OPEN_GL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title, monitor, share);
    glfwSetWindowUserPointer(_window, (void*) this);
    setupCallbacks(_window);
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
    glfwSetWindowUserPointer(_window, (void*) this);
    setupCallbacks(_window);
}

Window& Window::operator=(Window&& rhs)
{
    destory(_window);
    std::swap(_window, rhs._window);
    glfwSetWindowUserPointer(_window, (void*) this);
    setupCallbacks(_window);

    return *this;
}

inline void Window::makeCurrentContext() 
{ 
    glfwMakeContextCurrent(_window);
}

inline void Window::show() { glfwShowWindow(_window); }
inline void Window::hide() { glfwHideWindow(_window); }
inline bool Window::shouldClose() { return static_cast<bool>(glfwWindowShouldClose(_window)); }
inline void Window::swapBuffers() { glfwSwapBuffers(_window); }

std::tuple<int, int> Window::getFramebufferSize()
{
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    return std::make_tuple(width, height);
}

std::tuple<int, int> Window::getSize()
{
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return std::make_tuple(width, height);
}

inline void Window::setInputMode(int mode, int value)
{
    glfwSetInputMode(_window, mode, value);
}

inline void Window::setCursor(GLFWcursor *cursor)
{
    glfwSetCursor(_window, cursor);
}

void OnKeyEvent(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    auto window = (Window*) glfwGetWindowUserPointer(win);
    window->_onKeyEvent(key, scancode, action, mods);
}

void OnTextInput(GLFWwindow * win, unsigned int codepoint)
{
    auto window = (Window*) glfwGetWindowUserPointer(win);
    window->_onTextInput(codepoint);
}

void OnCursorEnter(GLFWwindow *win, int entered)
{
    auto window = (Window*) glfwGetWindowUserPointer(win);
    window->_onCursorEnter(entered);
}

void OnMouseMove(GLFWwindow *win, double xpos, double ypos)
{
    auto window = (Window*) glfwGetWindowUserPointer(win);
    window->_onMouseMove(xpos, ypos);
}

void OnMouseButtonEvent(GLFWwindow * win, int button, int action, int mods)
{
    auto window = (Window*) glfwGetWindowUserPointer(win);
    window->_onMouseButtonEvent(button, action, mods);
}

void OnScroll(GLFWwindow *win, double xoffset, double yoffset)
{
    auto window = (Window*) glfwGetWindowUserPointer(win);
    window->_onScroll(xoffset, yoffset);
}

inline void pollEvents() { glfwPollEvents(); }

const int   WIDTH  = 1024;
const int   HEIGHT = 768;
const char *TITLE  = "OpenGL Window";

Window easyWindow(int width, int height, const char *title, std::ostream &out)
{
    Window window(width, height, title, nullptr, nullptr);

    if (window.valid() == false)
    {
        out << "Could not create window.\n" 
            << "Has an App been created?" << std::endl;
        exit(EXIT_FAILURE);
    }

    window.makeCurrentContext();

    if (initGlTools() == false)
    {
        out << "Failed to load OpenGL." << std::endl;
        exit(EXIT_FAILURE);
    }

    return window;
}

inline Window easyWindow(int width, int height, const char *title)
{
    return easyWindow(width, height, title, std::cerr);
}

inline Window easyWindow(int width, int height, std::ostream &out)
{
    return easyWindow(width, height, TITLE, out);
}

inline Window easyWindow(int width, int height)
{
    return easyWindow(width, height, TITLE, std::cerr);
}

inline Window easyWindow(const char *title, std::ostream &out)
{
    return easyWindow(WIDTH, HEIGHT, title, out);
}

inline Window easyWindow(const char *title)
{
    return easyWindow(WIDTH, HEIGHT, title, std::cerr);
}

inline Window easyWindow(std::ostream &out)
{
    return easyWindow(WIDTH, HEIGHT, TITLE, out);
}

inline Window easyWindow()
{
    return easyWindow(WIDTH, HEIGHT, TITLE, std::cerr);
}

} // end namespace glt
