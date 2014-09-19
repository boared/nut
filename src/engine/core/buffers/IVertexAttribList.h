/** 
 * \file IVertexAttribList.h
 * \brief This interface is meant to be used for creation of classes that holds
 * a buffer with generic vertices attributes.
 * 
 * @author: Eder A. Perez.
 */

#ifndef IVERTEXATTRIBLIST_H
#define IVERTEXATTRIBLIST_H

enum class Type;



namespace nut
{
    class IVertexAttribList
    {
        public:

        virtual ~IVertexAttribList() {}

        /**
         * Get the number of attributes per vertex.
         * 
         * @return The number of attributes per vertex.
         */
        virtual int attribCount() const = 0;

        /**
         * Get the number of components an attribute has. This number must be
         * 1, 2, 3, or 4.
         * 
         * @param index The index of an attribute. It must be between zero and the
         * number of attributes - 1.
         * @return The number of components the i-th attribute has if @index is valid.
         * Otherwise returns zero.
         */
        virtual int attribComponentsCount(int index) const = 0;

        /**
         * Get the type of the i-th attribute. It's the type of its components.
         * 
         * @param index The index of an attribute. It must be between zero and the
         * number of attributes - 1.
         * @return The type of the i-th attribute if @index is valid.
         */
        virtual Type attribType(int index) const = 0;

        /**
         * Get the total number of vertices in this list.
         * 
         * @return The total number of vertices in this list.
         */
        virtual unsigned int vertexCount() const = 0;

        /**
         * Get the size in bytes of a vertex. It is the sum of the size of all
         * vertex attributes.
         * 
         * @return The size in bytes of a vertex attribute.
         */
        virtual size_t vertexSize() const = 0;

        /**
         * Get a memory block containing all vertices.
         * 
         * @return A memory block containing all vertices.
         */
        virtual const void* getBuffer() const = 0;

        /**
         * Get the total number of indices in the list of vertices indices.
         * 
         * @return The total number of indices.
         */
        virtual unsigned int indexCount() const = 0;

        /**
         * A list of indices.
         * 
         * @return A list of indices.
         */
        const unsigned int* getIndices() const = 0;
    };
}

#endif // IVERTEXATTRIBLIST_H
