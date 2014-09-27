/** 
 * \file DoubleStackAllocator.h
 * \brief Class definition for memory allocation.
 * 
 * @author: Eder A. Perez.
 */

#ifndef DOUBLESTACKALLOCATOR_H
#define DOUBLESTACKALLOCATOR_H

#include <mutex>
#include "DataType.h"



namespace nut
{
    /**
     * \brief Double-ended memory stack allocator singleton.
     * 
     * Memory is allocated in this class in a huge pre-allocated double-ended stack.
     * You can use lower stack for a type of data and upper stack for another type
     * of data. This avoid fragmentation if you release only one of the data. This
     * class is best suited to allocate a bunch of resources in the beginning of
     * a level and de-allocate them at the end. If you need to allocate and
     * de-allocate resources several times while the level is running, you should
     * use another memory allocator.
     */
    class DoubleStackAllocator
    {
        public:

        /**
         * \brief Indicates which stack we are talking about.
         */
        enum STACK
        {
            LowerStack,
            UpperStack
        };

        /**
         * \brief Stack marker: Represents the current top of the stack.
         * 
         * You can only roll back to a marker, not to arbitrary locations
         * within the stack.
         */
        typedef struct
        {
            U8* marker;
            STACK stack;
        } MARKER;

        /**
         * \brief Returns an unique instance of @DoubleStackAllocator.
         * 
         * WARNING: The first time this method is called isn't thread-safe.
         * 
         * @return An unique instance of @DoubleStackAllocator.
         */
        static DoubleStackAllocator& getInstance()
        {
            static DoubleStackAllocator instance;
            return instance;
        }

        /**
         * \brief Initialize the memory buffer with an specific size (all previous
         * data will be lost).
         * 
         * The memory allocated for the buffer is fixed and can only be changed
         * by calling this method.
         * 
         * WARNING: This method is thread-safe but should be used only once in the
         * initialization step.
         * 
         * @param size Size of memory buffer, in bytes.
         * @param alignment Memory alignment, in bytes (must be a power of 2).
         * @return Return true if memory was allocated, false otherwise.
         */
        bool init(size_t size, int alignment);

        /**
         * \brief Free memory buffer and reset everything.
         * 
         * This method is thread-safe.
         */
        void release();

        /**
         * \brief Roll both stacks back to zero.
         */
        void clear();

        /**
         * \brief Rolls the @stack back to zero.
         */
        void clear(STACK stack);

        /**
         * \brief Allocates an aligned block of memory in either lower or upper stack.
         * 
         * This method is thread-safe.
         * 
         * @param size Size of memory block, in bytes.
         * @param heap Indicates in which heap the memory is supposed to be allocated (either upper or lower heap).
         * @return If success, returns a pointer to the allocated memory block. Otherwise, returns NULL.
         */
        void* alloc(size_t size, STACK stack);

        /**
         * \brief Gets a marker to the stack.
         * 
         * @return Returns a marker to the current stack top.
         */
        MARKER getMarker(STACK stack);

        /**
         * \brief Roll the stack back to a previous marker.
         * 
         * WARNING: This method should not be called by more than one thread.
         * 
         * @param A marker returned by getMarker().
         */
        void freeToMarker(MARKER marker);



        private:

        U8* _buffer;  /**< Memory buffer. */

        int _alignment; /**< Used alignment. All allocated blocks will be aligned by this value. */
        U8* _base; /**< Points the lowest aligned memory address. */
        U8* _cap;  /**< Points to the next higher-aligned memory address. */
        U8* _lower; /**< Allocates upward. */
        U8* _upper; /**< Allocates downward. */

        std::mutex _mutex; /**< Used to guarantee exclusive access. */



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
        DoubleStackAllocator() : _buffer(0), _alignment(0), _base(0), _cap(0), _lower(0), _upper(0)
        {
        }

        // Stop the compiler generating methods of copy the object
        DoubleStackAllocator(DoubleStackAllocator const&); // Don't implement.
        void operator=(DoubleStackAllocator const&); // Don't implement
	};
}
#endif // DOUBLESTACKALLOCATOR_H
