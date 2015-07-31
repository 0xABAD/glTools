#include <glt/window.hpp>
#include <glt/gl.hpp>
#include <bandit/bandit.h>

using namespace bandit;

go_bandit([]() {

    describe("OpenGL loading", []() {

        it("can load OpenGL after window is made current context", []() {
            glt::Window window(1, 1, "test", nullptr, nullptr);
            window.makeCurrentContext();
            AssertThat(glt::initGlTools(), Is().EqualTo(true));
        });

        it("does no load OpenGL when there is no valid window context", []() {
            glt::Window window;
            AssertThat(glt::initGlTools(), Is().EqualTo(false));
        });
    });

    describe("#easyWindow", []() {

        it("returns a valid window", []() {
            auto out    = std::stringstream();
            auto window = glt::easyWindow(out);

            AssertThat(window.valid(),    Is().EqualTo(true));
            AssertThat(out.str().empty(), Is().EqualTo(true));
        });

        it("has correct size", []() {
            auto width  = 800;
            auto height = 600;
            auto out    = std::stringstream();
            auto window = glt::easyWindow(width, height, out);
            auto size   = window.getSize();

            AssertThat(std::get<0>(size), Equals(width));
            AssertThat(std::get<1>(size), Equals(height));
        });
    });
});