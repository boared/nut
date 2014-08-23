/** 
 * \file Vector3D.h
 * \brief Template class definition for 3-dimensional vectors manipulation.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include <cmath>



namespace nut
{
    template<typename T> class Vector3D
    {
        public:

        T x; /**< X coordinate. */
        T y; /**< Y coordinate. */
        T z; /**< Z coordinate. */



        /// Constant vectors ///

        static const Vector3D ZERO;   /**< Zero vector (0, 0, 0). */
        static const Vector3D UNIT;   /**< Unit vector (1, 1, 1). */
        static const Vector3D X_AXIS; /**< X-axis vector (1, 0, 0). */
        static const Vector3D Y_AXIS; /**< Y-axis vector (0, 1, 0). */
        static const Vector3D Z_AXIS; /**< Z-axis vector (0, 0, 1). */



        /// Constructors ///

        /**
         * Default constructor.
         * 
         * Instantiates a zero vector.
         */
        Vector3D() : x( T(0.0) ), y( T(0.0) ), z( T(0.0) )
        {
        }

        /**
         * Instantiates a vector with x, y, z coordinates.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         * @param z Z-coordinate.
         */
        Vector3D(const T x, const T y, const T z) : x(x), y(y), z(z)
        {
        }

        /**
         * Copy constructor.
         */
        Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z)
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
            return std::sqrt(x * x + y * y + z * z);
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
            return x * x + y * y + z * z;
        }

        /**
         * Converts vector to unit vector.
         */
        void normalize()
        {
            if (std::abs(x) > EPSILON || std::abs(y) > EPSILON || std::abs(z) > EPSILON)
            {
                T rLength = T(1.0) / std::sqrt(x * x + y * y + z * z);

                x *= rLength;
                y *= rLength;
                z *= rLength;
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
         */
        void scale(T sX, T sY, T sZ)
        {
            x *= sX;
            y *= sY;
            z *= sZ;
        }

        /**
         * Computes the cross product of @this and @v (@this X @v).
         * 
         * @param v A 3-dimensional vector.
         * @return A vector orthogonal to both @this and @v and with magnitude value
         * representing the area of a parallelogram which sides are @this and @v.
         */
        Vector3D cross(const Vector3D& v) const
        {
            return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
        }

        /**
         * Project vector @v onto @this.
         * 
         * @param v A 3-dimensional vector.
         * @return The projection of @v onto @this.
         */
        Vector3D project(const Vector3D& v) const
        {
            T f = (v.x * x + v.y * y + v.z * z) / (x * x + y * y + z * z);
            return Vector3D(f * x, f * y, f * z);
        }



        /// Operators ///

        /**
         * Computes the dot product between @this and @v.
         * 
         * @param v A 3-dimensional vector.
         * @return The dot product.
         */
        T operator * (const Vector3D& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        /**
         * Multiplication by a scalar (v * s).
         * 
         * @param s A scalar value.
         * @return A scaled vector.
         */
        Vector3D operator * (const T s) const
        {
            return Vector3D(x * s, y * s, z * s);
        }

        /**
         * Multiplication by a scalar (s * v).
         * 
         * @param s A scalar value.
         * @param v A 3-dimensional vector to be scaled.
         * @return A scaled @v.
         */
        friend Vector3D operator * (const T s, const Vector3D& v)
        {
            return Vector3D(v.x * s, v.y * s, v.z * s);
        }

        /**
         * Multiplication by a scalar (v = v * s).
         * 
         * @param s A scalar value.
         * @return A scaled vector.
         */
        Vector3D& operator *= (const T s)
        {
            x *= s;
            y *= s;
            z *= s;

            return *this;
        }

        /**
         * Division by a scalar (v / s).
         * 
         * @param s A scalar value
         * @return A scaled vector.
         */
        Vector3D operator / (const T s) const
        {
            T rScalar = T(1.0) / s;

            return Vector3D(x * rScalar, y * rScalar, z * rScalar);
        }

        /**
         * Division by a scalar (v = v / s).
         * 
         * @param s A scalar value
         * @return A scaled vector.
         */
        Vector3D& operator /= (const T s)
        {
            T rScalar = T(1.0) / s;

            x *= rScalar;
            y *= rScalar;
            z *= rScalar;

            return *this;
        }

        /**
         * Vector addition (u + v).
         * 
         * @param v A 3-dimensional vector.
         * @return The sum of @v and @this.
         */
        Vector3D operator + (const Vector3D& v) const
        {
            return Vector3D(x + v.x, y + v.y, z + v.z);
        }

        /**
         * Vector addition (u = u + v).
         * 
         * @param v A 3-dimensional vector.
         * @return The sum of @v and @this.
         */
        Vector3D& operator += (const Vector3D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;

            return *this;
        }

        /**
         * Vector subtraction (u - v).
         * 
         * @param v A 3-dimensional vector.
         * @return The subtraction of @this and @v.
         */
        Vector3D operator - (const Vector3D& v) const
        {
            return Vector3D(x - v.x, y - v.y, z - v.z);
        }

        /**
         * Vector subtraction (u = u - v).
         * 
         * @param v A 3-dimensional vector.
         * @return The subtraction of @this and @v.
         */
        Vector3D& operator -= (const Vector3D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;

            return *this;
        }

        /**
         * Vector additive inverse (-v).
         * 
         * @return -@this.
         */
        Vector3D operator - () const
        {
            return Vector3D(-x, -y, -z);
        }

        /**
         * Vector comparison.
         * 
         * @param v A 3-dimensional vector.
         * @return True if @this and @v have the same coordinates based on a EPSILON
         * error. Otherwise, return false.
         */
        bool operator == ( const Vector3D& v ) const
        {
            return (std::abs(x - v.x) < EPSILON && std::abs(y - v.y) < EPSILON &&
                    std::abs(z - v.z) < EPSILON);
        }

        /**
         * Vector comparison.
         * 
         * @param v A 3-dimensional vector.
         * @return False if @this and @v have the same coordinates based on a EPSILON
         * error. Otherwise, return true.
         */
        bool operator != ( const Vector3D& v ) const
        {
            return (std::abs(x - v.x) > EPSILON || std::abs(y - v.y) > EPSILON ||
                    std::abs(z - v.z) > EPSILON);
        }



        private:

        static const T EPSILON; /**< Very small value used for vector comparisons. */
    };

    template<typename T> const Vector3D<T> Vector3D<T>::ZERO( T(0.0), T(0.0), T(0.0) );
    template<typename T> const Vector3D<T> Vector3D<T>::UNIT( T(1.0), T(1.0), T(1.0) );
    template<typename T> const Vector3D<T> Vector3D<T>::X_AXIS( T(1.0), T(0.0), T(0.0) );
    template<typename T> const Vector3D<T> Vector3D<T>::Y_AXIS( T(0.0), T(1.0), T(0.0) );
    template<typename T> const Vector3D<T> Vector3D<T>::Z_AXIS( T(0.0), T(0.0), T(1.0) );
    template<typename T> const T Vector3D<T>::EPSILON = T(1e-10);
}
#endif // __VECTOR3D_H__
