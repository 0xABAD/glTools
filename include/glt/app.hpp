#ifndef __APP_HPP__
#define __APP_HPP__

#include <glt/api.hpp>

namespace glt {

/**
 * Initializes the underlying GLFW3 system.  This class should
 * be only constructed once and at the top of main.
 */
class GLT_API App final
{
public:
  App();
  ~App();
  App(const App&)       = delete;
  App(const App&&)      = delete;
  App& operator=(App&)  = delete;
  App& operator=(App&&) = delete;
};

/**
 * Initializes the glTools library.  This should be called after
 * a window has been made the current context. @see Window
 *
 * @returns True if glTools was loaded successfully, false otherwise.
 */
GLT_API bool initGlTools();

} // end namespace glt

#endif // __APP_HPP__
