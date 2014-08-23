/** 
 * \file GLModel.cpp
 * \brief This class loads model data to be processed by OpenGL.
 * 
 * @author: Eder A. Perez.
 */

#include "GLModel.h"



namespace nut
{
    void GLModel::setModel(const std::vector<GLuint>& indices,
                           const std::vector<GLfloat>& vertices,
                           const std::vector<GLint>& size, GLenum usage)
    {
        // Check parameters
        if (indices.size() == 0 || vertices.size() == 0)
            return;

        // Generate OpenGL object names if necessary
        if (_vaoName == 0)
            glGenVertexArrays(1, &_vaoName);

        if (_vboName == 0)
            glGenBuffers(1, &_vboName);

        if (_iboName == 0)
            glGenBuffers(1, &_iboName);

        _indicesSize = indices.size();

        // Set stride and attributes size

        // If there is only one attribute the stride is understood to be zero,
        // because in this case attributes are tightly packed in array.
        _stride = 0;
        _attribSize.clear();
        _attribSize.reserve(size.size());

        // If there is more than one attribute, the stride is computed based on
        // the number of components of each attribute.
        if (size.size() > 1)
        {
            for (unsigned int i = 0; i < size.size(); ++i)
            {
                _stride += size[i] * sizeof(GLfloat);
                _attribSize.push_back(size[i]);
            }
        }
        else
        {
            _attribSize.push_back(size[0]);
        }

        // Get current bound buffer to re-bind it later
        GLint boundVAO, boundVBO, boundIBO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &boundIBO);

        glBindVertexArray(_vaoName);

        // Initialize and fill vertex buffer object with vertices
        glBindBuffer(GL_ARRAY_BUFFER, _vboName);
        glBufferData(GL_ARRAY_BUFFER,  sizeof(GLfloat) * vertices.size(), &vertices[0], usage);

        // Initialize and fill index buffer object with indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboName);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], usage);

        // Re-bind last bound object
        glBindVertexArray(boundVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIBO);
        glBindBuffer(GL_ARRAY_BUFFER, boundVBO);
    }



    void GLModel::updateVertices(const std::vector<GLfloat>* vertices, size_t offset, size_t size)
    {
        // Check parameters
        if (vertices == 0 || _vaoName == 0)
            return;

        // Get current bound buffer to re-bind it later
        GLint boundVAO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
        if (boundVAO != static_cast<GLint>(_vaoName))
            glBindVertexArray(_vaoName);

        // Update vertex buffer
        GLintptr off = offset * sizeof(GLfloat);
        glBufferSubData(GL_ARRAY_BUFFER, off, size * sizeof(GLfloat), vertices);

        // Re-bind last bound object
        if (boundVAO != static_cast<GLint>(_vaoName))
            glBindVertexArray(boundVAO);
    }



    void GLModel::updateIndices(const std::vector<GLuint>* indices, size_t offset, size_t size)
    {
        // Check parameters
        if (indices == 0 || _vaoName == 0)
            return;

        // Get current bound buffer to re-bind it later
        GLint boundVAO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);
        if (boundVAO != static_cast<GLint>(_vaoName))
            glBindVertexArray(_vaoName);

        // Update index buffer
        GLintptr off = offset * sizeof(GLuint);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, off, sizeof(GLuint) * size, indices);

        // Re-bind last bound object
        if (boundVAO != static_cast<GLint>(_vaoName))
            glBindVertexArray(boundVAO);
    }



    void GLModel::setAttrib(GLint attribute, GLuint program, const GLchar* name)
    {
        if (attribute >= 0 && attribute < static_cast<GLint>(_attribSize.size()))
        {
            GLuint components = _attribSize[attribute];
            GLsizeiptr offset = 0;

            // Compute the offset of the first attribute of the first vertex
            // in the vertex buffer
            for (int i = 0; i < attribute; ++i)
            {
                offset += sizeof(GLfloat) * _attribSize[i];
            }

            GLint dataLocation = glGetAttribLocation(program, name);

            if (dataLocation != -1)
            {
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

                glVertexAttribPointer(dataLocation, components, GL_FLOAT, GL_FALSE, _stride, (const void*)(offset) );
                glEnableVertexAttribArray(dataLocation);

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



    void GLModel::draw(GLenum mode)
    {
        // Get current bound VAO to re-bind it later
        GLint boundVAO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVAO);

        if (boundVAO != static_cast<GLint>(_vaoName))
        {
            glBindVertexArray(_vaoName);
        }

        glDrawElements(mode, _indicesSize, GL_UNSIGNED_INT, (const void*)0);

        // Re-bind last VAO
        if (boundVAO != static_cast<GLint>(_vaoName))
        {
            glBindVertexArray(boundVAO);
        }
    }
}
