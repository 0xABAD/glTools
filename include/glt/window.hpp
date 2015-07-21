#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <glt/api.hpp>
#include <ostream>

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

/**
 * Creates a window with optional defaults, makes the window the
 * current contex, and initializes OpenGL.
 *
 * All parameters are optional.
 * 
 * @param width   Window's width (default 1024).
 * @param height  Window's height (default 768).
 * @param title   Window's title (default "OpenGL Window").
 * @param out     Out stream for any errors that occur (default std::cerr).
 *
 * @returns  A new window that is the current OpenGL context.  If the
 *           window could be created for any reason or OpenGL can not
 *           be loaded then the program will be prematurely exited.
 */
Window GLT_API easyWindow(int width, int height, const char *title, std::ostream &out);
Window GLT_API easyWindow(int width, int height, const char *title);
Window GLT_API easyWindow(int width, int height, std::ostream &out);
Window GLT_API easyWindow(int width, int height);
Window GLT_API easyWindow(const char *title, std::ostream &out);
Window GLT_API easyWindow(const char *title);
Window GLT_API easyWindow(std::ostream &out);
Window GLT_API easyWindow();

} // end namespace glt

#endif // __WINDOW_HPP__
