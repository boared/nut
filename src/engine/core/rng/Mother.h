/** 
 * \file Mother.h
 * \brief This class implements George Marsaglia's "The Mother of All" random
 * number generator producing uniformly distributed pseudo-random 32 bit values
 * with period about 2^250.
 * 
 * source: http://www.stat.berkeley.edu/classes/s243/mother.c visited on may 10, 2014.
 * 
 * @author: Eder A. Perez.
 */

#ifndef MOTHER_H
#define MOTHER_H



namespace nut
{
    class Mother
    {
        public:

        /// Methods ///

        /**
         * Initialize random number generator.
         * 
         * @param seed Generator seed.
         */
        static void srand(long seed);

        /**
         * Compute a uniformly distributed pseudo-random number.
         * 
         * @return A pseudo-random floating-point number uniformly distributed in
         * the range [0, 1].
         */
        static float rand();



        private:

        /// Private attributes ///

        static long _idum;

        static short mother1[10];
        static short mother2[10];

        static const long m16Long;     // 2^16
        static const long m16Mask;     // mask for lower 16 bits
        static const long m15Mask;     // mask for lower 15 bits
        static const long m31Mask;     // mask for 31 bits
        static const double m32Double; // 2^32-1
    };
}

#endif // MOTHER_H
