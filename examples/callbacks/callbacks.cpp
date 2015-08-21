#include <glt/glt.hpp>
#include <glt/window.hpp>
#include <glt/text.hpp>

#include <glm/glm.hpp>

#include <sstream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

int main(int argc, const char * argv[])
{
    glt::App app;

    const auto Identity = mat4{};
    const auto xLeft    = -0.97f;
    const auto yTop     = +0.92f;
    const auto textSz   = 0.05f;

    auto window    = glt::easyWindow("callbacks");
    auto consolas  = glt::makeConsolas(6, 256);
    auto textInput = std::string();

    consolas.load(0, "Mouse outside of window", vec3{ xLeft, yTop, 0 }, textSz);
    window.onCursorEnter([&](int entered) {
        if (entered)
            consolas.load(0, "Mouse entered window", vec3{ xLeft, yTop, 0 }, textSz);
        else
            consolas.load(0, "Mouse exited window", vec3{ xLeft, yTop, 0 }, textSz);
    });

    consolas.load(1, "Mouse Position:", vec3{ xLeft, yTop - 0.05f, 0 }, textSz);
    window.onMouseMove([&](double xPos, double yPos) {
        std::stringstream mousePos;
        mousePos << "Mouse Position: " << xPos << ", " << yPos;
        consolas.load(1, mousePos.str(), vec3{ xLeft, yTop - 0.05f, 0 }, textSz);
    });

    consolas.load(2, "No mouse button pressed", vec3{ xLeft, yTop - 0.1f, 0 }, textSz);
    window.onMouseButtonEvent([&](int button, int action, int mods) {
        const auto down = 0.1f;

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            consolas.load(2, "Left mouse button pressed", vec3{ xLeft, yTop - down, 0 }, textSz);
        else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            consolas.load(2, "Right mouse button pressed", vec3{ xLeft, yTop - down, 0 }, textSz);
        else
            consolas.load(2, "No mouse button pressed", vec3{ xLeft, yTop - down, 0 }, textSz);
    });

    consolas.load(3, "Scroll Offset:", vec3{ xLeft, yTop - 0.15f, 0 }, textSz);
    window.onScroll([&](double xOffset, double yOffset) {
        std::stringstream scroll;
        scroll << "Scroll Offset: " << xOffset << ", " << yOffset;
        consolas.load(3, scroll.str(), vec3{ xLeft, yTop - 0.15f, 0 }, textSz);
    });

    consolas.load(4, "Key Event: ", vec3{ xLeft, yTop - 0.2f, 0 }, textSz);
    window.onKeyEvent([&](int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS && key == GLFW_KEY_BACKSPACE && textInput.size() > 0)
        {
            textInput.pop_back();
            consolas.load(5, "Text Input: " + textInput, vec3{ xLeft, yTop - 0.25f, 0 }, textSz);
        }

        if (action == GLFW_PRESS)
            consolas.load(4, "Key Event: key pressed", vec3{ xLeft, yTop - 0.2f, 0 }, textSz);
        else if (action == GLFW_RELEASE)
            consolas.load(4, "Key Event: key released", vec3{ xLeft, yTop - 0.2f, 0 }, textSz);
    });

    consolas.load(5, "Text Input: ", vec3{ xLeft, yTop - 0.25f, 0 }, textSz);
    window.onTextInput([&](unsigned int codepoint) {
        textInput.push_back((char) codepoint);  // No unicode handling... so naughty.
        consolas.load(5, "Text Input: " + textInput, vec3{ xLeft, yTop - 0.25f, 0 }, textSz);
    });

    gl::ClearColor(0.1f, 0.4f, 0.2f, 1.0f);

    while (!window.shouldClose())
    {
        glt::pollEvents();

        gl::Clear(gl::COLOR_BUFFER_BIT);
        consolas.render(Identity, vec4{1.0f});

        window.swapBuffers();
    }

    return 0;
}