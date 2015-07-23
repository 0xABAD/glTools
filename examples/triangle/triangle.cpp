#include <glt/glt.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    glt::App app;
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    auto window    = glt::easyWindow("Triangle", std::cerr);
    auto program   = glt::compileProgram(std::cerr, { "simple.vert", "simple.frag" });
    auto vbo       = glt::VertexBuffer(1);
    auto vao       = glt::VertexArray(1);
    auto frameSize = window.getFramebufferSize();

    gl::BindVertexArray(vao[0]);
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertices), vertices, gl::STATIC_DRAW);
    gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 3 * sizeof(GLfloat), (GLvoid*)0);
    gl::EnableVertexAttribArray(0);
    gl::BindVertexArray(0);

    gl::Viewport(0, 0, std::get<0>(frameSize), std::get<1>(frameSize));
    gl::ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose())
    {
        glt::pollEvents();

        gl::Clear(gl::COLOR_BUFFER_BIT);
        gl::UseProgram(program);
        gl::BindVertexArray(vao[0]);
        gl::DrawArrays(gl::TRIANGLES, 0, 3);
        gl::BindVertexArray(0);

        window.swapBuffers();
    }

    return 0;
}
