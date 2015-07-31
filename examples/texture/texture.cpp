#include <glt/glt.hpp>
#include <glt/window.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    glt::App app;

    auto window  = glt::easyWindow("Texture", std::cerr);
    auto vbo     = glt::VertexBuffer(2);
    auto vao     = glt::VertexArray(1);
    auto tex     = glt::TextureBuffer(1);
    auto image   = glt::Image("../media/container.jpg");
    auto program = glt::compileProgram({ "tex.vert", "tex.frag" });

    GLfloat vertices[] = {
        // vertices    // tex coords
        -0.5, -0.5,    +0.0, +0.0,
        +0.5, -0.5,    +1.0, +0.0,
        +0.5, +0.5,    +1.0, +1.0,
        -0.5, +0.5,    +0.0, +1.0,
    };
    GLuint indices[] = { 0, 1, 2, 0, 2, 3 };

    gl::BindVertexArray(vao[0]);
    gl::BindBuffer(gl::ARRAY_BUFFER,         vbo[0]);
    gl::BufferData(gl::ARRAY_BUFFER,         sizeof(vertices), vertices, gl::STATIC_DRAW);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo[1]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, gl::STATIC_DRAW);
    gl::VertexAttribPointer(0, 2, gl::FLOAT, false, 4 * sizeof(GLfloat), nullptr);
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(1, 2, gl::FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    gl::EnableVertexAttribArray(1);
    gl::BindVertexArray(0);

    gl::BindTexture(gl::TEXTURE_2D, tex[0]);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_R, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
    gl::TextureStorage2D(tex[0], 1, gl::RGB8, image.width(), image.height());
    gl::TextureSubImage2D(tex[0], 0, 0, 0, image.width(), image.height(), gl::RGB, gl::UNSIGNED_BYTE, image.data());
    gl::BindTexture(gl::TEXTURE_2D, 0);

    gl::ClearColor(0.1, 0.4, 0.2, 1.0);

    while (!window.shouldClose())
    {
        glt::pollEvents();

        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        gl::UseProgram(program);

        gl::ActiveTexture(gl::TEXTURE0);
        gl::BindTexture(gl::TEXTURE_2D, tex[0]);

        gl::BindVertexArray(vao[0]);
        gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, nullptr);
        gl::BindVertexArray(0);

        window.swapBuffers();
    }

    return 0;
}
