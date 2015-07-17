#include <glt/glt.hpp>
#include <bandit/bandit.h>

using namespace bandit;

go_bandit([]() {

    describe("OpenGL loading", []() {
        glt::Window window;
        window.makeCurrentContext();

        it("can load OpenGL after window is made current context", []() {
            glt::initGlTools();
        });
    });
});