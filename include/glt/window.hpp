#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <glt/api.hpp>
#include <ostream>
#include <tuple>

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

    /**
     * Returns true when the window received an event notifying
     * that it should be destroyed (e.g. Alt + F4).
     */
    bool shouldClose();

    /** Swaps the windows front and back buffer. */
    void swapBuffers();

    /**
     * Returns the size of the window's frame buffer.
     *
     * This is the size, in pixels, of the window's frame buffer and
     * typically the dimensions you want when calling glViewport.
     *
     * @returns  A tuple where the first element is the frame buffer's
     *           width and the second is its height.
     */
    std::tuple<int, int> getFramebufferSize();

    /**
     * Returns the size of this window.
     *
     * Note that when working with OpenGL, such as calling glViewPort,
     * then size of the window in pixels is what you want.
     * @see getFrameBufferSize()
     *
     * @returns  A tuple where the first element is the window's
     *           width and the second is its height.
     */
    std::tuple<int, int> getSize();
};

/** Processes events in the event queue. */
GLT_API void pollEvents();

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
GLT_API Window easyWindow(int width, int height, const char *title, std::ostream &out);
GLT_API Window easyWindow(int width, int height, const char *title);
GLT_API Window easyWindow(int width, int height, std::ostream &out);
GLT_API Window easyWindow(int width, int height);
GLT_API Window easyWindow(const char *title, std::ostream &out);
GLT_API Window easyWindow(const char *title);
GLT_API Window easyWindow(std::ostream &out);
GLT_API Window easyWindow();

} // end namespace glt

#endif // __WINDOW_HPP__
