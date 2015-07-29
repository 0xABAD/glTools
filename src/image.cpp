#include <glt/image.hpp>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace glt {

Image::Image(const char *filepath, bool flip, int force)
    : _data(nullptr)
    , _width(0)
    , _height(0)
    , _compPerPixel(0)
{
    stbi_set_flip_vertically_on_load(flip);
    _data = stbi_load(filepath, &_width, &_height, &_compPerPixel, 0);
}

unsigned char* destroy(unsigned char *data)
{
    stbi_image_free(data);
    return nullptr;
}

Image::~Image()
{
    _data = destroy(_data);
}

Image::Image(Image&& rhs)
    : _data(nullptr)
    , _width(0)
    , _height(0)
    , _compPerPixel(0)
{
    std::swap(_data,         rhs._data);
    std::swap(_width,        rhs._width);
    std::swap(_height,       rhs._height);
    std::swap(_compPerPixel, rhs._compPerPixel);
}

Image& Image::operator=(Image&& rhs)
{
    _data = destroy(_data);
    _width = _height = _compPerPixel = 0;
    std::swap(_data,         rhs._data);
    std::swap(_width,        rhs._width);
    std::swap(_height,       rhs._height);
    std::swap(_compPerPixel, rhs._compPerPixel);

    return *this;
}

void loadTexture2D(const char * filepath, 
                   bool         flip, 
                   GLuint       texture, 
                   GLenum       internalformat, 
                   GLenum       format)
{
    glt::Image image(filepath, flip);

    gl::BindTexture(gl::TEXTURE_2D, texture);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
    gl::TextureStorage2D(texture, 1, internalformat, image.width(), image.height());
    gl::TextureSubImage2D(texture, 0, 0, 0, 
                         image.width(), image.height(), 
                         format, gl::UNSIGNED_BYTE, 
                         image.data());
}

} // end namespace glt
