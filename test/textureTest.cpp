#include <glt/window.hpp>
#include <glt/textureBuffer.hpp>
#include <glt/image.hpp>
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

    describe("Image", []() {

        it("can load image from file", []() {
            auto image   = glt::Image("container.jpg");
            auto isValid = image.data() != nullptr;

            AssertThat(isValid,                    Is().True());
            AssertThat(image.width(),              Equals(512));
            AssertThat(image.height(),             Equals(512));
            AssertThat(image.componentsPerPixel(), Equals(3));
        });
    });

});