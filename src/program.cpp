#include <glt/program.hpp>
#include <glt/shader.hpp>
#include <sstream>
#include <vector>

namespace glt {

#define LINK_PROGRAM(prog, out) {                         \
    GLint success;                                        \
    gl::LinkProgram(prog);                                \
    gl::GetProgramiv(prog, gl::LINK_STATUS, &success);    \
                                                          \
    if (success == gl::FALSE_)                            \
    {                                                     \
        const GLsizei SIZE = 512;                         \
        GLchar log[SIZE] = {0};                           \
                                                          \
        gl::GetProgramInfoLog(prog, SIZE, nullptr, log);  \
        out << log;                                       \
                                                          \
        return Program();                                 \
    }                                                     \
}

Program GLT_API compileProgram(std::ostream &out, std::initializer_list<std::string> shaderFilePaths)
{
    auto prog    = Program::create();
    auto shaders = std::vector<Shader>();

    for (auto path : shaderFilePaths)
    {
        auto shader = compileShader(path, out);

        if (shader != 0) gl::AttachShader(prog, shader);
        else return Program();

        // We don't want to have the shader delete itself here just yet.
        shaders.push_back(std::move(shader));
    }

    LINK_PROGRAM(prog, out);

    return prog;
}

Program GLT_API compileProgram(std::initializer_list<std::string> shaderFilePaths)
{
    return compileProgram(std::ostringstream(), shaderFilePaths);
}

Program GLT_API compileProgram(std::ostream &out, GLuint shaderId, std::initializer_list<GLuint> otherIds)
{
    auto prog = Program::create();

    gl::AttachShader(prog, shaderId);
    for (auto id : otherIds)
    {
        if (id != 0) gl::AttachShader(prog, id);
        else return Program();
    }

    LINK_PROGRAM(prog, out);

    return prog;
}

Program GLT_API compileProgram(GLuint shaderId, std::initializer_list<GLuint> otherIds)
{
    return compileProgram(std::ostringstream(), shaderId, otherIds);
}

#undef LINK_PROGRAM

} // end namespace glt
