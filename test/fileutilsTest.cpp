#include <cstdio>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <bandit/bandit.h>
#include <glt/glt.hpp>

using namespace bandit;

go_bandit([]() {

	describe ("glt::readAllAsciiText:", []() {
		auto temp = "__test_file__.txt";

		it ("can read all ascii text", [&]() {
			auto text = "testing\n";

			std::ofstream      outfile(temp);
			std::ostringstream buffer;

			outfile << text;
			outfile.flush();
			outfile.close();

			AssertThat(glt::readAllAsciiText(temp, buffer), IsTrue());
			AssertThat(buffer.str(), Is().EqualTo(text));

			std::remove(temp);
		});

		it ("returns false for non-existing file", [&]() {
			AssertThat(glt::readAllAsciiText(temp, std::ostringstream()), IsFalse());
		});
	});

	describe("glt::shaderType:", []() {

		it("returns a vertex shader type", []() {
			AssertThat(glt::shaderType("foo.vert"), Is().EqualTo(gl::VERTEX_SHADER));
		});

		it("returns a fragment shader type", []() {
			AssertThat(glt::shaderType("foo.frag"), Is().EqualTo(gl::FRAGMENT_SHADER));
		});

		it("returns a geometry shader type", []() {
			AssertThat(glt::shaderType("foo.geom"), Is().EqualTo(gl::GEOMETRY_SHADER));
		});

		it("returns a tessellation control shader type", []() {
			AssertThat(glt::shaderType("foo.tesc"), Is().EqualTo(gl::TESS_CONTROL_SHADER));
		});

		it("returns a tessellation evaluation shader type", []() {
			AssertThat(glt::shaderType("foo.tese"), Is().EqualTo(gl::TESS_EVALUATION_SHADER));
		});

		it("returns a compute shader type", []() {
			AssertThat(glt::shaderType("foo.comp"), Is().EqualTo(gl::COMPUTE_SHADER));
		});

		it("returns a geometry shader type with mixed case extension", []() {
			AssertThat(glt::shaderType("foo.GeOm"), Is().EqualTo(gl::GEOMETRY_SHADER));
		});

		it("returns -1 with unrecognized extension", []() {
			AssertThat(glt::shaderType("foo.bar"), Is().EqualTo(-1));
		});
	});
});
