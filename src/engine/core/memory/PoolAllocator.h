/** 
 * \file PoolAllocator.h
 * \brief Class definition for memory allocation.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __POOLALLOCATOR_H__
#define __POOLALLOCATOR_H__

#include <mutex>



namespace nut
{
    /**
     * \brief Memory pool allocator singleton.
     * 
     * The memory buffer is a double-linked list. Each memory block points to both
     * next and previoius free memory block.
     * 
     * Below is an example of a block of memory with its metadata:
     * 
     *             ____________________________
     *            | MEMORY BLOCK | PREV | NEXT |
     * 
     * MEMORY BLOCK: Fixed sized block of memory to be allocated.
     * PREV: If the memory block is not allocated, points to the previous free memory
     *       block. Otherwise, points to the previous allocated memory block.
     * NEXT: If the memory block is not allocated, points to the next free memory
     *       block. Otherwise, points to the next allocated memory block.
     */
    class PoolAllocator
    {
        public:

        /**
         * \brief Return an unique instance of @PoolAllocator.
         * 
         * WARNING: The first time this function is called isn't thread-safe.
         * 
         * @return An unique instance of @PoolAllocator.
	     */
        inline static PoolAllocator& getInstance()
        {
            static PoolAllocator instance;
            return instance;
        }

        /**
         * \brief Initialize the memory buffer with an specific size (all previous
         * data will be lost).
         * 
         * The memory allocated for the buffer is fixed and can only be changed by calling
         * this function.
         * 
         * WARNING: This function is thread-safe but should be used only once in the
         * initialization step.
         * 
         * @param size Size of memory buffer, in bytes.
         * @param alignment Memory alignment, in bytes (must be a power of 2).
         * @param blockSize Size in bytes any allocated memory block will have.
         * @return Return true if memory was allocated, false otherwise.
         */
        bool init(size_t size, int alignment, size_t blockSize);

        /**
         * \brief Free memory buffer and reset everything.
         */
        void release();

        /**
         * \brief Free all blocks of memory.
         */
        void clear();

        /**
         * \brief Allocates a block of memory.
         * 
         * @return An allocated fixed-sized block of memory.
         */
        void* alloc();

        /**
         * \brief Free a block of memory.
         * 
         * @param p A pointer to a block allocated by @PoolAllocator.
         */
        void free(void* p);



        private:

        U8* _buffer;  /**< Memory buffer. */

        int _alignment;       /**< Used alignment. All allocated blocks will be aligned by @_alignment bytes. */
        int _blockSize;       /**< Size in bytes of an allocated memory block. */
        U8* _firstBlock;      /**< First buffer memory block. */
        U8* _lastBlock;       /**< Last buffer memory block. */
        U8* _freeBlock;       /**< Points to a double-linked list of free memory blocks. */
        U8* _allocatedBlock;  /**< Points to a double-linked list of allocated memory blocks. */

        std::mutex _mutex; /**< Used to guarantee exclusive access. */
        
        static const int _sizeofU8ptr; /**< Size of a U8 pointer. */



        /**
         * \brief Return the next memory address aligned by @alignment bytes.
         * 
         * @param address Memory address.
         * @param alignment Must be a power of two.
         * @return Next address, with alignment @alignment, before @address.
         */
        IPTR _alignUp(IPTR address, IPTR alignment)
        {
            if (alignment == 0)
            {
                return address;
            }
            else
            {
                return (address + alignment - 1) & ~(alignment - 1);
            }
        }

        /**
         * \brief Constructor.
         */
        PoolAllocator() : _buffer(0), _alignment(0), _blockSize(0), _firstBlock(0),
                          _lastBlock(0), _freeBlock(0), _allocatedBlock(0)
        {
        }

        // Stop the compiler generating methods of copy the object
        PoolAllocator(PoolAllocator const&);  // Don't implement.
        void operator=(PoolAllocator const&); // Don't implement
	};
}
#endif // __POOLALLOCATOR_H__
