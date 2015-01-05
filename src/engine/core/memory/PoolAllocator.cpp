/** 
 * \file PoolAllocator.cpp
 * \brief Class definition for memory allocation.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include "Math.h"
#include "Exception.h"
#include "PoolAllocator.h"



namespace nut
{
    const int PoolAllocator::_sizeofU8ptr = sizeof(U8*);

    

    bool PoolAllocator::init(size_t size, int alignment, size_t blockSize)
    {
        _mutex.lock();

        bool result = false;

        if (blockSize > size)
            return result;

        delete[] _buffer;

        // Check if alignment is zero or a power of two
        if ( alignment == 0 || Math<int>::isPowerOf2(alignment) )
        {
            // Adjust block size to hold pointers to next and previous
            // free memory blocks and to be a multiple of alignment
            unsigned int fullBlockSize = blockSize + 2 * _sizeofU8ptr;
            if (alignment > 0 && fullBlockSize % alignment > 0)
            {
                fullBlockSize = fullBlockSize + (alignment - fullBlockSize % alignment);
            }

            // Adjust memory size to contain an integer number of unit blocks
            if (size % fullBlockSize > 0)
            {
                size = size + fullBlockSize - size % fullBlockSize;
            }

            unsigned int blockCount = size / fullBlockSize;

            // Make sure @size is a multiple of alignment
            size = _alignUp(size, alignment);

            // First allocate our memory block given it room to align its first position
            // in a valid aligned address
            _buffer = new U8[size + alignment];

            if (_buffer)
            {
                _alignment = alignment;
                _blockSize = fullBlockSize -  2 * _sizeofU8ptr;

                _firstBlock = (U8*) _alignUp((IPTR)_buffer, alignment);
                _lastBlock  = _firstBlock + (blockCount - 1) * fullBlockSize;
                _freeBlock = _firstBlock;

                // Set previous/next for first and last blocks
                _firstBlock[_blockSize] = (IPTR)_lastBlock;
                _firstBlock[_blockSize + _sizeofU8ptr] = (IPTR)(_firstBlock + fullBlockSize);

                _lastBlock[_blockSize] = (IPTR)(_lastBlock - fullBlockSize);
                _lastBlock[_blockSize + _sizeofU8ptr] = (IPTR)_firstBlock;

                // Set previous/next for the other
                for (unsigned int i = 1; i < blockCount - 1; ++i)
                {
                    U8* block = _firstBlock + i * fullBlockSize;

                    // Set previous free block
                    block[_blockSize] = (IPTR)(block - fullBlockSize);

                    // Set next free block
                    block[_blockSize + _sizeofU8ptr] = (IPTR)(block + fullBlockSize);
                }

                result = true;
            }
        }

        _mutex.unlock();

        return result;
    }



    void PoolAllocator::release()
    {
        _mutex.lock();

        if (_buffer)
        {
            delete[] _buffer;
            _buffer = 0;
            _alignment  = 0;
            _blockSize  = 0;
            _firstBlock = _lastBlock  = 0;
            _freeBlock  = _allocatedBlock = 0;
        }

        _mutex.unlock();
    }



    void PoolAllocator::clear()
    {
        while (_allocatedBlock)
        {
            free(_allocatedBlock);
        }
    }



    void* PoolAllocator::alloc()
    {
        _mutex.lock();

        U8* p = 0;

        if (_freeBlock)
        {
            p = _freeBlock;

            // Sets _freeBlock to next free block
            _freeBlock = (U8*)(_freeBlock + _blockSize + _sizeofU8ptr);

            if (_freeBlock)
            {
                // Sets previous of current _freeBlock to NULL
                _freeBlock[_blockSize] = 0;
            }

            // Sets next of current allocated block to the last allocated block
            p[_blockSize + _sizeofU8ptr] = (IPTR)_allocatedBlock;

            if (_allocatedBlock)
            {
                // Sets previous of last allocated block to the current allocated block
                _allocatedBlock[_blockSize] = (IPTR)p;
            }

            // Update current allocated block
            _allocatedBlock = p;
        }

        _mutex.unlock();

        return (void*)p;
    }



    void PoolAllocator::free(void* p)
    {
        _mutex.lock();

        U8* ptr = (U8*)p;

        if (ptr >= _firstBlock && ptr <= _lastBlock)
        {
            // Updates the current allocated block
            _allocatedBlock = (U8*)(ptr + _blockSize + _sizeofU8ptr);

            if (_allocatedBlock)
            {
                // Sets the previous allocated block to NULL
                _allocatedBlock[_blockSize] = 0;
            }

            // Sets the next-pointer of the new free block to the current free block
            ptr[_blockSize + _sizeofU8ptr] = (IPTR)_freeBlock;

            if (_freeBlock)
            {
                // Sets the previous-pointer of the current free block to the new free block
                _freeBlock[_blockSize] = (IPTR)ptr;
            }

            // Updates the free memory blocks list
            _freeBlock = ptr;
        }

        _mutex.unlock();
    }
}
