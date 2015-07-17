#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <glt/api.hpp>

struct GLFWwindow;
struct GLFWmonitor;

namespace glt {

class GLT_API Window final {
private:
    GLFWwindow *_window;

public:
    Window() : _window(nullptr) {}

    Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
    ~Window();

    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&);
    Window& operator=(Window&&);

    /** Returns true if the window if valid. */
    bool valid() { return _window != nullptr; }

    /** Makes this window have the current OpenGL context. */
    void makeCurrentContext();

    /** Shows this window. */
    void show();

    /** Hides this window. */
    void hide();
};


} // end namespace glt

#endif // __WINDOW_HPP__
