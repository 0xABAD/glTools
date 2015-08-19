#include <glt/glt.hpp>
#include <glt/window.hpp>
#include <glt/geometry.hpp>
#include <glt/text.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <cstdint>

using glm::vec3;    using glm::vec4;
using glm::mat3;    using glm::mat4;

mat4 rotate(float theta, float phi)
{
    auto rotateX = glm::rotate(mat4{}, glm::radians(theta), vec3{ 1,0,0 });
    return glm::rotate(rotateX, glm::radians(phi), vec3{ 0,1,0 });
}

int main(int argc, char * argv[])
{
    glt::App app;

    auto window     = glt::easyWindow("textfont");
    auto custom     = glt::Text(glt::BitmapFont("test_font-512.bff"), 2, 64);
    auto consolas   = glt::makeConsolas(7, 32);
    auto segoe      = glt::makeSegoeUI(1, 64, glt::compileShader("custom.frag"));
    auto backColor  = gl::GetUniformLocation(segoe.programId(), "BackgroundTextColor");
    auto cubeProg   = glt::compileProgram({"textfont.vert", "textfont.frag"});
    auto cubeVao    = glt::VertexArray(1);
    auto cubeVbo    = glt::VertexBuffer(2);
    auto cubeTbo    = glt::TextureBuffer(1);
    auto mvpLoc     = gl::GetUniformLocation(cubeProg, "MVP");
    auto cube       = glt::makeBox(1, 1, 1);
    auto width      = std::get<0>(window.getFramebufferSize());
    auto height     = std::get<1>(window.getFramebufferSize());
    auto aspect     = (float) width / height;
    auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 10.0f);
    auto view       = glm::lookAt(vec3{ 0,0,5 }, vec3{ 0,0,0 }, vec3{ 0,1,0 });
    auto theta      = 0.0f;
    auto phi        = 0.0f;
    auto Identity   = mat4();
    auto boxTextPos = vec3{ -0.35f, -0.1f, +0.51f };
    auto boxTextSz  = 0.3f;

    custom  .load(0, "Custom font from Codehead's generator",    vec3{ -0.95f, -0.8f,  0.0f }, 0.04f);
    custom  .load(1, "Same custom font but bigger",              vec3{ -0.9f,  -0.95f, 0.0f }, 0.06f);
    segoe   .load(0, "SegoeUI built-in font with custom shader", vec3{ -0.95f, +0.8f,  0.0f }, 0.10f);
    consolas.load(0, "Consolas built-in font",                   vec3{ -0.95f, +0.9f,  0.0f }, 0.06f);
    consolas.load(1, "Front",  boxTextPos, Identity,       boxTextSz);
    consolas.load(2, "Right",  boxTextPos, rotate(0, 90),  boxTextSz);
    consolas.load(3, "Back",   boxTextPos, rotate(0, 180), boxTextSz);
    consolas.load(4, "Left",   boxTextPos, rotate(0, -90), boxTextSz);
    consolas.load(5, "Top",    boxTextPos, rotate(-90, 0), boxTextSz);
    consolas.load(6, "Bottom", boxTextPos, rotate(90, 0),  boxTextSz);

    gl::BindVertexArray(cubeVao[0]);
    glt::loadGeometry(cube, cubeVbo[0], cubeVbo[1]);
    glt::setupAttributes(cube);
    glt::loadTexture2D("../media/container.jpg", false, cubeTbo[0], gl::RGB8, gl::RGB);

    gl::ClearColor(0.4f, 0.7f, 0.6f, 1.0f);
    gl::Enable(gl::DEPTH_TEST);

    while (!window.shouldClose())
    {
        auto MVP = projection * view * rotate(theta, phi);

        glt::pollEvents();
        gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

        custom.render(Identity, vec4{ 0.1f, 0.3f, 0.7f, 1.0f });
        consolas.render(0, Identity, vec4{ 0.5f, 0.1f, 0.3f, 1.0f });
        consolas.render(1, 7, MVP, vec4{ 1, 1, 1, 1 });

        // Load in the uniform for the custom fragment shader.
        gl::UseProgram(segoe.programId());
        gl::Uniform4fv(backColor, 1, glm::value_ptr(vec4 { 0.0f, 0.0f, 0.0f, 1.0f }));
        segoe.render(Identity, vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

        gl::UseProgram(cubeProg);
        gl::UniformMatrix4fv(mvpLoc, 1, gl::FALSE_, glm::value_ptr(MVP));

        gl::ActiveTexture(gl::TEXTURE0);
        gl::BindTexture(gl::TEXTURE_2D, cubeTbo[0]);

        gl::BindVertexArray(cubeVao[0]);
        gl::DrawElements(gl::TRIANGLES, cube.indices.size(), gl::UNSIGNED_INT, nullptr);

        window.swapBuffers();

        theta += 0.2f;
        phi   -= 0.1f;
    }

    return 0;
}
