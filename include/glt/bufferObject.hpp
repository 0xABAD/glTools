#ifndef __BUFFER_OBJECT_HPP__
#define __BUFFER_OBJECT_HPP__

#include <glt/api.hpp>
#include <glt/gl.hpp>
#include <vector>

namespace glt {

using Allocator   = void (*)(GLsizei, GLuint *);
using Deallocator = void (*)(GLsizei, const GLuint *);

/**
 * Container for OpenGL buffer objects of various types.
 * Has the same interface, albiet a subset, of an STL vector.  
 * However, unlike a vector, a BufferObject can not be modified 
 * after it is created.
 */
template <Allocator allocator, Deallocator deallocator>
class BufferObject {
private:
    std::vector<GLuint> _vector;

    void destroy()
    {
        deallocator(_vector.size(), _vector.data()); 
        _vector.clear();
    }

public:
    BufferObject() : BufferObject(0) {}

    explicit BufferObject(GLsizei count)
        : _vector(count, 0) 
    { 
        allocator(count, _vector.data()); 
    }

    virtual ~BufferObject() { destroy(); }

    BufferObject(const BufferObject&)            = delete;
    BufferObject& operator=(const BufferObject&) = delete;

    BufferObject(BufferObject&& rhs) 
        : _vector(0)
    { _vector.swap(rhs._vector); }

    BufferObject& operator=(BufferObject&& rhs)
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

class VertexBuffer final 
    : public BufferObject<gl::GenBuffers, gl::DeleteBuffers>
{
public:
             VertexBuffer()              : BufferObject()      {}
    explicit VertexBuffer(GLsizei count) : BufferObject(count) {}
};

class VertexArray final 
    : public BufferObject<gl::GenVertexArrays, gl::DeleteVertexArrays>
{
public:
             VertexArray()              : BufferObject()      {}
    explicit VertexArray(GLsizei count) : BufferObject(count) {}
};

class TextureBuffer final 
    : public BufferObject<gl::GenTextures, gl::DeleteTextures>
{
public:
             TextureBuffer()              : BufferObject()      {}
    explicit TextureBuffer(GLsizei count) : BufferObject(count) {}
};

} // end namespace glt

#endif  // __BUFFER_OBJECT_HPP__
