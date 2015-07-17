#include <glt/app.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace glt {

App::App()  { glfwInit(); }
App::~App() { glfwTerminate(); }


bool GLT_API initGlTools()
{
    return gl::sys::LoadFunctions();
}

} // end namespace glt
