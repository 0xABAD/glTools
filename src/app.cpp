#include <glt/app.hpp>
#include <glt/gl.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace glt {

App::App()  { glfwInit(); }
App::~App() { glfwTerminate(); }


bool initGlTools()
{
    return gl::sys::LoadFunctions();
}

} // end namespace glt
