#ifndef __APP_HPP__
#define __APP_HPP__

namespace glt {

/**
 * Initializes the underlying GLFW3 system.  This class should
 * be only constructed once and at the top of main.
 */
class App final
{
public:
  App();
  ~App();
  App(const App&)       = delete;
  App(const App&&)      = delete;
  App& operator=(App&)  = delete;
  App& operator=(App&&) = delete;
};

} // end namespace glt

#endif // __APP_HPP__
