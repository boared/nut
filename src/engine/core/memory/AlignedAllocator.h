/** 
 * \file AlignedAllocator.h
 * \brief Class definition for aligned memory allocation. Aligned memory blocks
 * can be allocated statically or on the heap.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef ALIGNEDALLOCATOR_H
#define ALIGNEDALLOCATOR_H

#include <cstdlib>
#include "Math.h"



namespace nut
{
    // This define is used for aligned memory declaration.
    #if defined(_MSC_VER) // Microsoft Visual C++
        /**
         * \def ALIGNED_ALLOC_DECL(type, identifier, nbytes)
         * \brief Declare a variable @identifier of type @type and @alignment bytes aligned.
         * 
         * @param type Data type.
         * @identifier Variable identifier.
         * @aligment Memory aligment (it must be a power of two).
         */
        #define ALIGNED_ALLOC_DECL(type, identifier, alignment) __declspec(align(alignment)) type identifier

    #elif defined (__GNUC__) // GNU C/C++ Compiler
	
        /**
         * \def ALIGNED_ALLOC_DECL(type, identifier, nbytes)
         * \brief Declare a variable @identifier of type @type and @alignment bytes aligned.
         * 
         * @param type Data type.
         * @identifier Variable identifier.
         * @aligment Memory aligment (it must be a power of two).
         */
        #define ALIGNED_ALLOC_DECL(type, identifier, alignment) type identifier __attribute__((__aligned__(alignment)))

    #endif



    /**
     * \brief AlignedAllocator.
     * 
     * This static class is used to dynamically allocate and de-allocate aligned
     * blocks of memory.
     */
    class AlignedAllocator
    {
        public:

        /**
         * \brief Allocate a block of memory of size @size and aligned @alignment
         * bytes.
         * 
         * It is highly recommended that all allocated block through this method be
         * freed by @AlignedAllocator::free().
         * 
         * @param size Block size in bytes.
         * @param alignment Memory alignment (it must be a power of two).
         * @return Returns an aligned memory block in case of success. Otherwise, returns a null pointer.
         */
        template<class C> static C* alloc(size_t size, size_t alignment)
        {
            void* block = 0;

            // Must be a power of two
            if (Math<size_t>::isPowerOf2(alignment))
            {
                #if defined(_MSC_VER) // Microsoft Visual C++
                    block = _aligned_malloc(size, alignment);
                #elif defined (__GNUC__) // GNU C/C++ Compiler
                    posix_memalign(&block, alignment, size);
                #endif
            }

            return static_cast<C*>(block);
        }

        /**
         * \brief Free a block of memory allocated by @AlignedAllocator::alignedAlloc().
         * 
         * @param block Memory block to be freed.
         */
        static void release(void* block)
        {
            #if defined(_MSC_VER) // Microsoft Visual C++
                _aligned_free(m);
            #elif defined (__GNUC__) // GNU C/C++ Compiler
                free(block);
            #endif
        }
	};
}
#endif // ALIGNEDALLOCATOR_H
