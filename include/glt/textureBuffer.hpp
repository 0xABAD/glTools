#ifndef __TEXTURE_BUFFER_HPP__
#define __TEXTURE_BUFFER_HPP__

#include <glt/api.hpp>
#include <glt/gl.hpp>
#include <vector>

namespace glt {

/**
 * Container for OpenGL texture objects.  Has the same 
 * interface, albiet a subset, of an STL vector.  Unlike a
 * vector, a TextureBuffer can not be modified after it is
 * created.
 */
class TextureBuffer final {
private:
    std::vector<GLuint> _vector;

    void destroy()
    {
        gl::DeleteTextures(_vector.size(), _vector.data()); 
        _vector.clear();
    }

public:
    TextureBuffer() : TextureBuffer(0) {}

    explicit TextureBuffer(std::size_t count)
        : _vector(count, 0) 
    { gl::GenTextures(count, _vector.data()); }

    ~TextureBuffer() { destroy(); }

    TextureBuffer(const TextureBuffer&)            = delete;
    TextureBuffer& operator=(const TextureBuffer&) = delete;

    TextureBuffer(TextureBuffer&& rhs) 
        : _vector(0)
    { _vector.swap(rhs._vector); }

    TextureBuffer& operator=(TextureBuffer&& rhs)
    {
        destroy();
        _vector.swap(rhs._vector);
        return *this;
    }

    // No returning of references.
    GLuint at(std::size_t index)             { return _vector.at(index); }
    GLuint at(std::size_t index)       const { return _vector.at(index); }
    GLuint operator[](std::size_t pos)       { return _vector[pos]; }
    GLuint operator[](std::size_t pos) const { return _vector[pos]; }

    const GLuint* data() const { return _vector.data(); }

    bool empty()       { return _vector.empty(); }
    bool empty() const { return _vector.empty(); }

    std::size_t size()       { return _vector.size(); }
    std::size_t size() const { return _vector.size(); }

    using const_iterator         = std::vector<GLuint>::const_iterator;
    using const_reverse_iterator = std::vector<GLuint>::const_reverse_iterator;

    const_iterator         begin()   const { return _vector.begin(); }
    const_iterator         cbegin()  const { return _vector.cbegin(); }
    const_iterator         end()     const { return _vector.end(); }
    const_iterator         cend()    const { return _vector.cend(); }
    const_reverse_iterator rbegin()  const { return _vector.rbegin(); }
    const_reverse_iterator crbegin() const { return _vector.crbegin(); }
    const_reverse_iterator rend()    const { return _vector.rend(); }
    const_reverse_iterator crend()   const { return _vector.crend(); }
};

} // end namespace glt

#endif  // __TEXTURE_BUFFER_HPP__
