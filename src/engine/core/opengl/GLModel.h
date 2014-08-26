/** 
 * \file GLModel.h
 * \brief This class loads model data to be processed by OpenGL.
 * 
 * @author: Eder A. Perez.
 */

#ifndef GLMODEL_H
#define GLMODEL_H

#include <vector>
#include "GL/glew.h"



namespace nut
{
    class GLModel
    {
        public:

        /// Constructors ///

        /**
         * Default constructor.
         */
        GLModel() : _vboName(0),
                    _iboName(0),
                    _vaoName(0),
                    _indicesSize(0),
                    _stride(0)
        {
        }

        /**
         * Constructor.
         *
         * This constructor loads data for vertices and triangle indices in a
         * OpenGL's buffer. A vertex may contain information about position,
         * color, normal, texture coordinates and so on.
         * 
         * @param indices Indices of triangles.
         * @param vertices List of model's vertices.
         * @param size A list containing the number of components of each vertex
         * attribute (must be 1, 2, 3, or 4).
         * @param usage Provides a hint as to how the data will be read and written
         * after allocation. Valid values are GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
         * GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ,
         * GL_DYNAMIC_COPY.
         */
        GLModel(const std::vector<GLuint>& indices,
                const std::vector<GLfloat>& vertices,
                const std::vector<GLint>& size, GLenum usage) :
            _vboName(0),
            _iboName(0),
            _vaoName(0),
            _indicesSize(0),
            _stride(0)
        {
            setModel(indices, vertices, size, usage);
        }

        /**
         * Destructor.
         * 
         * Release all previously allocated resources.
         */
        ~GLModel()
        {
            glDeleteVertexArrays(1, &_vaoName);
            glDeleteBuffers(1, &_vboName);
            glDeleteBuffers(1, &_iboName);
        }



        /// Methods ///

        /**
         * Create or reset buffers and vertex arrays in OpenGL and fill with data.
         * 
         * Necessary buffers and vertex arrays are created once, if buffers/vertex
         * arrays was previously created and filled, all data will be lost. The
         * data refers to vertices and triangle indices. A vertex may contain
         * information about position, color, normal, texture coordinates and so on.
         * 
         * @param indices Indices of triangles.
         * @param vertices List of model's vertices.
         * @param size A list containing the number of components of each vertex
         * attribute (values must be 1, 2, 3, or 4). The list is in the same order
         * as the attribute in a vertex.
         * @param usage Provides a hint as to how the data will be read and written
         * after allocation. Valid values are GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
         * GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ,
         * GL_DYNAMIC_COPY.
         */
        void setModel(const std::vector<GLuint>& indices,
                      const std::vector<GLfloat>& vertices,
                      const std::vector<GLint>& size, GLenum usage);

        /**
         * Update the content of vertices.
         * 
         * @param vertices List containing new vertices values.
         * @param offset Index of the first vertex to be updated.
         * @param size Number of vertices to be updated.
         */
        void updateVertices(const std::vector<GLfloat>* vertices, size_t offset, size_t size);

        /**
         * Update the content of indices.
         * 
         * @param indices List containing new indices values.
         * @param offset Index of the first index to be updated.
         * @param size Number of indices to be updated.
         */
        void updateIndices(const std::vector<GLuint>* indices, size_t offset, size_t size);

        /**
         * Return the vertex buffer object name.
         * 
         * @return A GLuint representing the vertex buffer object name.
         */
        GLuint getVBO()
        {
            return _vboName;
        }

        /**
         * Return the vertex array object name.
         * 
         * @return A GLuint representing the vertex array object name.
         */
        GLuint getVAO()
        {
            return _vaoName;
        }

        /**
         * Return the index buffer object name.
         * 
         * @return A GLuint representing the index buffer object name.
         */
        GLuint getIBO()
        {
            return _iboName;
        }

        /**
         * Associate an attribute of the vertices array with a variable in an
         * OpenGL program.
         * 
         * @param attribute The index of a vertex attribute.
         * @param program A valid OpenGL program.
         * @param name The name of an existing variable in @program.
         */
        void setAttrib(GLint attribute, GLuint program, const GLchar* name);

        /**
         * Draw the model calling @glDrawArrays.
         * 
         * @param mode Specifies what kind of primitives are constructed and is one
         * of GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES,
         * GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, and GL_PATCHES.
         */
        void draw(GLenum mode);



        private:

        /// Private attributes ///

        GLuint _vboName;                /**< Buffer object name for vertices properties. */
        GLuint _iboName;                /**< Buffer object name for vertices indices. */
        GLuint _vaoName;                /**< Vertex array object name. */
        GLsizei _indicesSize;           /**< Number of indices. */
        GLuint _stride;                 /**< Specifies the byte offset between consecutive generic vertex attributes. */
        std::vector<GLint> _attribSize; /**< A list containing the number of components of each vertex attribute
                                             (values must be 1, 2, 3, or 4). The list is in the same order
                                             as the attributes in a vertex. */
    };
}

#endif // GLMODEL_H
