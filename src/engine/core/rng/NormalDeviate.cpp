/** 
 * \file NormalDeviate.cpp
 * \brief This class generates normal (or gaussian) deviates (pseudo-random numbers
 * normally distributed) using Box-Muller method.
 * 
 * source: Numerical Recipes in C, 2nd edition - chapter 7.2.
 * 
 * @author: Eder A. Perez.
 */

#include <cmath>
#include "NormalDeviate.h"



namespace nut
{
    unsigned long NormalDeviate::_x = 123456789;
    unsigned long NormalDeviate::_y = 362436069;
    unsigned long NormalDeviate::_z = 521288629;
    unsigned long NormalDeviate::_w = 88675123;



    float NormalDeviate::rand()
    {
        static int iset = 0;
        static float gset;
        float fac, rsq, v1, v2;

        // We don't have an extra deviate handy, so...
        if (iset == 0)
        {
            do
            {
                // ... pick two uniform numbers in the square extending from -1 to +1 in each direction
                // see if they are in the unit circle, and if they are not, try again.
                v1 = 2.0 * _xorshift() - 1.0;
                v2 = 2.0 * _xorshift() - 1.0;

                rsq = v1*v1 + v2*v2;
            } while (rsq >= 1.0 || rsq == 0.0);

            fac = sqrt(-2.0 * log(rsq) / rsq);

            // Now make the Box-Muller transformation to get two normal deviates.
            // Return one and save the other for next time.
            gset = v1 * fac;
            iset = 1; // Set flag

            return v2 * fac;
        }
        // We have an extra deviate handy, so unset the flag and return it.
        else
        {
            iset = 0;
            return gset;
        }
    }
}
