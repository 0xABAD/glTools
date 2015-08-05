#include <glt/bitmapFont.hpp>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <algorithm>

using namespace std;

using Widths = glt::BitmapFont::CharWidths;

void readBitmap(istream         &stream, 
                vector<uint8_t> &_image, 
                Widths          &_charWidths, 
                int8_t          &_bpp,
                int8_t          &_asciiStart,
                int32_t         &_imageWidth, 
                int32_t         &_imageHeight, 
                int32_t         &_cellWidth, 
                int32_t         &_cellHeight)
{
    uint16_t magic;
    int8_t   bpp, start;
    int32_t  imgX, imgY, cellX, cellY;

    stream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
    if (magic != 0xF2BF) return;

    stream.read(reinterpret_cast<char *>(&imgX),  sizeof imgX);
    stream.read(reinterpret_cast<char *>(&imgY),  sizeof imgY);
    stream.read(reinterpret_cast<char *>(&cellX), sizeof cellX);
    stream.read(reinterpret_cast<char *>(&cellY), sizeof cellY);
    stream.read(reinterpret_cast<char *>(&bpp),   sizeof bpp);
    stream.read(reinterpret_cast<char *>(&start), sizeof start);
    stream.read(reinterpret_cast<char *>(_charWidths.data()), _charWidths.size());

    auto bytes = imgX * imgY * (bpp / 8);

    _image.resize(bytes);
    stream.read(reinterpret_cast<char *>(_image.data()), bytes);

    if (stream.bad() || stream.fail())
    {
        _image.resize(0);
        return;
    }

    _imageWidth  = imgX;
    _imageHeight = imgY;
    _cellWidth   = cellX;
    _cellHeight  = cellY;
    _bpp         = bpp;
    _asciiStart  = start;

    // Invert Y-axis of the image
    for (auto i = 0; i < imgY/2; ++i)
    {
        auto first = _image.data() + (i * imgX);
        auto last  = _image.data() + ((imgY - 1 - i) * imgX);

        swap_ranges(first, first + imgX, last);
    }
}

glt::BitmapFont::BitmapFont(const char * filename)
    : _imageWidth(0)
    , _imageHeight(0)
    , _cellWidth(0)
    , _cellHeight(0)
    , _bpp(0)
    , _asciiStart(0)
{
    stringstream stream(ios_base::in | ios_base::out | ios_base::binary);
    ifstream     file;

    file.open(filename, ios_base::in | ios_base::binary);

    if (file.is_open())
    {
        stream << file.rdbuf();
        file.close();
    }
    else return;

    if (!file.bad() && !file.fail())
        readBitmap(stream, 
                   _image,      _charWidths, 
                   _bpp,        _asciiStart,
                   _imageWidth, _imageHeight,
                   _cellWidth,  _cellHeight);
}

glt::BitmapFont::BitmapFont(const char * rawdata, size_t numBytes)
    : _imageWidth(0)
    , _imageHeight(0)
    , _cellWidth(0)
    , _cellHeight(0)
    , _bpp(0)
    , _asciiStart(0)
{
    stringstream stream(ios_base::in | ios_base::out | ios_base::binary);

    stream.write(rawdata, numBytes);
    readBitmap(stream, 
               _image,      _charWidths, 
               _bpp,        _asciiStart,
               _imageWidth, _imageHeight,
               _cellWidth,  _cellHeight);
}
