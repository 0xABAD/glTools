#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <glt/gl.hpp>

namespace glt {

/**
 * Provides ability to load an image from a file.  This is a
 * wrapper around the stb_image.h library.
 */
class Image final {
public:
    /** 
     * Constructs an image whose contents are from filepath.  The
     * components per pixel will be determined by the underlying
     * library.
     */
    explicit Image(const char *filepath) : Image(filepath, false, 0) {}

    /** 
     * Constructs an image whose contents are from filepath. 
     *
     * @param filepath  Path of the file to load the image contents from.
     * @param flip      True to flip the image vertically when loading.
     */
    Image(const char *filepath, bool flip) : Image(filepath, flip, 0) {}

    /** 
     * Constructs an image whose contents are from filepath. 
     *
     * @param filepath  Path of the file to load the image contents from.
     * @param flip      True to flip the image vertically when loading.
     * @param force     Forces the number components per pixel to be this
     *                  this number.  Valid values are from 1 thru 4 inclusive.
     *                  This range is not checked.
     */
    Image(const char *filepath, bool flip, int force);

    ~Image();

    Image()                 = delete;
    Image(const Image&)     = delete;
    Image& operator=(Image) = delete;

    Image(Image&&);
    Image& operator=(Image&&);

    const unsigned char * data() const { return _data; }

    /** The width of the image in pixels. */
    int width() const { return _width; }

    /** The height of the image in pixels. */
    int height() const { return _height; }

    /** The number of components per pixel of the image. */
    int componentsPerPixel() const { return _compPerPixel; }

private:
    unsigned char *_data;
    int _width, _height, _compPerPixel;
};

/**
 * Loads a 2D image as a texture into OpenGL.
 *
 * @param filepath        File path of image to load.
 * @param flip            Whether to flip the image vertically on load.
 * @param texture         Texture object that the texture will be bound to.
 * @param internalformat  Memory layout of each pixel in the image
 *                        (e.g. gl::RGBA8).
 * @param format          Format of each pixel in the image for usage
 *                        (e.g. gl::RGBA).
 */
void loadTexture2D(const char * filepath, 
                   bool         flip, 
                   GLuint       texture, 
                   GLenum       internalformat, 
                   GLenum       format);

} // end namespace glt

#endif // __IMAGE_HPP__
