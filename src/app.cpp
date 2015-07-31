#include <glt/app.hpp>
#include <GLFW/glfw3.h>

namespace glt {

App::App()  { glfwInit(); }
App::~App() { glfwTerminate(); }

} // end namespace glt
