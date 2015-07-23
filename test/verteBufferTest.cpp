#include <glt/vertexBuffer.hpp>
#include <glt/window.hpp>
#include <bandit/bandit.h>

using namespace bandit;

go_bandit([]() {
    auto ctx = glt::easyWindow(1, 1);

    describe("#VertexBuffer", []() {

        it("can create multiple vertex buffer objects", []() {
            auto vbos = glt::VertexBuffer(2);

            for (auto vbo : vbos)
                AssertThat(vbo, Is().GreaterThan(0));

            AssertThat(vbos.size(), Equals(2));
            AssertThat(vbos[0], Is().Not().EqualTo(vbos[1]));
        });

        it("has correct move semantics", []() {
            auto vbuf1 = glt::VertexBuffer();
            auto vbuf2 = glt::VertexBuffer(2);

            AssertThat(vbuf1.size(), Equals(0));
            AssertThat(vbuf2.size(), Equals(2));

            vbuf1 = std::move(vbuf2);

            AssertThat(vbuf1.size(), Equals(2));
            AssertThat(vbuf2.size(), Equals(0));
        });
    });
});