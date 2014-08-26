/** 
 * \file Vector4D.h
 * \brief Template class definition for 4-dimensional vectors manipulation.
 * 
 * @author: Eder A. Perez.
 */

#ifndef VECTOR4D_H
#define VECTOR4D_H

#include <cmath>
#include "Math.h"



namespace nut
{
    template<typename T> class Vector4D
    {
        public:

        T x; /**< X coordinate. */
        T y; /**< Y coordinate. */
        T z; /**< Z coordinate. */
        T w; /**< W coordinate. */



        /// Constant vectors ///

        static const Vector4D ZERO;   /**< Zero vector (0, 0, 0, 0). */
        static const Vector4D UNIT;   /**< Unit vector (1, 1, 1, 1). */
        static const Vector4D X_AXIS; /**< X-axis vector (1, 0, 0, 0). */
        static const Vector4D Y_AXIS; /**< Y-axis vector (0, 1, 0, 0). */
        static const Vector4D Z_AXIS; /**< Z-axis vector (0, 0, 1, 0). */
        static const Vector4D W_AXIS; /**< W-axis vector (0, 0, 0, 1). */



        /// Constructors ///

        /**
         * Default constructor.
         * 
         * Instantiates a zero vector.
         */
        Vector4D() : x( T(0.0) ), y( T(0.0) ), z( T(0.0) ), w( T(0.0) )
        {
        }

        /**
         * Instantiates a vector with x, y, z, w coordinates.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         * @param z Z-coordinate.
         * @param w W-coordinate.
         */
        Vector4D(const T x, const T y, const T z, const T w) : x(x), y(y), z(z), w(w)
        {
        }

        /**
         * Copy constructor.
         */
        Vector4D(const Vector4D& v) : x(v.x), y(v.y), z(v.z), w(v.w)
        {
        }



        /// Methods ///

        /**
         * Computes the magnitude of a vector (|v|).
         * 
         * @return A value representing the vector's magnitude.
         */
        T length() const
        {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        /**
         * Computes the squared magnitude of a vector (|v|^2).
         * 
         * Squared magnitude is cheaper than magnitude because of there's no squared root calculation.
         * It's useful when comparing two lengths.
         * 
         * @return A value representing the vector's squared magnitude.
         */
        T slength() const
        {
            return x * x + y * y + z * z + w * w;
        }

        /**
         * Converts vector to unit vector.
         */
        void normalize()
        {
            if (std::abs(x) > Math<T>::EPSILON || std::abs(y) > Math<T>::EPSILON || std::abs(z) > Math<T>::EPSILON || std::abs(w) > Math<T>::EPSILON)
            {
                T rLength = T(1.0) / std::sqrt(x * x + y * y + z * z + w * w);

                x *= rLength;
                y *= rLength;
                z *= rLength;
                w *= rLength;
            }
        }

        /**
         * Non-uniform vector scaling.
         * 
         * Uniform vector scaling is accomplished by operator* overload.
         * 
         * @param sX Scale factor in X axis.
         * @param sY Scale factor in Y axis.
         * @param sZ Scale factor in Z axis.
         * @param sW Scale factor in W axis.
         */
        void scale(T sX, T sY, T sZ, T sW)
        {
            x *= sX;
            y *= sY;
            z *= sZ;
            w *= sW;
        }

        /**
         * Project vector @v onto @this.
         * 
         * @param v A 4-dimensional vector.
         * @return The projection of @v onto @this.
         */
        Vector4D project(const Vector4D& v) const
        {
            T f = (v.x * x + v.y * y + v.z * z + v.w * w) / (x * x + y * y + z * z + w * w);
            return Vector4D(f * x, f * y, f * z, f * w);
        }



        /// Operators ///

        /**
         * Computes the dot product between @this and @v.
         * 
         * @param v A 4-dimensional vector.
         * @return The dot product.
         */
        T operator * (const Vector4D& v) const
        {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }

        /**
         * Multiplication by a scalar (v * s).
         * 
         * @param s A scalar value.
         * @return A scaled vector.
         */
        Vector4D operator * (const T s) const
        {
            return Vector4D(x * s, y * s, z * s, w * s);
        }

        /**
         * Multiplication by a scalar (s * v).
         * 
         * @param s A scalar value.
         * @param v A 4-dimensional vector to be scaled.
         * @return A scaled @v.
         */
        friend Vector4D operator * (const T s, const Vector4D& v)
        {
            return Vector4D(v.x * s, v.y * s, v.z * s, v.w * s);
        }

        /**
         * Multiplication by a scalar (v = v * s).
         * 
         * @param s A scalar value.
         * @return A scaled vector.
         */
        Vector4D& operator *= (const T s)
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;

            return *this;
        }

        /**
         * Division by a scalar (v / s).
         * 
         * @param s A scalar value
         * @return A scaled vector.
         */
        Vector4D operator / (const T s) const
        {
            T rScalar = T(1.0) / s;

            return Vector4D(x * rScalar, y * rScalar, z * rScalar, w * rScalar);
        }

        /**
         * Division by a scalar (v = v / s).
         * 
         * @param s A scalar value
         * @return A scaled vector.
         */
        Vector4D& operator /= (const T s)
        {
            T rScalar = T(1.0) / s;

            x *= rScalar;
            y *= rScalar;
            z *= rScalar;
            w *= rScalar;

            return *this;
        }

        /**
         * Vector addition (u + v).
         * 
         * @param v A 4-dimensional vector.
         * @return The sum of @v and @this.
         */
        Vector4D operator + (const Vector4D& v) const
        {
            return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        /**
         * Vector addition (u = u + v).
         * 
         * @param v A 4-dimensional vector.
         * @return The sum of @v and @this.
         */
        Vector4D& operator += (const Vector4D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;

            return *this;
        }

        /**
         * Vector subtraction (u - v).
         * 
         * @param v A 4-dimensional vector.
         * @return The subtraction of @this and @v.
         */
        Vector4D operator - (const Vector4D& v) const
        {
            return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        /**
         * Vector subtraction (u = u - v).
         * 
         * @param v A 4-dimensional vector.
         * @return The subtraction of @this and @v.
         */
        Vector4D& operator -= (const Vector4D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;

            return *this;
        }

        /**
         * Vector additive inverse (-v).
         * 
         * @return -@this.
         */
        Vector4D operator - () const
        {
            return Vector4D(-x, -y, -z, -w);
        }

        /**
         * Vector comparison.
         * 
         * @param v A 4-dimensional vector.
         * @return True if @this and @v have the same coordinates based on a EPSILON
         * error. Otherwise, return false.
         */
        bool operator == ( const Vector4D& v ) const
        {
            return (std::abs(x - v.x) < Math<T>::EPSILON && std::abs(y - v.y) < Math<T>::EPSILON &&
                    std::abs(z - v.z) < Math<T>::EPSILON && std::abs(w - v.w) < Math<T>::EPSILON);
        }

        /**
         * Vector comparison.
         * 
         * @param v A 4-dimensional vector.
         * @return False if @this and @v have the same coordinates based on a EPSILON
         * error. Otherwise, return true.
         */
        bool operator != ( const Vector4D& v ) const
        {
            return (std::abs(x - v.x) > Math<T>::EPSILON || std::abs(y - v.y) > Math<T>::EPSILON ||
                    std::abs(z - v.z) > Math<T>::EPSILON || std::abs(w - v.w) > Math<T>::EPSILON);
        }
    };

    template<typename T> const Vector4D<T> Vector4D<T>::ZERO( T(0.0), T(0.0), T(0.0), T(0.0) );
    template<typename T> const Vector4D<T> Vector4D<T>::UNIT( T(1.0), T(1.0), T(1.0), T(1.0) );
    template<typename T> const Vector4D<T> Vector4D<T>::X_AXIS( T(1.0), T(0.0), T(0.0), T(0.0) );
    template<typename T> const Vector4D<T> Vector4D<T>::Y_AXIS( T(0.0), T(1.0), T(0.0), T(0.0) );
    template<typename T> const Vector4D<T> Vector4D<T>::Z_AXIS( T(0.0), T(0.0), T(1.0), T(0.0) );
    template<typename T> const Vector4D<T> Vector4D<T>::W_AXIS( T(0.0), T(0.0), T(0.0), T(1.0) );
}
#endif // VECTOR4D_H
