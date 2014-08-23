/** 
 * \file XORShift.h
 * \brief This class implements George Marsaglia's XORShift fast random number
 * generator producing uniformly distributed pseudo-random with a period of
 * (2^128) - 1.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __XORSHIFT_H__
#define __XORSHIFT_H__



namespace nut
{
    class XORShift
    {
        public:

        /// Methods ///

        /**
         * Initialize random number generator.
         * 
         * @param x Generator seed (default value 123456789).
         * @param y Generator seed (default value 362436069).
         * @param z Generator seed (default value 521288629).
         * @param w Generator seed (default value 88675123).
         */
        static void srand(unsigned long x, unsigned long y, unsigned long z, unsigned long w)
        {
            _x = x;
            _y = y;
            _z = z;
            _w = w;
        }

        /**
         * Compute a uniformly distributed pseudo-random number.
         * 
         * @return A pseudo-random floating-point number uniformly distributed in
         * the range [0, 1].
         */
        static unsigned long rand()
        {
            unsigned long t;

            t = (_x ^ (_x << 11));

            _x = _y; _y = _z; _z = _w;

            return _w = (_w ^ (_w >> 19)) ^ (t ^ (t >> 8));
        }



        private:

        /// Private attributes ///

        static unsigned long _x, _y, _z, _w;
    };

    // Initialize private attributes

    unsigned long XORShift::_x = 123456789;
    unsigned long XORShift::_y = 362436069;
    unsigned long XORShift::_z = 521288629;
    unsigned long XORShift::_w = 88675123;
}

#endif // __XORSHIFT_H__
