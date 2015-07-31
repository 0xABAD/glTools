#include <glt/glt.hpp>
#include <glt/window.hpp>
#include <glt/geometry.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using glm::vec3;
using glm::mat4;

int main(int argc, char * argv[])
{
    glt::App app;

    auto window     = glt::easyWindow("spincube", std::cerr);
    auto width      = std::get<0>(window.getFramebufferSize());
    auto height     = std::get<1>(window.getFramebufferSize());
    auto vao        = glt::VertexArray(1);
    auto vbo        = glt::VertexBuffer(2);
    auto tbo        = glt::TextureBuffer(2);
    auto program    = glt::compileProgram(std::cerr, { "spincube.vert", "spincube.frag" });
    auto mvpLoc     = gl::GetUniformLocation(program, "MVP");
    auto cube       = glt::makeBox(1, 1, 1);
    auto theta      = 0.0f;
    auto phi        = 0.0f;
    auto aspect     = (float) width / height;
    auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 10.0f);
    auto view       = glm::lookAt(vec3{ 0,0,5 }, vec3{ 0,0,0 }, vec3{ 0,1,0 });

    gl::BindVertexArray(vao[0]);
    glt::loadGeometry(cube, vbo[0], vbo[1]);
    glt::setupAttributes(cube);

    glt::loadTexture2D("../media/container.jpg",   false, tbo[0], gl::RGB8,  gl::RGB);
    glt::loadTexture2D("../media/awesomeface.png", true,  tbo[1], gl::RGBA8, gl::RGBA);

    gl::Viewport(0, 0, width, height);
    gl::ClearColor(0.1f, 0.4f, 0.3f, 1.0f);
    gl::Enable(gl::DEPTH_TEST);

    while (!window.shouldClose())
    {
        glt::pollEvents();

        auto rotateX = glm::rotate(mat4{},  glm::radians(theta), vec3{ 1,0,0 });
        auto rotateY = glm::rotate(rotateX, glm::radians(phi),   vec3{ 0,1,0 });
        auto MVP     = projection * view * rotateY;

        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
        gl::UseProgram(program);

        gl::UniformMatrix4fv(mvpLoc, 1, gl::FALSE_, glm::value_ptr(MVP));

        gl::ActiveTexture(gl::TEXTURE0);
        gl::BindTexture(gl::TEXTURE_2D, tbo[0]);
        gl::ActiveTexture(gl::TEXTURE1);
        gl::BindTexture(gl::TEXTURE_2D, tbo[1]);

        gl::BindVertexArray(vao[0]);
        gl::DrawElements(gl::TRIANGLES, cube.indices.size(), gl::UNSIGNED_INT, nullptr);

        window.swapBuffers();
        theta += 0.2f;
        phi   += 0.1f;
    }

    return 0;
}