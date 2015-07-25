#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <glt/api.hpp>

namespace glt {

class GLT_API Texture {
public:
    explicit Texture(const char *filepath) : Texture(filepath, 0) {};

    Texture(const char *filepath, int force);

    ~Texture();

    Texture()                   = delete;
    Texture(const Texture&)     = delete;
    Texture& operator=(Texture) = delete;

    Texture(Texture&&);
    Texture& operator=(Texture&&);

    const unsigned char * data() const { return _data; }

    int width()              const { return _width; }
    int height()             const { return _height; }
    int componentsPerPixel() const { return _compPerPixel; }

private:
    unsigned char *_data;
    int _width, _height, _compPerPixel;
};

} // end namespace glt

#endif // __TEXTURE_HPP__
