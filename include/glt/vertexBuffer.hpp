#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

#include <glt/api.hpp>
#include <glt/gl.hpp>
#include <vector>

namespace glt {

/**
 * Container for OpenGL vertex buffer objects.  Has the same 
 * interface, albiet a subset, of an STL vector.  Unlike a
 * vector, a VertexBuffer can not be modified after it is
 * created.
 */
class VertexBuffer final {
private:
    std::vector<GLuint> _vector;

    void destroy()
    {
        gl::DeleteBuffers(_vector.size(), _vector.data()); 
        _vector.clear();
    }

public:
    VertexBuffer() : VertexBuffer(0) {}

    explicit VertexBuffer(std::size_t count)
        : _vector(count, 0) 
    { gl::GenBuffers(count, _vector.data()); }

    ~VertexBuffer() { destroy(); }

    VertexBuffer(const VertexBuffer&)            = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& rhs) 
        : _vector(0)
    { _vector.swap(rhs._vector); }

    VertexBuffer& operator=(VertexBuffer&& rhs)
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

#endif  // __VERTEX_BUFFER_HPP__
