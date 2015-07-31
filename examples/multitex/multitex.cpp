#include <glt/glt.hpp>
#include <glt/window.hpp>
#include <glt/geometry.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <array>

void makeView(GLuint tex, GLuint origianl, GLint param, GLenum internalformat)
{
    gl::TextureView(tex, gl::TEXTURE_2D, origianl, internalformat, 0, 1, 0, 1);
    gl::BindTexture(gl::TEXTURE_2D, tex);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, param);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, param);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
}

int main(int argc, char *argv[])
{
    glt::App app;

    auto window    = glt::easyWindow("Multitex", std::cerr);
    auto program   = glt::compileProgram(std::cerr, { "multitex.vert", "multitex.frag" });
    auto vao       = glt::VertexArray(1);
    auto vbo       = glt::VertexBuffer(2);
    auto texbuf    = glt::TextureBuffer(8);
    auto transLoc  = gl::GetUniformLocation(program, "Translation");
    auto scaleLoc  = gl::GetUniformLocation(program, "TexScale");
    auto topLeft   = glm::translate(glm::mat4{}, glm::vec3{-0.5f, +0.5f, 0});
    auto botLeft   = glm::translate(glm::mat4{}, glm::vec3{-0.5f, -0.5f, 0});
    auto topRight  = glm::translate(glm::mat4{}, glm::vec3{+0.5f, +0.5f, 0});
    auto botRight  = glm::translate(glm::mat4{}, glm::vec3{+0.5f, -0.5f, 0});
    auto matrices  = std::array<glm::mat4 *, 4> { &topLeft, &topRight, &botLeft, &botRight };
    auto plane     = glt::makePlane(0.5, 0.5);

    gl::BindVertexArray(vao[0]);
    glt::loadGeometry(plane, vbo[0], vbo[1]);
    glt::setupAttributes(plane);
    gl::BindVertexArray(0);

    glt::loadTexture2D("../media/container.jpg", false, texbuf[0], gl::RGB8, gl::RGB);
    makeView(texbuf[1], texbuf[0], gl::REPEAT,        gl::RGB8);
    makeView(texbuf[2], texbuf[0], gl::REPEAT,        gl::RGB8);
    makeView(texbuf[3], texbuf[0], gl::CLAMP_TO_EDGE, gl::RGB8);

    glt::loadTexture2D("../media/awesomeface.png", true, texbuf[4], gl::RGBA8, gl::RGBA);
    makeView(texbuf[5], texbuf[4], gl::REPEAT,          gl::RGBA8);
    makeView(texbuf[6], texbuf[4], gl::MIRRORED_REPEAT, gl::RGBA8);
    makeView(texbuf[7], texbuf[4], gl::REPEAT,          gl::RGBA8);

    gl::BindTexture(gl::TEXTURE_2D, 0);
    gl::ClearColor(0.1f, 0.4f, 0.3f, 1.0f);

    while (!window.shouldClose())
    {
        glt::pollEvents();

        gl::Clear(gl::COLOR_BUFFER_BIT);
        gl::UseProgram(program);
        gl::BindVertexArray(vao[0]);

        for (size_t i = 0; i < matrices.size(); ++i) 
        {
            gl::ActiveTexture(gl::TEXTURE0);
            gl::BindTexture(gl::TEXTURE_2D, texbuf[i]);

            gl::ActiveTexture(gl::TEXTURE1);
            gl::BindTexture(gl::TEXTURE_2D, texbuf[i + 4]);

            gl::Uniform1f(scaleLoc, i == 0 ? 1.0f : 2.0f);
            gl::UniformMatrix4fv(transLoc, 1, gl::FALSE_, glm::value_ptr(*matrices[i]));
            gl::DrawElements(gl::TRIANGLES, plane.indices.size(), gl::UNSIGNED_INT, nullptr);
        }

        gl::BindVertexArray(0);
        window.swapBuffers();
    }

    return 0;
}