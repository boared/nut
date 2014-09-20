/** 
 * \file GLVertexBuffer.h
 * \brief This class is responsible to store vertices attributes to be processed
 * by an OpenGL program.
 * 
 * Unless said the other way round, all methods in this class
 * keep the OpenGL state the same as before they are called.
 * 
 * @author: Eder A. Perez.
 */

#ifndef GLVERTEXBUFFER_H
#define GLVERTEXBUFFER_H

#include <vector>
#include <utility>
#include "GL/glew.h"



namespace nut
{
    class VertexAttribList;
    enum class Type;

    class GLVertexBuffer
    {
        public:

        /**
         * Default constructor.
         */
        GLVertexBuffer() :
            _vboName(0),
            _iboName(0),
            _vaoName(0),
            _indexCount(0),
            _stride(0)
        {
        }

        /**
         * Destructor.
         * 
         * Delete all previously allocated resources but do not change OpenGL state.
         */
        ~GLVertexBuffer()
        {
            glDeleteVertexArrays(1, &_vaoName);
            glDeleteBuffers(1, &_vboName);
            glDeleteBuffers(1, &_iboName);
        }



        /**
         * Set or reset OpenGL buffers and fill them with data.
         * 
         * Necessary buffers objects and vertex array object are created once,
         * if buffers/vertex arrays was previously created and filled, all
         * buffer's stored data will be lost and memory will be reallocated.
         * @vertexAttribList object must contain a list of indices, otherwise
         * buffer is not set.
         * 
         * @param vertexAttribList Object containing all vertices attributes.
         * This object is not stored internally and can be released after this
         * method call.
         * @param usage Provides a hint as to how the data will be read and written
         * after allocation. Valid values are GL_STREAM_DRAW, GL_STREAM_READ,
         * GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
         * GL_DYNAMIC_READ, GL_DYNAMIC_COPY.
         */
        void set(const VertexAttribList& vertexAttribList, GLenum usage);

        /**
         * Update the content of vertices. If buffer was not already created and
         * filled, nothing happens. Furthermore, the vertices in @vertexAttribList
         * should be of the same type of the current stored vertices and @offset
         * and @size must define a range lying entirely within the buffer.
         * 
         * @param vertices List containing new vertices values.
         * @param vertexSize Size in bytes of one vertex.
         * @param offset Index of the first vertex in the buffer to be updated.
         * @param size Number of vertices to be updated.
         */
        void updateVertices(const void* vertices, size_t vertexSize, size_t offset, size_t size);

        /**
         * Update the content of indices. If buffer was not already created and
         * filled, nothing happens. @offset and @size must define a range lying
         * entirely within the buffer.
         * 
         * @param indices List containing new indices values.
         * @param offset Index of the first index in the buffer to be updated.
         * @param size Number of indices to be updated.
         */
        void updateIndices(const unsigned int* indices, size_t offset, size_t size);

        /**
         * Associate an @attribute of this vertex buffer with a @variable in an
         * OpenGL program and enables this @variable using @glEnableVertexAttribArray.
         * 
         * @param attribute The index of a vertex attribute.
         * @param variable A valid index of the generic vertex attribute returned by @glGetAttribLocation.
         */
        void setAttrib(GLint attribute, GLint variable);

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
         * Return the size of the index array.
         * 
         * @return The number of elements in index array.
         */
        size_t getIndexCount()
        {
            return _indexCount;
        }



        private:

        /// Private attributes ///

        GLuint _vboName;        /**< Buffer object name for vertices properties. */
        GLuint _iboName;        /**< Buffer object name for vertices indices. */
        GLuint _vaoName;        /**< Vertex array object name. */
        GLsizei _indexCount;    /**< Number of indices. */
        GLuint _stride;         /**< Specifies the byte offset between consecutive generic vertex attributes.
                                     Actually it is the size in bytes of a vertex with all its attributes or
                                     zero if there is only one attribute (in this case the attribute is tightly packed in the array). */

        std::vector< std::pair<Type, int> > _attribSize; /**< A list containing both the type of a component and the number of
                                                              components of each vertex attribute (component values must be 1, 2,
                                                              3, or 4). The list is in the same order as the attributes in a vertex. */
        
    };
}

#endif // GLVERTEXBUFFER_H
