/** 
 * \file Math.h
 * \brief This header defines several mathematical functions and constants.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __MATH_H__
#define __MATH_H__



namespace nut
{
    template<typename T> class Math
    {
        public:

        /// Class members ///

        static const T EPSILON;       /**< Represents a very small floating point value. */
        static const T PI;            /**< Represents an approximation of pi number. */
        static const T HALF_PI;       /**< Represents an approximation of pi / 2. */
        static const T _180_OVER_PI;  /**< Represents an approximation of 180 / pi. */
        static const T PI_OVER_180;   /**< Represents an approximation of pi / 180. */



        /// Class functions ///

        /**
         * Return the absolute value of a number.
         * 
         * @param value Number.
         * @return The absolute value.
         */
        static T abs(T value)
        {
            return value < 0 ? -value : value;
        }

        /**
         * Check if a small float point number can be considered zero.
         * 
         * @param value Floating-point value.
         * @return True if the value is less than Math::EPSILON. Otherwise, returns false.
         */
        static bool isZero(T value)
        {
            return abs(value) < EPSILON;
        }

        /**
         * Convert radian to degree.
         * 
         * @param angle Angle in radians.
         * @return Angle in degrees.
         */
        static T rad2deg(T angle)
        {
            return angle * _180_OVER_PI;
        }

        /**
         * Convert degree to radian.
         * 
         * @param angle Angle in degrees.
         * @return Angle in radians.
         */
        static T deg2rad(T angle)
        {
            return angle * PI_OVER_180;
        }

        /**
         * Check if an integer number is a power of two.
         * 
         * WARNING: This function should be used only with integers. Otherwise its
         * result is unpredictable.
         * 
         * @param value Interger value.
         * @return True if value is a power of two. Otherwise, returns false.
         */
        static bool isPowerOf2(T value)
        {
            if (value <= 0)
            {
                return false;
            }
            else
            {
                return (value & (value - 1)) == 0;
            }
        }
    };
    

    
    /// Definition of constants ///
    
    template<typename T> const T Math<T>::EPSILON       = T(1e-7);
    template<typename T> const T Math<T>::PI            = T(3.1415926535897932384626433832795028841971693993751058209749445923078164062);
    template<typename T> const T Math<T>::HALF_PI       = T(1.5707963267948966192313216916398);
    template<typename T> const T Math<T>::_180_OVER_PI  = T(57.295779513082320876798154814105);
    template<typename T> const T Math<T>::PI_OVER_180   = T(0.01745329251994329576923690768489);
}
#endif // __MATH_H__
