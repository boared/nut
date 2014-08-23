/** 
 * \file DoubleStackAllocator.cpp
 * \brief Class definition for memory allocation.
 * 
 * @author: Eder A. Perez.
 */

#include "Math.h"
#include "Exception.h"
#include "DoubleStackAllocator.h"



namespace nut
{
    bool DoubleStackAllocator::init(size_t size, int alignment)
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

                // Set up cap pointer to the next higher-aligned memory address.
                _cap = (U8*) _alignUp( (IPTR)_buffer + size, alignment );

                _lower = _base;
                _upper = _cap;

                result = true;
            }
        }

        _mutex.unlock();

        return result;
    }



    void DoubleStackAllocator::release()
    {
        _mutex.lock();

        if (_buffer)
        {
            delete[] _buffer;
            _buffer = 0;
            _alignment = 0;
            _base = _cap = _lower = _upper = 0;
        }

        _mutex.unlock();
    }



    void DoubleStackAllocator::clear()
    {
        _lower = _base;
        _upper = _cap;
    }



    void DoubleStackAllocator::clear(STACK stack)
    {
        switch (stack)
        {
            case LowerStack:
                _lower = _base;
                break;

            case UpperStack:
                _upper = _cap;
                break;

            default:
                break;
        }
    }



    void* DoubleStackAllocator::alloc(size_t size, STACK stack)
    {
        _mutex.lock();

        U8* p = 0;

        // First, align the requested size
        size = _alignUp(size, _alignment);

        // Checks for available memory
        if ( _lower + size <= _upper )
        {
            // Allocates on the choosen heap
            switch (stack)
            {
                case LowerStack:
                    p = _lower;
                    _lower += size;
                    break;
                
                case UpperStack:
                    _upper -= size;
                    p = _upper;
                    break;
            }
        }

        _mutex.unlock();

        return (void*)p;
    }



    DoubleStackAllocator::MARKER DoubleStackAllocator::getMarker(STACK stack)
    {
        MARKER marker;

        marker.stack = stack;

        switch (stack)
        {
            case LowerStack:
                marker.marker = _lower;
                break;

            case UpperStack:
                marker.marker = _upper;
                break;

            default:
                break;
        }

        return marker;
    }



    void DoubleStackAllocator::freeToMarker(MARKER marker)
    {
        switch (marker.stack)
        {
            case LowerStack:
                
                NUT_ASSERT(marker.marker <= _lower && marker.marker >= _base);

                _lower = marker.marker;
                break;

            case UpperStack:
                
                NUT_ASSERT(marker.marker >= _upper && marker.marker <= _cap);

                _upper = marker.marker;
                break;
        }
    }
}
