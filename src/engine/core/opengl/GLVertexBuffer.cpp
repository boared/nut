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

#include "GLVertexBuffer.h"
#include "IVertexAttribList.h"
#include "GLTypeConversion.h"



namespace nut
{
    void GLVertexBuffer::set(const IVertexAttribList* vertexAttribList, GLenum usage)
    {
        if (vertexAttribList && vertexAttribList->indexCount() > 0)
        {
            // Generate OpenGL object names if necessary
            if (_vaoName == 0)
                glGenVertexArrays(1, &_vaoName);

            if (_vboName == 0)
                glGenBuffers(1, &_vboName);

            if (_iboName == 0)
                glGenBuffers(1, &_iboName);

            _indicesCount = vertexAttribList->indexCount();
            
            int attribCount = vertexAttribList->attribCount();

            _attribSize.clear();
            _attribSize.reserve(attribCount);

            // Compute the offset between consecutive vertices
            // If there is more than one attribute, the stride is computed based on
            // the number of components of each attribute.
            if (attribCount > 1)
            {
                _stride = vertexAttribList->vertexSize();

                for (unsigned int i = 0; i < attribCount; ++i)
                {
                    _attribSize.push_back(vertexAttribList->attribComponentsCount(i));
                }
            }
            // If there is only one attribute the stride is understood to be zero,
            // because in this case attributes are tightly packed in array.
            else
            {
                _stride = 0;
                _attribSize.push_back(vertexAttribList->attribComponentsCount(0));
            }

            // Get current bound buffer to re-bind it later
            GLint boundVAO, boundVBO, boundIBO;
            glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
            glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
            glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &boundIBO);

            glBindVertexArray(_vaoName);

            // Initialize and fill vertex buffer object with vertices
            glBindBuffer(GL_ARRAY_BUFFER, _vboName);
            glBufferData(GL_ARRAY_BUFFER,  vertexAttribList->vertexSize() * vertexAttribList->vertexCount(), vertexAttribList->getBuffer(), usage);

            // Initialize and fill index buffer object with indices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboName);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indicesCount, vertexAttribList->getIndices(), usage);

            // Re-bind last bound object
            glBindVertexArray(boundVAO);
            glBindBuffer(GL_ARRAY_BUFFER, boundVBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIBO);
        }
    }



    void GLVertexBuffer::updateVertices(const void* vertices, size_t vertexSize, size_t offset, size_t size)
    {
        if (vertices && _vaoName != 0)
        {
            // Get current bound buffer to re-bind it later
            GLint boundVAO;
            glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
            if (boundVAO != static_cast<GLint>(_vaoName))
                glBindVertexArray(_vaoName);

            // Update vertex buffer
            GLintptr off = offset * vertexSize;
            glBufferSubData(GL_ARRAY_BUFFER, off, size * vertexSize, vertices);

            // Re-bind last bound object
            if (boundVAO != static_cast<GLint>(_vaoName))
                glBindVertexArray(boundVAO);
        }
    }



    void GLVertexBuffer::updateIndices(const unsigned int* indices, size_t offset, size_t size)
    {
        if (indices && _vaoName != 0)
        {
            // Get current bound buffer to re-bind it later
            GLint boundVAO;
            glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
            if (boundVAO != static_cast<GLint>(_vaoName))
                glBindVertexArray(_vaoName);

            // Update index buffer
            GLintptr off = offset * sizeof(unsigned int);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, off, sizeof(unsigned int) * size, indices);

            // Re-bind last bound object
            if (boundVAO != static_cast<GLint>(_vaoName))
                glBindVertexArray(boundVAO);
        }
    }



    void GLVertexBuffer::setAttrib(GLint attribute, GLint variable)
    {
        if (variable != -1 && attribute >= 0 && attribute < static_cast<GLint>(_attribSize.size()))
        {
            GLuint components = _attribSize[attribute].second;
            GLsizeiptr offset = 0;

            // Compute the offset of the first attribute of the first vertex
            // in the vertex buffer
            for (int i = 0; i < attribute; ++i)
            {
                size_t size = DataType::getSize(_attribSize[i].first);
                offset += size * _attribSize[i].second;
            }

            GLenum type = GLTypeConversion::typeToGLenum(_attribSize[attribute].first);

            // Get current bound buffer to re-bind it later
            GLint boundVAO, boundVBO, boundIBO;
            glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
            glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
            glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER, &boundIBO);

            // Bind buffers from this object
            if ( boundVAO != static_cast<GLint>(_vaoName) ||
                 boundVBO != static_cast<GLint>(_vboName) ||
                 boundIBO != static_cast<GLint>(_iboName) )
            {
                glBindVertexArray(_vaoName);
                glBindBuffer(GL_ARRAY_BUFFER, _vboName);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboName);
            }

            glVertexAttribPointer(variable, components, type, GL_FALSE, _stride, (const void*)(offset) );
            glEnableVertexAttribArray(variable);

            // Re-bind last bound object
            if ( boundVAO != static_cast<GLint>(_vaoName) ||
                 boundVBO != static_cast<GLint>(_vboName) ||
                 boundIBO != static_cast<GLint>(_iboName) )
            {
                glBindVertexArray(boundVAO);
                glBindBuffer(GL_ARRAY_BUFFER, boundVBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIBO);
            }
        }
    }
}
