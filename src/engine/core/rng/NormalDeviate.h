/** 
 * \file NormalDeviate.h
 * \brief This class generates normal (or gaussian) deviates (pseudo-random numbers
 * normally distributed) using Box-Muller method.
 * 
 * source: Numerical Recipes in C, 2nd edition - chapter 7.2.
 * 
 * @author: Eder A. Perez.
 */

#ifndef NORMALDEVIATE_H
#define NORMALDEVIATE_H



namespace nut
{
    class NormalDeviate
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
         * Compute a normally distributed deviate with zero mean and unit variance.
         * 
         * @return A pseudo-random floating-point number normally distributed with
         * zero mean and unit variance.
         */
        static float rand();



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
}

#endif // NORMALDEVIATE_H
