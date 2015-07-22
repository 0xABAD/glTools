#ifndef _FILEUTILS_HPP_
#define _FILEUTILS_HPP_

#include <glt/api.hpp>
#include <glt/gl_core_4_5.hpp>
#include <string>
#include <ostream>

namespace glt {

/**
 * Reads all ascii text from the file at filepath into out.
 * 
 * @param filepath  Path of file to read text from.
 * @param out       ostream where text will be piped into.  May contain
 *                  garbage if the file could not be read.
 *
 * @return  True if the text was loaded in successsfully, false otherwise.
 */
GLT_API bool readAllAsciiText(const std::string& filepath, std::ostream& out);

/**
 * Returns the OpenGL shader type based off the extension of filename.
 *
 * The extension of filename is expected to be one of the file extensions
 * expected by the glslangValidator shader reference compiler by the
 * Kronos group.  The valid extensions are vert, frag, geom, tesc, tese,
 * and comp.
 *
 * @param filename  Name of the shader file
 *
 * @return  One of the shader types defined by the OpenGL API (e.g.
 *          GL_VERTEX_SHADER) or -1 if the extension is not recognized.
 */
GLT_API GLenum shaderType(const std::string& filename);

}

#endif /* _FILEUTILS_HPP_ */
