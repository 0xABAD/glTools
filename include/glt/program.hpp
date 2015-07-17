#ifndef __PROGRAM_HPP__
#define __PROGRAM_HPP__

#include <glt/api.hpp>
#include <ostream>

namespace glt {

class GLT_API Program final {
private:
    GLuint _program;
public:
    Program() : _program(0) {}
    ~Program() { gl::DeleteProgram(_program); }

    Program(const Program&)            = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&& other) : Program() {
        std::swap(_program, other._program);
    }

    Program& operator=(Program&& other) {
        gl::DeleteProgram(_program);
        _program = 0;
        std::swap(_program, other._program);
        return *this;
    }

    static Program create() {
        Program prog;
        prog._program = gl::CreateProgram();
        return prog;
    }

    operator GLuint() const { return _program; }
    GLuint   getId()  const { return _program; }
};

/**
 * Compile an OpenGL program using the shader programs from the given file paths.
 *
 * @param out     Out stream to place the error message if the shader 
 *          could not compiled for any reason.  This parameter is
 *          optional.
 *
 * @param paths   Zero or more file path names with valid glslangValidator
 *          extensions.  @see shaderType
 *
 * @returns  If any of the shaders can not be compiled or linked into the program
 *       for any reason the the returned program will have an id of zero, otherwise
 *       it will have an id greater than zero.
 */
Program GLT_API compileProgram(std::ostream &out, std::initializer_list<std::string> paths);
Program GLT_API compileProgram(std::initializer_list<std::string> paths);

/**
 * Compile an OpenGL program using the given pre-compiled shader programs.
 *
 * @param out       Out stream to place the error message if the program
 *                  can not be linked for any reason.
 *
 * @param shaderId  Id of the first shader to link to the program.
 *
 * @param otherIds  Zero or more precompiled shader program ids.
 *
 * @returns  If any of the shader ids are zero or the program can not be
 *           linked for any reason then a program with an id of zero will
 *           be returned, otherwise the program will have an id greater
 *           than zero.
 */
Program GLT_API compileProgram(std::ostream &out, GLuint shaderId, std::initializer_list<GLuint> otherIds);
Program GLT_API compileProgram(GLuint shaderId, std::initializer_list<GLuint> otherIds);

} // end namepsace glt

#endif // __PROGRAM_HPP__
