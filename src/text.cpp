#include <glt/text.hpp>
#include <glt/gl.hpp>
#include <glt/textrender_vert.hpp>
#include <glt/textrender_geom.hpp>
#include <glt/textrender_frag.hpp>
#include <glt/consolas.hpp>
#include <glt/segoeui.hpp>
#include <glm/gtc/type_ptr.hpp>

glt::Text::Text()
    : _widths()
    , _imgX(0)
    , _imgY(0)
    , _cellX(0)
    , _cellY(0)
    , _start(0)
    , _capacity(0)
{}

glt::Text::Text(const glt::BitmapFont& font, size_t buffers, size_t capacity)
    : glt::Text(font, buffers, capacity, 
                glt::compileShaderSource(textrender_frag.data(), gl::FRAGMENT_SHADER))
{}

glt::Text::Text(const glt::BitmapFont& font, 
                size_t buffers, 
                size_t capacity, 
                const glt::Shader& fragmentShader)
    : _program(glt::compileProgram(fragmentShader, { 
        glt::compileShaderSource(textrender_geom.data(), gl::GEOMETRY_SHADER), 
        glt::compileShaderSource(textrender_vert.data(), gl::VERTEX_SHADER)
    }))
    , _vao(glt::VertexArray(buffers))
    , _vbo(glt::VertexBuffer(buffers))
    , _tbo(glt::TextureBuffer(1))
    , _widths(font.characterWidths())
    , _imgX((GLfloat) font.imageWidth())
    , _imgY((GLfloat) font.imageHeight())
    , _cellX((GLfloat) font.cellWidth())
    , _cellY((GLfloat) font.cellHeight())
    , _start((GLfloat) font.asciiStart())
    , _capacity(capacity)
{
    if (_program.getId() == 0) return;

    _buffers.resize(buffers);
    _transforms.resize(buffers);

    GLenum internalFormat, format;
    switch (font.bitsPerPixel())
    {
    case 8:  internalFormat = gl::R8;    format = gl::RED;  break;
    case 24: internalFormat = gl::RGB8;  format = gl::RGB;  break;
    case 32: internalFormat = gl::RGBA8; format = gl::RGBA; break;
    default: internalFormat = 0;         format = 0;        break;
    }

    const auto PT_SIZE    = 3;
    const auto TRAIT_SIZE = 3;
    const auto STORAGE = (PT_SIZE + TRAIT_SIZE) * sizeof GLfloat;
    for (auto i = 0u; i < buffers; ++i)
    {
        gl::BindVertexArray(_vao[i]);
        gl::BindBuffer(gl::ARRAY_BUFFER, _vbo[i]);
        gl::NamedBufferStorage(_vbo[i], _capacity * STORAGE, nullptr, gl::MAP_WRITE_BIT);
        gl::VertexAttribPointer(0, PT_SIZE, gl::FLOAT, false, STORAGE, nullptr);
        gl::VertexAttribPointer(1, TRAIT_SIZE, gl::FLOAT, false, STORAGE, (void *)(PT_SIZE * sizeof GLfloat));
        gl::EnableVertexAttribArray(0);
        gl::EnableVertexAttribArray(1);
    }

    auto width  = font.imageWidth();
    auto height = font.imageHeight();

    gl::BindTexture(gl::TEXTURE_2D, _tbo[0]);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
    gl::TextureStorage2D(_tbo[0], 1u, internalFormat, width, height);
    gl::TextureSubImage2D(_tbo[0], 0, 0, 0, width, height, format, gl::UNSIGNED_BYTE, font.image());
    gl::BindTexture(gl::TEXTURE_2D, 0);

    _mvpLoc        = gl::GetUniformLocation(_program, "MVP");
    _startLoc      = gl::GetUniformLocation(_program, "StartIndex");
    _imgWidthLoc   = gl::GetUniformLocation(_program, "ImageWidth");
    _cellWidthLoc  = gl::GetUniformLocation(_program, "CellWidth");
    _cellHeightLoc = gl::GetUniformLocation(_program, "CellHeight");
    _cellCountXLoc = gl::GetUniformLocation(_program, "CellCountX");
    _imgYLoc       = gl::GetUniformLocation(_program, "ImgY");
    _textColorLoc  = gl::GetUniformLocation(_program, "TextColor");
}

