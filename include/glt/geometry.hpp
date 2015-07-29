#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

#include <vector>
#include <glt/api.hpp>
#include <glt/gl.hpp>

namespace glt {

struct Geometry {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<GLuint>  indices;
};

/**
 * Loads geometry onto GPU memory where the geometry itself will be bound
 * to vbo in the array buffer and the indices will be bound to ibo in the
 * element array buffer.  The geometry data is not interleaved, instead the
 * array buffer will contain all the vertex data, then the normal data,
 * and then the texture coordinate data.
 *
 * @param geometry  The geometry to load into GPU memory.
 * @param vbo       Vertex buffer object id of where vertex, normal, and texture
 *                  data is bound to in the array buffer.
 * @param ibo       Vertex buffer object id of where the geometry index data 
 *                  will be bound to.
 */
GLT_API void loadGeometry(const Geometry& geometry, GLuint vbo, GLuint ibo);

/**
 * Sets up the vertex attributes for geometry to the attribute positions
 * pos1, pos2, and pos3 locations of the vertex shader.  This assumes
 * that the vertex position is at location pos1 in the vertex shader,
 * that the normal is at location pos2, and the texture coordinate is at
 * location pos3.
 *
 * @param geometry  Geometry data.
 * @param pos1      Location of the vertex position in the vertex shader.
 *                  Default is 0.
 * @param pos2      Location of the normal in the vertex shader.
 *                  Default is 1.
 * @param pos3      Location of the texture coordiante in the vertex shader.
 *                  Default is 2.
 *
 * @example
 *
 *      auto vao   = glt::VertexArray(1);
 *      auto vbo   = glt::VertexBuffer(2);
 *      auto plane = glt::makePlane(1.0f, 1.0f);

 *      gl::BindVertexArray(vao[0]);
 *      glt::loadGeometry(plane, vbo[0], vbo[1]);
 *      glt::setupAttributes(plane);                // using default locations.
 *      gl::BindVertexArray(0);
 *
 * // Assume our vertex shader starts like this:
 *      #version 450
 *
 *      layout (location = 0) in vec3 VertexPosition;
 *      layout (location = 1) in vec3 VertexNormal;
 *      layout (location = 2) in vec3 TextureCoordinate;
 *
 *      ...
 *
 */
GLT_API void setupAttributes(const Geometry& geometry, GLuint pos1 = 0, GLuint pos2 = 1, GLuint pos3 = 2);

/**
 * Creates a geometrical plane of width and height.  The plane, and its 
 * normals, will be facing the positive z-axis in a right handed
 * coordinate system.  The plane will be centered at the origin.
 *
 * @param width    Width of the plane.
 * @param heigth   Height of the plane.
 *
 * @returns   A Geometrical plane.
 */
GLT_API Geometry makePlane(float width, float height);

/**
 * Creates a geometry that forms a box.  The geometry will normals
 * that face outward of each face.
 *
 * @param width   Width of the box.
 * @param height  Height of the box.
 * @param depth   Depth of the box.
 *
 * @returns  A box geometry.
 */
GLT_API Geometry makeBox(float width, float height, float depth);

} // end namespace glt

#endif // __GEOMETRY_HPP__
