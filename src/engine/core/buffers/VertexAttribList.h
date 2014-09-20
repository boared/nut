/** 
 * \file VertexAttribList.h
 * \brief This class is used for holds a buffer with generic vertices attributes.
 * 
 * @author: Eder A. Perez.
 */

#ifndef VERTEXATTRIBLIST_H
#define VERTEXATTRIBLIST_H

#include <cstring>
#include "DataType.h"



namespace nut
{
    class VertexAttribList
    {
        public:

        VertexAttribList() : _buffer(0), _bufferSize(0), _indices(0), _indexCount(0), _vertexCount(0), _vertexSize(0)
        {
        }

        ~VertexAttribList()
        {
            delete[] _buffer;
            delete[] _indices;
        }

        /**
         * Get the number of attributes per vertex.
         * 
         * @return The number of attributes per vertex.
         */
        int attribCount() const
        {
            return _attributesInfo.size();
        }

        /**
         * Get the number of components an attribute has. This number must be
         * 1, 2, 3, or 4.
         * 
         * @param index The index of an attribute. It must be between zero and the
         * number of attributes - 1.
         * @return The number of components the i-th attribute has if @index is valid.
         * Otherwise returns zero.
         */
        int attribComponentsCount(int index) const
        {
            if (index >= 0 && index < static_cast<int>(_attributesInfo.size()))
            {
                return _attributesInfo[index].second;
            }
            
            return 0;
        }

        /**
         * Get the type of the i-th attribute. It's the type of its components.
         * 
         * @param index The index of an attribute. It must be between zero and the
         * number of attributes - 1.
         * @return The type of the i-th attribute if @index is valid. Otherwise,
         * returns Type::UNKNOW.
         */
        Type attribType(int index) const
        {
            if (index >= 0 && index < static_cast<int>(_attributesInfo.size()))
            {
                return _attributesInfo[index].first;
            }

            return Type::UNKNOW;
        }

        /**
         * Get the total number of vertices in this list.
         * 
         * @return The total number of vertices in this list.
         */
        unsigned int vertexCount() const
        {
            return _vertexCount;
        }

        /**
         * Get the size in bytes of a vertex. It is the sum of the size of all
         * vertex attributes.
         * 
         * @return The size in bytes of a vertex attribute.
         */
        size_t vertexSize() const
        {
            return _vertexSize;
        }

        /**
         * Get a memory block containing all vertices.
         * 
         * @return A memory block containing all vertices.
         */
        const void* getBuffer() const
        {
            return _buffer;
        }

        /**
         * Get the total number of indices in the list of vertices indices.
         * 
         * @return The total number of indices.
         */
        unsigned int indexCount() const
        {
            return _indexCount;
        }

        /**
         * A list of indices.
         * 
         * @return A list of indices.
         */
        unsigned int* getIndices() const
        {
            return _indices;
        }
        
        /**
         * Allocate a buffer of size @size and fill with @buffer's content. If
         * a buffer was previously allocated, all its content is lost. If buffer
         * is NULL, nothing happens.
         * 
         * @param buffer A block of memory with data.
         * @param size The size in bytes of @buffer.
         */
        void setBufffer(const void* buffer, size_t size)
        {
            if (buffer)
            {
                delete[] _buffer;

                _buffer = new I8[size];
                _bufferSize = size;

                memcpy(_buffer, buffer, size);
            }
        }

        /**
         * Allocate a array of size @size and fill with @indices's content. If
         * a buffer was previously allocated, all its content is lost.
         * 
         * @param indices An array containing indices of vertices.
         * @param size The number of elements of @indices.
         */
        void setIndices(const unsigned int* indices, size_t size)
        {
            if (indices)
            {
                delete[] _indices;

                _indices = new unsigned int[size];
                _indexCount = size;

                memcpy(_indices, indices, sizeof(unsigned int)*size);
            }
        }
        
        /**
         * Informs that vertices have a new attribute. If components is not 1, 2,
         * 3, or 4, the attribute is not added. This method have to called for
         * each attribute and in the same order they appear in the vertex array.
         * 
         * @param components Number of components of the attribute (must be 1, 2, 3 or 4).
         * @param type The type of a component.
         */
        void addAttrib(int components, Type type)
        {
            if (components > 0 && components <= 4)
            {
                _attributesInfo.push_back( std::pair<Type, int>(type, components) );

                // Update vertex size and vertex count
                _vertexSize += components * DataType::getSize(type);
                _vertexCount = _bufferSize / _vertexSize;
            }
        }



        private:

        I8* _buffer;                /**< Store the vertices. */
        size_t _bufferSize;         /**< Size of @_buffer in bytes. */
        unsigned int* _indices;     /**< Store the triangulation. */
        unsigned int _indexCount;   /**< Number of elements in @_indices. */
        unsigned int _vertexCount;  /**< Store the total amount of vertices. */
        size_t _vertexSize;         /**< Size of a single vertex in bytes. */
        std::vector< std::pair<Type, int> > _attributesInfo; /**< Information about added attributes (type of components and number of them). */
    };
}

#endif // VERTEXATTRIBLIST_H
