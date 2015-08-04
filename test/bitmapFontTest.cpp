#include <glt/bitmapFont.hpp>
#include <bandit/bandit.h>

#include <iostream>

#include "test_font.hpp"

using namespace bandit;

void runFontTest(const glt::BitmapFont &font)
{
    auto widths = font.characterWidths();
    auto size   = font.imageWidth() * font.imageHeight() * (font.bitsPerPixel() / 8);
    auto idx    = font.asciiStart();

    AssertThat(font.imageWidth(),   Equals(64));
    AssertThat(font.imageHeight(),  Equals(64));
    AssertThat(font.cellWidth(),    Equals(32));
    AssertThat(font.cellHeight(),   Equals(32));
    AssertThat(font.bitsPerPixel(), Equals(8));
    AssertThat(font.asciiStart(),   Equals(32));
    AssertThat(widths[idx],         Equals(8));
    AssertThat(widths[idx + 1],     Equals(8));
    AssertThat(widths[idx + 2],     Equals(10));
    AssertThat(widths[idx + 3],     Equals(17));
    AssertThat(font.size(),         Equals(size));
}

go_bandit([]() {
    describe("BitmapFont", []() {

        it("can load bitmap font image from file", []() {
            glt::BitmapFont font("test_img_64x64_cell_32x32_bpp_8_start_32_widths_8_8_10_17.bff");
            runFontTest(font);
        });

        it("can load bitmap font image from raw data", []() {
            glt::BitmapFont font(test_font.data(), test_font.size());
            runFontTest(font);
        });

    });

});
