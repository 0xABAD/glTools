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

} // end namespace glt
