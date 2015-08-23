#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <glt/gl.hpp>
#include <string>
#include <ostream>

namespace glt {

class Shader final {
private:
    GLuint _shader;
    GLenum _shader_t;

public:
    Shader() : _shader(0), _shader_t(0) {}

    explicit Shader(GLenum shaderType) 
        : _shader(0)
        , _shader_t(shaderType) 
    {
        _shader = gl::CreateShader(shaderType);
    }

    ~Shader() { gl::DeleteShader(_shader); }

    Shader(const Shader&)            = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) : Shader() {
        std::swap(_shader,   other._shader);
        std::swap(_shader_t, other._shader_t);
    }

    Shader& operator=(Shader&& other) {
        gl::DeleteShader(_shader);
        _shader   = 0;
        _shader_t = 0;
        std::swap(_shader,   other._shader);
        std::swap(_shader_t, other._shader_t);
        return *this;
    }

    operator GLuint()  const { return _shader; }
    GLuint   getId()   const { return _shader;  }
    GLenum   getType() const { return _shader_t; }
};

/**
 * Compile an OpenGL shader using the source from filepath.
 *
 * @param filepath    Path to the file containing the shader source code.
 *
 * @param shadertype  The shader's type (e.g. GL_VERTEX_SHADER).  This parameter
 *                    is optional and if left out then the shader's type will
 *                    will be inferred from by the shader's file extension.
 *                    @see shaderType()
 *
 * @param out         Out stream to place the error message if the shader 
 *                    could not compiled for any reason.  This parameter is
 *                    optional.
 *
 * @returns  An OpenGL shader with a positive shader id.  If the shader could
 *           not be compiled for any reason then the shader returned will have
 *           and id of zero.
 */
Shader compileShader(const std::string& filepath, GLenum shadertype, std::ostream &out);
Shader compileShader(const std::string& filepath, GLenum shadertype);
Shader compileShader(const std::string& filepath, std::ostream &out);
Shader compileShader(const std::string& filepath);

/**
 * Compile a shader directly from a source string.
 *
 * @param source      The shaders source code.
 * @param shadertype  Shader type (e.g. GL_VERTEX_SHADER).
 * @param out         Out stream to place the error message if the shader 
 *                    could not compiled for any reason.  This parameter is
 *                    optional.

 * @returns  An OpenGL shader with a positive shader id.  If the shader could
 *           not be compiled for any reason then the shader returned will have
 *           and id of zero.
 */
Shader compileShaderSource(const char * source, GLenum shadertype, std::ostream &out);
Shader compileShaderSource(const char * source, GLenum shadertype);

} // end namespace glt

#endif // __SHADER_HPP__
