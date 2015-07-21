#include <glt/glt.hpp>
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
            glt::Window window();
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
    });
});