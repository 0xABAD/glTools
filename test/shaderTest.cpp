#include <glt/glt.hpp>
#include <glt/window.hpp>
#include <bandit/bandit.h>
#include <fstream>
#include <cstdio>

const char * VERTEX_SOURCE = "#version 450 core\n"
"layout (location = 0) in vec3 VertexPosition;\n"
"void main() {	gl_Position = vec4(VertexPosition, 1.0f); }\n";

const char * FRAGMENT_SOURCE = "#version 450 core\n"
"layout (location = 0) out vec4 FragColor;\n"
"void main() {	FragColor = vec4(0.2f, 0.5f, 0.8f, 1.0f); }\n";

const GLchar * BAD_SOURCE = "#version 450 core\n"
"layout (location = 0) in vec3 VertexPosition	// missing semicolon \n"
"void main() { gl_Position = vec4(VertexPosition, 1.0f); }\n";

using namespace bandit;

go_bandit([]() {
    glt::Window window(1, 1, "Test", nullptr, nullptr);

    window.hide();
    window.makeCurrentContext();
    glt::initGlTools();

    describe("shader compilation errors: ", []() {

        it("fails with bogus filepath", []() {
            auto shader = glt::compileShader("__xdslfkj_foo_bar__");
            AssertThat( shader.getId(), Equals(0) );
        });

        it("fails with unrecognized shader file extension", []() {
            auto temp   = "shader.vtx";
            auto file   = std::ofstream(temp);
            auto shader = glt::compileShader(temp);

            AssertThat( shader.getId(), Equals(0) );

            file.close();
            std::remove(temp);
        });

        it("fails with errors in source code", []() {
            auto temp = "shader.vert";
            auto file = std::ofstream(temp);

            file << BAD_SOURCE;
            file.flush();
            file.close();

            auto errors = std::ostringstream();
            auto shader = glt::compileShader(temp, errors);

            AssertThat( shader.getId(), Equals(0) );
            AssertThat( errors.str(),  Contains("syntax error") );

            std::remove(temp);
        });

    });

    describe("shader compilation success: ", []() {

        it("can compile with valid source code", []() {
            auto temp = "shader.vert";
            auto file = std::ofstream(temp);

            file << VERTEX_SOURCE;
            file.flush();
            file.close();

            auto errors = std::ostringstream();
            auto shader = glt::compileShader(temp, errors);

            AssertThat( shader.getId(), Is().GreaterThan(0) );

            std::remove(temp);
        });

    });

    describe("compileProgram link errors: ", []() {

        it("fails when a shader can't be compiled", []() {
            auto vert  = "shader.vert";
            auto frag  = "shader.frag";
            auto file1 = std::ofstream(vert);
            auto file2 = std::ofstream(frag);

            file1 << BAD_SOURCE;
            file1.flush();
            file1.close();
            file2 << FRAGMENT_SOURCE;
            file2.flush();
            file2.close();

            auto errors  = std::ostringstream();
            auto program = glt::compileProgram(errors, { vert, frag });

            AssertThat(program.getId(), Equals(0));
            AssertThat(errors.str(), Contains("syntax error"));

            std::remove(vert);
            std::remove(frag);
        });

        it("fails when a zero shader is given", []() {
            auto program = glt::compileProgram((GLuint)0, {});
            AssertThat(program.getId(), Equals(0));
        });
    });

    describe("compileProgram can link: ", []() {

        it("successfully links vertex and fragment shader", []() {
            auto vert  = "shader.vert";
            auto frag  = "shader.frag";
            auto file1 = std::ofstream(vert);
            auto file2 = std::ofstream(frag);

            file1 << VERTEX_SOURCE;
            file1.flush();
            file1.close();
            file2 << FRAGMENT_SOURCE;
            file2.flush();
            file2.close();

            auto errors  = std::ostringstream();
            auto program = glt::compileProgram(errors, { vert, frag });

            AssertThat(program.getId(), Is().GreaterThan(0));

            std::remove(vert);
            std::remove(frag);
        });

    });

});