glt::Text::Text(Text&& other)
    : _program(std::move(other._program))
    , _vao(std::move(other._vao))
    , _vbo(std::move(other._vbo))
    , _tbo(std::move(other._tbo))
    , _widths(std::move(other._widths))
    , _imgX(other._imgX)
    , _imgY(other._imgY)
    , _cellX(other._cellX)
    , _cellY(other._cellY)
    , _start(other._start)
    , _capacity(other._capacity)
    , _buffers(std::move(other._buffers))
    , _transforms(std::move(other._transforms))
    , _mvpLoc(other._mvpLoc)
    , _startLoc(other._startLoc)
    , _imgWidthLoc(other._imgWidthLoc)
    , _cellWidthLoc(other._cellWidthLoc)
    , _cellHeightLoc(other._cellHeightLoc)
    , _cellCountXLoc(other._cellCountXLoc)
    , _imgYLoc(other._imgYLoc)
    , _textColorLoc(other._textColorLoc)
{}

void glt::Text::render(size_t start,
                       size_t end,
                       const glm::mat4& modelViewProjection,
                       const glm::vec4& textColor)
{
    if (_program.getId() == 0) return;

    gl::UseProgram(_program);
    gl::Uniform4fv(_textColorLoc,  1, glm::value_ptr(textColor));
    gl::Uniform1f(_startLoc,      _start);
    gl::Uniform1f(_imgWidthLoc,   _imgX);
    gl::Uniform1f(_cellWidthLoc,  _cellX);
    gl::Uniform1f(_cellHeightLoc, _cellY);
    gl::Uniform1f(_cellCountXLoc, _imgX / _cellX);
    gl::Uniform1f(_imgYLoc,       _cellY / _imgY);

    gl::ActiveTexture(gl::TEXTURE0);
    gl::BindTexture(gl::TEXTURE_2D, _tbo[0]);

    for (auto i = start; i < end; ++i)
    {
        auto MVP = modelViewProjection * _transforms[i];
        
        gl::UniformMatrix4fv(_mvpLoc, 1, gl::FALSE_, glm::value_ptr(MVP));
        gl::BindVertexArray(_vao[i]);
        gl::DrawArrays(gl::POINTS, 0, _buffers[i]);
        gl::BindVertexArray(0);
    }

    gl::BindTexture(gl::TEXTURE_2D, 0);
}

void glt::Text::load(size_t buffer,
                     const std::string& text,
                     const glm::vec3& lowerLeft,
                     const glm::mat4& transform,
                     GLfloat heightScale)
{
    if (_program.getId() == 0) return;

    auto count  = std::min(text.size(), _capacity);
    auto accumX = 0.0f;
    auto bytes  = count * sizeof GLfloat;
    auto points = (GLfloat *)gl::MapNamedBufferRange(_vbo[buffer], 0, bytes, gl::MAP_WRITE_BIT);

    _buffers[buffer]    = count;
    _transforms[buffer] = transform;

    for (auto i = 0u; i < count; ++i)
    {
        auto chIdx = (size_t)text[i];
        auto width = (GLfloat)_widths[chIdx];

        *points++ = lowerLeft.x + accumX;
        *points++ = lowerLeft.y;
        *points++ = lowerLeft.z;
        *points++ = width;
        *points++ = heightScale;
        *points++ = (GLfloat)chIdx;

        accumX += width * (heightScale / _cellY);
    }

    gl::UnmapNamedBuffer(_vbo[buffer]);
}

glt::Text glt::makeConsolas(size_t buffers, size_t capacity)
{
    auto bitmap = glt::BitmapFont(consolas.data(), consolas.size());
    return Text(bitmap, buffers, capacity);
}

glt::Text glt::makeConsolas(size_t buffers, size_t capacity, const Shader & fragmentShader)
{
    auto bitmap = glt::BitmapFont(consolas.data(), consolas.size());
    return Text(bitmap, buffers, capacity, fragmentShader);
}

glt::Text glt::makeSegoeUI(size_t buffers, size_t capacity)
{
    auto bitmap = glt::BitmapFont(segoeui.data(), segoeui.size());
    return Text(bitmap, buffers, capacity);
}

glt::Text glt::makeSegoeUI(size_t buffers, size_t capacity, const Shader & fragmentShader)
{
    auto bitmap = glt::BitmapFont(segoeui.data(), segoeui.size());
    return Text(bitmap, buffers, capacity, fragmentShader);
}
