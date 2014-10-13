/** 
 * \file Mother.cpp
 * \brief This class implements George Marsaglia's "The Mother of All" random
 * number generator producing uniformly distributed pseudo-random 32 bit values
 * witht period about 2^250.
 * 
 * source: http://www.stat.berkeley.edu/classes/s243/mother.c visited on may 10, 2014.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include <cstring>
#include "Mother.h"



namespace nut
{
    long Mother::_idum = 0;

    short Mother::mother1[10] = { 0 };
    short Mother::mother2[10] = { 0 };

    const long Mother::m16Long = 65536L;           // 2^16
    const long Mother::m16Mask = 0xFFFF;           // mask for lower 16 bits
    const long Mother::m15Mask = 0x7FFF;           // mask for lower 15 bits
    const long Mother::m31Mask = 0x7FFFFFFF;       // mask for 31 bits
    const double Mother::m32Double = 4294967295.0; // 2^32-1



    void Mother::srand(long seed)
    {
        unsigned short sNumber;
        unsigned long number;
        short n, *p;

        _idum = seed == 0 ? seed ^ 123459876 : seed; // Avoid using zero for seed

        // Initialize motheri with 9 random values the first time
        sNumber = _idum & m16Mask;  // The low 16 bits
        number = _idum & m31Mask;   // Only want 31 bits

        p = mother1;
        for (n = 18; n--;)
        {
            number = 30903 * sNumber + (number >> 16);
            *p++ = sNumber = number & m16Mask;

            if (n == 9)
                p = mother2;
        }

        // Make carry 15 bits
        mother1[0] &= m15Mask;
        mother2[0] &= m15Mask;
    }



    float Mother::rand()
    {
        unsigned long number1, number2;

        // Move elements 1 to 8 to 2 to 9
        memcpy((char*)mother1 + 2,(char*)mother1 + 1, 8 * sizeof(short));
        memcpy((char*)mother2 + 2,(char*)mother2 + 1, 8 * sizeof(short));

        // Put the carry values in numberi
        number1 = mother1[0];
        number2 = mother2[0];

        // Form the linear combinations
        number1 += 1941 * mother1[2] +  1860 * mother1[3] +
                   1812 * mother1[4] +  1776 * mother1[5] +
                   1492 * mother1[6] +  1215 * mother1[7] +
                   1066 * mother1[8] + 12013 * mother1[9];

        number2 += 1111 * mother2[2] + 2222 * mother2[3] +
                   3333 * mother2[4] + 4444 * mother2[5] +
                   5555 * mother2[6] + 6666 * mother2[7] +
                   7777 * mother2[8] + 9272 * mother2[9];

        // Save the high bits of numberi as the new carry
        mother1[0] = number1 / m16Long;
        mother2[0] = number2 / m16Long;

        // Put the low bits of numberi into motheri[1]
        mother1[1] = m16Mask & number1;
        mother2[1] = m16Mask & number2;

        // Combine the two 16 bit random numbers into one 32 bit
        _idum = ( ( (long)mother1[1] ) << 16) + (long)mother2[1];

        // Return a float value between 0 and 1
        return ((float)_idum) / m32Double;
    }
}
