#include <glt/bufferObject.hpp>
#include <glt/window.hpp>
#include <bandit/bandit.h>

using namespace bandit;

go_bandit([]() {
    auto ctx = glt::easyWindow(1, 1);

    describe("#VertexArray", []() {

        it("can create multiple vertex array objects", []() {
            auto vaos = glt::VertexArray(2);

            for (auto vbo : vaos)
                AssertThat(vbo, Is().GreaterThan(0));

            AssertThat(vaos.size(), Equals(2));
            AssertThat(vaos[0], Is().Not().EqualTo(vaos[1]));
        });

        it("has correct move semantics", []() {
            auto varr1 = glt::VertexArray();
            auto varr2 = glt::VertexArray(2);

            AssertThat(varr1.size(), Equals(0));
            AssertThat(varr2.size(), Equals(2));

            varr1 = std::move(varr2);

            AssertThat(varr1.size(), Equals(2));
            AssertThat(varr2.size(), Equals(0));
        });
    });
});
