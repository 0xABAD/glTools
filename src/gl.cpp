#include <glt/gl.hpp>

namespace glt {

bool initGlTools()
{
    return gl::sys::LoadFunctions();
}

} // end namespace glt
