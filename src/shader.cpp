#include <glt/shader.hpp>
#include <glt/fileutils.hpp>
#include <utility>
#include <sstream>

namespace glt {

bool compileSource(const Shader& shader, const char * source, GLenum shadertype, std::ostream& out)
{
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

        return false;
    }

    return true;
}

Shader compileShader(const std::string& filename)
{
    auto shader_t = shaderType(filename);

    if (shader_t == -1) return Shader();
    else return compileShader(filename, shader_t);
}

Shader compileShader(const std::string& filename, GLenum shadertype)
{
    std::ostringstream dump;
    return compileShader(filename, shadertype, dump);
}

Shader compileShader(const std::string& filename, std::ostream &out)
{
    auto shader_t = shaderType(filename);

    if (shader_t == -1) return Shader();
    else return compileShader(filename, shader_t, out);
}

Shader compileShader(const std::string& filename, GLenum shadertype, std::ostream &out)
{
    std::ostringstream contents;

    if (!readAllAsciiText(filename, contents))
        return Shader();

    auto shader = Shader(shadertype);
    auto asStr  = contents.str();
    auto source = asStr.c_str();

    if (compileSource(shader, source, shadertype, out))
        return shader;

    return Shader();
}

Shader compileShaderSource(const char * source, GLenum shadertype, std::ostream &out)
{
    auto shader = Shader(shadertype);

    if (compileSource(shader, source, shadertype, out))
        return shader;

    return Shader();
}

Shader compileShaderSource(const char * source, GLenum shadertype)
{
    std::ostringstream dump;
    return compileShaderSource(source, shadertype, dump);
}

} // end namespace glt
