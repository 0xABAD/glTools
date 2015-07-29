#include <glt/geometry.hpp>

namespace glt {

void loadGeometry(const Geometry& geometry, GLuint vbo, GLuint ibo)
{
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ibo);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, 
                   geometry.indices.size() * sizeof(GLuint), 
                   geometry.indices.data(), 
                   gl::STATIC_DRAW);

    auto vtxSz   = sizeof(GLfloat) * geometry.vertices.size();
    auto normSz  = sizeof(GLfloat) * geometry.normals.size();
    auto tcSz    = sizeof(GLfloat) * geometry.texCoords.size();
    auto arrSize = vtxSz + normSz + tcSz;

    gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
    gl::BufferData(gl::ARRAY_BUFFER, arrSize, nullptr, gl::STATIC_DRAW);
    gl::BufferSubData(gl::ARRAY_BUFFER, 0,              vtxSz,  geometry.vertices.data());
    gl::BufferSubData(gl::ARRAY_BUFFER, vtxSz,          normSz, geometry.normals.data());
    gl::BufferSubData(gl::ARRAY_BUFFER, vtxSz + normSz, tcSz,   geometry.texCoords.data());
}

void setupAttributes(const Geometry& geometry, GLuint pos1, GLuint pos2, GLuint pos3)
{
    auto normalOffset   = geometry.vertices.size() * sizeof(GLfloat);
    auto texCoordOffset = normalOffset + (geometry.normals.size()  * sizeof(GLfloat));

    gl::VertexAttribPointer(pos1, 3, gl::FLOAT, false, 0, nullptr);
    gl::VertexAttribPointer(pos2, 3, gl::FLOAT, false, 0, (void*)normalOffset);
    gl::VertexAttribPointer(pos3, 2, gl::FLOAT, false, 0, (void*)texCoordOffset);
    gl::EnableVertexAttribArray(pos1);
    gl::EnableVertexAttribArray(pos2);
    gl::EnableVertexAttribArray(pos3);
}

Geometry makePlane(float width, float height)
{
    Geometry result;

    auto xStart = -width  / 2;
    auto yStart = -height / 2;

    result.indices   = { 0, 1, 2, 0, 2, 3 };
    result.vertices  = { xStart,         yStart,          0,
                         xStart + width, yStart,          0,
                         xStart + width, yStart + height, 0,
                         xStart,         yStart + height, 0 };
    result.normals   = { 0, 0, 1,
                         0, 0, 1,
                         0, 0, 1,
                         0, 0, 1, };
    result.texCoords = { 0, 0,
                         1, 0,
                         1, 1,
                         0, 1 };

    return result;
}

Geometry makeBox(float width, float height, float depth)
{
    Geometry result;

    auto x1 = -width  / 2;
    auto x2 = x1 + width;
    auto y1 = -height / 2;
    auto y2 = y1 + height;
    auto z1 = depth / 2;
    auto z2 = z1 - depth;

    result.vertices = {
        x1, y1, z1,     // front face
        x2, y1, z1,
        x2, y2, z1,
        x1, y2, z1,

        x2, y2, z2,     // back face
        x2, y1, z2,
        x1, y1, z2,
        x1, y2, z2,

        x1, y1, z1,     // left face
        x1, y2, z1,
        x1, y2, z2,
        x1, y1, z2,

        x2, y1, z1,     // right face
        x2, y1, z2,
        x2, y2, z2,
        x2, y2, z1,

        x1, y1, z1,     // bottom face
        x1, y1, z2,
        x2, y1, z2,
        x2, y1, z1,

        x1, y2, z1,     // top face
        x2, y2, z1,
        x2, y2, z2,
        x1, y2, z2,
    };

    result.texCoords = {
        0,0,   1,0,   1,1,   0,1,   // front
        0,1,   0,0,   1,0,   1,1,   // back
        1,0,   1,1,   0,1,   0,0,   // left
        0,0,   1,0,   1,1,   0,1,   // right
        0,1,   0,0,   1,0,   1,1,   // bottom
        0,0,   1,0,   1,1,   0,1    // top
    };

    result.indices = {
         0,  1,  2,  2,  3,  0,     // front face
         4,  5,  6,  6,  7,  4,     // back face
         8,  9, 10, 10, 11,  8,     // left face
        12, 13, 14, 14, 15, 12,     // right face
        16, 17, 18, 18, 19, 16,     // bottom face
        20, 21, 22, 22, 23, 20      // top face
    };

    result.normals = {
         0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
         0, 0,-1,    0, 0,-1,    0, 0,-1,    0, 0,-1,
        -1, 0, 0,   -1, 0, 0,   -1, 0, 0,   -1, 0, 0,
         1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
         0,-1, 0,    0,-1, 0,    0,-1, 0,    0,-1, 0 ,
         0, 1, 0,    0, 1, 0,    0, 1, 0,    0, 1, 0
    };

    return result;
}

} // end namespace glt
