/** 
 * \file StackAllocator.cpp
 * \brief Class definition for memory allocation.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include "Math.h"
#include "Exception.h"
#include "StackAllocator.h"



namespace nut
{
    bool StackAllocator::init(size_t size, int alignment)
    {
        _mutex.lock();

        if (_buffer)
            delete[] _buffer;

        bool result = false;

        // Check if alignment is zero or a power of two
        if ( alignment == 0 || Math<int>::isPowerOf2(alignment) )
        {
            // Make sure @size is a multiple of alignment
            size = _alignUp(size, alignment);

            // First allocate our memory block given it room to align its first position
            // in a valid aligned address
            _buffer = new U8[size + alignment];

            if (_buffer)
            {
                _alignment = alignment;
                
                // Set up base pointer to lowest aligned memory address
                _base = (U8*) _alignUp( (IPTR)_buffer, alignment );

                // Set up cap pointer to the last memory address
                _cap = (U8*) (_alignUp( (IPTR)_buffer + size, alignment ) - 1);

                _top = _base;

                result = true;
            }
        }

        _mutex.unlock();

        return result;
    }



    void StackAllocator::release()
    {
        _mutex.lock();

        if (_buffer)
        {
            delete[] _buffer;
            _buffer = 0;
            _alignment = 0;
            _base = _cap = _top = 0;
        }

        _mutex.unlock();
    }



    void StackAllocator::clear()
    {
        _top = _base;
    }



    void* StackAllocator::alloc(size_t size)
    {
        _mutex.lock();

        U8* p = 0;

        // First, align the requested size
        size = _alignUp(size, _alignment);

        // Checks for available memory
        if ( _top + (size - 1) <= _cap )
        {
            // Allocates on the choosen heap
            p = _top;
            _top += size;
        }

        _mutex.unlock();

        return (void*)p;
    }



    StackAllocator::MARKER StackAllocator::getMarker()
    {
        return _top;
    }



    void StackAllocator::freeToMarker(MARKER marker)
    {
        NUT_ASSERT(marker <= _top && marker >= _base);

        _top = marker;
    }
}
