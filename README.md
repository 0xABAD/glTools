glTools
=======

A library to reduce the boilerplate for writing simple OpenGL 4.5 programs.

Dependencies
------------

* [GLFW](http://www.glfw.org/) for windowing.

* [glm](http://glm.g-truc.net/0.9.5/index.html) for standard graphics math.

* [bandit](http://banditcpp.org/index.html) *optional* if you want to run 
the tests.

* [premake5](https://premake.github.io/) to setup the build environment.

Note that libraries such as [GLEW](http://http://glew.sourceforge.net/) and 
such are not required as the OpenGL 4.5 loading library uses one created from
[GLLoadGen](https://bitbucket.org/alfonse/glloadgen/wiki/Home).  The library
generated specifies the core OpenGL 4.5 profile using the `func_cpp` style
option.  So, OpenGL calls will be like `gl::CreateProgram()`.

Building
--------

Since glTools makes use of C++ standard library in its interfaces the library
is intended to be built as a static library.  These instructions and the premake
files are known to work on Windows.  Building on Linux may need some fine
tuning and Mac OS X is not supported as Apple does not support OpenGL 4.5.
To build:

* Clone this project.

* After obtaining glfw3, glm, and bandit (if you plan to run the tests), place
the include portions of those libraries into the glTools include folder.

* Build the glfw3 library as static library with same compiler that you will
be building glTools with.  Place the built library file into the lib directory
of glTools.

* *Optional* If you do not want to run the tests then comment out the
`glToolsTest` project from the premake5.lua file.

* Run premake5.exe for your chosen compiler toolchain (e.g.
`$ premake5.exe vs2015` for Visual Studio 2015 on Windows).

* Build the project (VS solution) from the generated build directory.

If you wish to run the examples then go to the examples directory, run premake
for your toolchain, then build the projects.  It is recommended to run the
individual examples in their source directory as they use relative paths from
that directory to load any assets, shader source code, etc.

Overview
--------

The library can be broken down into the following core sections:

* glt/glt.hpp - Contains most basic elements for rendering in OpenGL (vertex
buffers, compile shader programs, loading images for textures, etc.).  Image
class uses the [stb_image](https://github.com/nothings/stb) libary.  This
header will typically always be included.

* glt/window.hpp - Windowing using GLFW3.  A wrapper class Window
class is defined to give programs a more modern C++ feel (e.g.
the ability to use lambdas for callbacks).  Including this file
also includes GLFW3/glfw3.h for its defined macro constants.

* glt/geometry.hpp - Functions for creating simple geometry to
get something up and running quickly.  Only planes and boxes are
currently defined.

* glt/text.hpp - Simple text rendering facilities and loading
custom bitmaps with [Codehead's](http://www.codehead.co.uk/cbfg/)
bitmap fong generator.  The Text class provides a basic text
rendering engine.  With it you can use custom fonts or use one of
the two built-in font bitmaps provided with the library.

A Trivial Example
-----------------

A tiny program to illustrate the library's style.  The examples folder
contains several example programs that better illustrate different portions of
the library.  Assume the project directory has the following structure with
debug versions of glTools and glfw3 static libraries:

```
trivial/
 | include/
 	| glt/
 	| glm/
 	| glfw3/
 | lib/
 	| glTools.lib
 	| glfw3.lib
 | main.cpp
```

And uses this premake5.lua file:

```lua
solution "trivial"
    configurations { "Debug" }
    location "build"

project "trivial"
    location    "build/trivial"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "lib" }
    includedirs { "include" }
    files       { "main.cpp" }
    links       { "glTools", "glfw3", "opengl32" }

    filter "system:windows"
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }
```

And then main.cpp:

```c++
#include <glt/glt.hpp>
#include <glt/window.hpp>
#include <glt/text.hpp>

#include <glm/glm.hpp>
#include <sstream>

const char * vertex =
"#version 450                                                   \n"
"const vec4 vertices[3] = vec4[3](vec4(-0.5, -0.5, 0.0, 1.0),   \n"
"                                 vec4( 0.5, -0.5, 0.0, 1.0),   \n"
"                                 vec4( 0.0,  0.5, 0.0, 1.0));  \n"
"                                                               \n"
"const vec4 colors[3]   = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),     \n"
"                                 vec4(0.0, 1.0, 0.0, 1.0),     \n"
"                                 vec4(0.0, 0.0, 1.0, 1.0));    \n"
"out vec4 VertexColor;                                          \n"
"void main() {                                                  \n"
"   VertexColor = colors[gl_VertexID];                          \n"
"   gl_Position = vertices[gl_VertexID];                        \n"
"}                                                              \n";

const char * fragment =
"#version 450                               \n"
"in  vec4 VertexColor;                      \n"
"out vec4 FragColor;                        \n"
"void main() { FragColor = VertexColor; }   \n";

int main(int argc, const char * argv[])
{
    glt::App app;

    auto window    = glt::easyWindow("glTools");
    auto text      = glt::makeConsolas(1, 64);
    auto Identity  = glm::mat4{};
    auto textColor = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
    auto textPos   = glm::vec3{ -0.97f, 0.92f, 0.0f };
    auto vao       = glt::VertexArray(1);
    auto program   = glt::compileProgram(
    					 glt::compileShaderSource(vertex,   gl::VERTEX_SHADER),
                        {glt::compileShaderSource(fragment, gl::FRAGMENT_SHADER)});

    window.onMouseMove([&](double xPos, double yPos) {
        std::stringstream mousePos;
        mousePos << "Mouse Position: " << xPos << ", " << yPos;
        text.load(0, mousePos.str(), textPos, 0.05f);
    });

    gl::ClearColor(0.0f, 0.3f, 0.2f, 1.0f);

    while (!window.shouldClose())
    {
        glt::pollEvents();

        gl::Clear(gl::COLOR_BUFFER_BIT);
        gl::UseProgram(program);
        gl::BindVertexArray(vao[0]);
        gl::DrawArrays(gl::TRIANGLES, 0, 3);
        text.render(Identity, textColor);

        window.swapBuffers();
    }

    return 0;
}
```