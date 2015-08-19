#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include <glt/glt.hpp>
#include <glt/bitmapFont.hpp>
#include <glm/glm.hpp>

namespace glt {

/**
 * A simple text rendering engine.
 */
class GLT_API Text {
public:
    Text();

    /**
     * Constructs a text engine using the built-in default fragment shader.
     *
     * @param font     Type of bitmap font to use.
     * @param buffers  Number of buffers the Text can maintain.  It is useful
     *                 to think of a buffer as single line of text.
     * @param capacity How many characters that can be fit into a single buffer.
     *
     */
    Text(const glt::BitmapFont& font, size_t buffers, size_t capacity);

    /**
     * Constructs a text engine.
     *
     * @param font     Type of bitmap font to use.
     * @param buffers  Number of buffers the Text can maintain.  It is useful
     *                 to think of a buffer as single line of text.
     * @param capacity How many characters that can be fit into a single buffer.
     *
     * @param fragmentShader  A custom fragment shader to use instead of the
     *                        built in default.  This shader is expected to
     *                        have a vec4 uniform named 'TextColor' and a
     *                        uniform sampler2D named 'Bitmap' at layout
     *                        binding 0.
     */
    Text(const glt::BitmapFont& font, size_t buffers, size_t capacity, const glt::Shader& fragmentShader);

    Text(Text&&);

    Text(const Text&)         = delete;
    Text& operator =(Text)    = delete;
    Text& operator =(Text &&) = delete;

    /** Returns how many buffers this Text engine contains. */
    size_t bufferCount() { return _buffers.size(); }

    /** Returns the shader program Id of the internal shader program. */
    GLuint programId() { return _program.getId(); }

    /**
     * Renders all buffers of text.
     *
     * @param modelViewProjection  Matrix to apply to the text character vertices.
     * @param textColor            Color that the text should be rendered at.
     */
    void render(const glm::mat4& modelViewProjection,
                const glm::vec4& textColor)
    {
        render(0, _buffers.size(), modelViewProjection, textColor);
    }

    /**
     * Renders the line of text specified at the buffer location.  So, if
     * the Text engine was constructed with 3 buffers and you want to render
     * the second line of text then you would pass in 1 to this method.
     *
     * @param modelViewProjection  Matrix to apply to the text character vertices.
     * @param textColor            Color that the text should be rendered at.
     */
    void render(size_t buffer,
                const glm::mat4& modelViewProjection,
                const glm::vec4& textColor)
    {
        render(buffer, buffer + 1, modelViewProjection, textColor);
    }

    /**
     * Renders the lines of text within the [start, end) range.  So
     * a range of [0, 2) would render the text at buffers 0 and 1.
     *
     * @param modelViewProjection  Matrix to apply to the text character vertices.
     * @param textColor            Color that the text should be rendered at.
     */
    void render(size_t start,
                size_t end,
                const glm::mat4& modelViewProjection,
                const glm::vec4& textColor);

    /**
     * Loads the string of characters into the buffer location specified
     * by 'buffer'.
     *
     * @param buffer  Buffer ID to load the charcter string into.
     *
     * @param text    Text string to load.  If the count of characters
     *                in string exceed the capacity given to the Text
     *                constructor then only the first 'capcity' characters 
     *                of the string will be loaded.
     *
     * @param lowerLeft  Lower left coordinate of the first character in the
     *                   string.
     *
     * @param heightScale  Height scale of the rendered characters.
     */
    void load(size_t buffer,
              const std::string& text,
              const glm::vec3& lowerLeft,
              GLfloat heightScale)
    {
        load(buffer, text, lowerLeft, glm::mat4{}, heightScale);
    }

    /**
     * Loads the string of characters into the buffer location specified
     * by 'buffer'.
     *
     * @param buffer  Buffer ID to load the charcter string into.
     *
     * @param text    Text string to load.  If the count of characters
     *                in string exceed the capacity given to the Text
     *                constructor then only the first 'capcity' characters 
     *                of the string will be loaded.
     *
     * @param lowerLeft  Lower left coordinate of the first character in the
     *                   string.
     *
     * @param transform  The initial transform to apply to the all vertices
     *                   of the characters in the string the buffer.
     *
     * @param heightScale  Height scale of the rendered characters.
     */
    void load(size_t buffer,
              const std::string& text,
              const glm::vec3& lowerLeft,
              const glm::mat4& transform,
              GLfloat heightScale);

private:
    glt::Program       _program;
    glt::VertexArray   _vao;
    glt::VertexBuffer  _vbo;
    glt::TextureBuffer _tbo;

    std::vector<size_t>    _buffers;
    std::vector<glm::mat4> _transforms;
    const size_t           _capacity;

    // Font image rendering information
    const GLfloat _imgX, _imgY, _cellX, _cellY, _start;
    const glt::BitmapFont::CharWidths _widths;

    // Shader program uniform locations
    GLint _mvpLoc
        , _startLoc
        , _imgWidthLoc
        , _cellWidthLoc
        , _cellHeightLoc
        , _cellCountXLoc
        , _imgYLoc
        , _textColorLoc;
};

/**
 * Returns a Text rendering engine using the built-in monospaced
 * Consolas font.
 *
 * @param buffers  How many buffers (lines of text) the text engine contains.
 * @param capacity How many characters can fit into a single buffer.
 *
 * @param fragmentShader  An optional custom fragment shader to use instead 
 *                        of the built in default.  This shader is expected to
 *                        have a vec4 uniform named 'TextColor' and a
 *                        uniform sampler2D named 'Bitmap' at layout
 *                        binding 0.
 *
 */
GLT_API Text makeConsolas(size_t buffers, size_t capacity);
GLT_API Text makeConsolas(size_t buffers, size_t capacity, const Shader& fragmentShader);

/**
 * Returns a Text rendering engine using the built-in Segoe UI font.
 *
 * @param buffers  How many buffers (lines of text) the text engine contains.
 * @param capacity How many characters can fit into a single buffer.
 *
 * @param fragmentShader  An optional custom fragment shader to use instead 
 *                        of the built in default.  This shader is expected to
 *                        have a vec4 uniform named 'TextColor' and a
 *                        uniform sampler2D named 'Bitmap' at layout
 *                        binding 0.
 *
 */
GLT_API Text makeSegoeUI(size_t buffers, size_t capacity);
GLT_API Text makeSegoeUI(size_t buffers, size_t capacity, const Shader& fragmentShader);

} // end namespace glt


#endif // __TEXT_HPP__