#include <glt/window.hpp>
#include <glt/textureBuffer.hpp>
#include <glt/texture.hpp>
#include <bandit/bandit.h>

#include <iostream>
using namespace bandit;

go_bandit([]() {
    auto window = glt::easyWindow(1, 1);

    describe("TextureBuffer", []() {

        it("can create a texture buffer", []() {
            glt::TextureBuffer buf(2);

            AssertThat(buf.size(), Equals(2));
            AssertThat(buf[0],     Is().GreaterThan(0));
            AssertThat(buf[1],     Is().GreaterThan(0));
        });
    });

    describe("Texture", []() {

        it("can load image from file", []() {
            auto texture = glt::Texture("container.jpg");
            auto isValid = texture.data() != nullptr;

            AssertThat(isValid,                      Is().True());
            AssertThat(texture.width(),              Equals(512));
            AssertThat(texture.height(),             Equals(512));
            AssertThat(texture.componentsPerPixel(), Equals(3));
        });
    });

});