#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <glt/api.hpp>
#include <glt/app.hpp>
#include <glt/gl.hpp>
#include <GLFW/glfw3.h>

#include <ostream>
#include <tuple>
#include <functional>

namespace glt {

class GLT_API Window final {
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

    /**
     * Set the input mode for the window (e.g. disabling the cursor).
     * 
     * See http://www.glfw.org/docs/latest/input.html#cursor_mode
     */
    void setInputMode(int mode, int value);

    /** Sets the cursor for the window.  */
    void setCursor(GLFWcursor *cursor);

    /**
     * Called when a key event is recognized.  The callback is passed
     * the key, the scancode, the action (pressed or released), and
     * the modifier keys pressed.
     *
     * See http://www.glfw.org/docs/latest/input.html#input_keyboard
     */
    void onKeyEvent(std::function<void(int, int, int, int)> callback) 
    { 
        _onKeyEvent = callback;
    }

    /**
     * Called when text input is received.  The callback is passed
     * the UTF-32 codepoint (native endian).
     */
    void onTextInput(std::function<void(unsigned int)> callback)
    {
        _onTextInput = callback;
    }

    /**
     * Called whenever the mouse cursor enters or exits the window.
     * A non zero value is passed to the callback when the mouse
     * cursor enters the window and zero for when it exits.
     */
    void onCursorEnter(std::function<void(int)> callback)
    {
        _onCursorEnter = callback;
    }

    /**
     * Called whenever the mouse moves within the window.  The
     * (x, y) position, where (0, 0) is the top left corner,
     * is passed to the callback function.
     */
    void onMouseMove(std::function<void(double, double)> callback)
    {
        _onMouseMove = callback;
    }

    /**
     * Called whenever a mouse button is pressed or released.  The
     * first parameter of the callback is the mouse button, the
     * second is the action, which is either GLFW_PRESS or
     * GLFW_RELEASE, and the third parameter is the modifier
     * that is pressed in during the event.
     *
     * See http://www.glfw.org/docs/latest/input.html#events
     * See http://www.glfw.org/docs/latest/group__buttons.html
     * See http://www.glfw.org/docs/latest/group__mods.html
     */
    void onMouseButtonEvent(std::function<void(int, int, int)> callback)
    {
        _onMouseButtonEvent = callback;
    }

    /**
     * Called when a scroll event occurs from either a mouse
     * wheel or touchpad gesture.  The x and y offsets are
     * passed to the callback function.
     */
    void onScroll(std::function<void(double, double)> callback)
    {
        _onScroll = callback;
    }

    friend void OnKeyEvent(GLFWwindow *, int, int, int, int);
    friend void OnTextInput(GLFWwindow *, unsigned int);
    friend void OnCursorEnter(GLFWwindow *, int);
    friend void OnMouseMove(GLFWwindow *, double, double);
    friend void OnMouseButtonEvent(GLFWwindow *, int, int, int);
    friend void OnScroll(GLFWwindow *, double, double);

private:
    GLFWwindow * _window;
    std::function<void(int, int, int, int)> _onKeyEvent;
    std::function<void(unsigned int)>       _onTextInput;
    std::function<void(double, double)>     _onMouseMove;
    std::function<void(int)>                _onCursorEnter;
    std::function<void(int, int, int)>      _onMouseButtonEvent;
    std::function<void(double, double)>     _onScroll;
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
