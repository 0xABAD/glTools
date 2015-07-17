#include <glt/shader.hpp>
#include <glt/fileutils.hpp>
#include <utility>
#include <sstream>

namespace glt {

Shader GLT_API compileShader(const std::string& filename)
{
    auto shader_t = shaderType(filename);

    if (shader_t == -1) return Shader();
    else return compileShader(filename, shader_t);
}

Shader GLT_API compileShader(const std::string& filename, GLenum shadertype)
{
    std::ostringstream dump;
    return compileShader(filename, shadertype, dump);
}

Shader GLT_API compileShader(const std::string& filename, std::ostream &out)
{
    auto shader_t = shaderType(filename);

    if (shader_t == -1) return Shader();
    else return compileShader(filename, shader_t, out);
}

Shader GLT_API compileShader(const std::string& filename, GLenum shadertype, std::ostream &out)
{
    std::ostringstream contents;

    if (!readAllAsciiText(filename, contents))
        return Shader();

    auto shader = Shader(shadertype);
    auto asStr  = contents.str();
    auto source = asStr.c_str();

    gl::ShaderSource(shader, 1, static_cast<const GLchar * const *>(&source), nullptr);
    gl::CompileShader(shader);

    GLint success;
    gl::GetShaderiv(shader, gl::COMPILE_STATUS, &success);

    if (success == gl::FALSE_)
    {
        const GLsizei SIZE = 512;
        GLchar log[SIZE] = {0};

        gl::GetShaderInfoLog(shader, SIZE, nullptr, log);
        out << log;

        return Shader();
    }

    return shader;
}

} // end namespace glt
