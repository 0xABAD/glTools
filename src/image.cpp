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

} // end namespace glt
