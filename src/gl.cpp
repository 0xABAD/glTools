#include <glt/gl.hpp>

namespace glt {

inline bool initGlTools()
{
    return gl::sys::LoadFunctions();
}

} // end namespace glt
