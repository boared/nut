/** 
 * \file ExpDeviate.h
 * \brief This class generates exponential deviates (pseudo-random numbers distributed
 * exponentially).
 * 
 * source: Numerical Recipes in C, 2nd edition - chapter 7.2.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __EXPDEVIATE_H__
#define __EXPDEVIATE_H__

#include <cmath>



namespace nut
{
    class ExpDeviate
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
         * Compute an exponentially distributed, positive, random deviate of unit mean.
         * 
         * @return A pseudo-random floating-point number exponentially distributed in
         * the range (0, +inf).
         */
        static float rand()
        {
            float value;

            // Discarded
            _xorshift();

            // Generate an uniform deviate for input for an exponential function
            do
            {
                value = _xorshift();
            } while (value == 0.0);

            return -log(value);
        }



        private:

        /// Private attributes ///

        static unsigned long _x, _y, _z, _w;



        /// Private methods ///

        /**
         * Compute a uniformly distributed pseudo-random number.
         * 
         * @return A pseudo-random floating-point number uniformly distributed in
         * the range [0, 1].
         */
        static float _xorshift()
        {
            unsigned long t;

            t = (_x ^ (_x << 11));

            _x = _y; _y = _z; _z = _w;

            return _w = (_w ^ (_w >> 19)) ^ (t ^ (t >> 8));
        }
    };

    // Initialize private attributes

    unsigned long XORShift::_x = 123456789;
    unsigned long XORShift::_y = 362436069;
    unsigned long XORShift::_z = 521288629;
    unsigned long XORShift::_w = 88675123;
}

#endif // __EXPDEVIATE_H__
