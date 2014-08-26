/** 
 * \file Vector2D.h
 * \brief Template class definition for 2-dimensional vectors manipulation.
 * 
 * @author: Eder A. Perez.
 */

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>



namespace nut
{
    template<typename T> class Vector2D
    {
        public:

        T x; /**< X coordinate. */
        T y; /**< Y coordinate. */



        /// Constant vectors ///

        static const Vector2D ZERO;   /**< Zero vector (0, 0). */
        static const Vector2D UNIT;   /**< Unit vector (1, 1). */
        static const Vector2D X_AXIS; /**< X-axis vector (1, 0). */
        static const Vector2D Y_AXIS; /**< Y-axis vector (0, 1). */



        /// Constructors ///

        /**
         * Default constructor.
         * 
         * Instantiates a zero vector.
         */
        Vector2D() : x( T(0.0) ), y( T(0.0) )
        {
        }

        /**
         * Instantiates a vector with x, y coordinates.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         */
        Vector2D(const T x, const T y) : x(x), y(y)
        {
        }

        /**
         * Copy constructor.
         */
        Vector2D(const Vector2D& v) : x(v.x), y(v.y)
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
            return std::sqrt(x * x + y * y);
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
            return x * x + y * y;
        }

        /**
         * Converts vector to unit vector.
         */
        void normalize()
        {
            if (std::abs(x) > EPSILON || std::abs(y) > EPSILON)
            {
                T rLength = T(1.0) / std::sqrt(x * x + y * y);

                x *= rLength;
                y *= rLength;
            }
        }

        /**
         * Non-uniform vector scaling.
         * 
         * Uniform vector scaling is accomplished by operator* overload.
         * 
         * @param sX Scale factor in X axis.
         * @param sY Scale factor in Y axis.
         */
        void scale(T sX, T sY)
        {
            x *= sX;
            y *= sY;
        }

        /**
         * Computes the oriented area of a parallelogram which sides are @this and @v.
         * 
         * This computation is a kind of cross product in 2-dimensional vectors. The
         * result is a signed scalar representing the "z" coordinate, which is the
         * area of a parallelogram build by the two vectors. The sign of the area
         * follows the right-hand rule as the following example.
         * 
         * Example:
         * 
         * u = (1, 0)
         * v = (0, 1)
         * 
         * u X v = 1
         * v X u = -1
         * 
         * @param v A 2-dimensional vector.
         * @return The oriented area value.
         */
        T oriArea(const Vector2D& v) const
        {
            return (x * v.y - y * v.x);
        }

        /**
         * Project vector @v onto @this.
         * 
         * @param v A 2-dimensional vector.
         * @return The projection of @v onto @this.
         */
        Vector2D project(const Vector2D& v) const
        {
            T f = (v.x * x + v.y * y) / (x * x + y * y);
            return Vector2D(f * x, f * y);
        }



        /// Operators ///

        /**
         * Computes the dot product between @this and @v.
         * 
         * @param v A 2-dimensional vector.
         * @return The dot product.
         */
        T operator * (const Vector2D& v) const
        {
            return x * v.x + y * v.y;
        }

        /**
         * Multiplication by a scalar (v * s).
         * 
         * @param s A scalar value.
         * @return A scaled vector.
         */
        Vector2D operator * (const T s) const
        {
            return Vector2D(x * s, y * s);
        }

        /**
         * Multiplication by a scalar (s * v).
         * 
         * @param s A scalar value.
         * @param v A 2-dimensional vector to be scaled.
         * @return A scaled @v.
         */
        friend Vector2D operator * (const T s, const Vector2D& v)
        {
            return Vector2D(v.x * s, v.y * s);
        }

        /**
         * Multiplication by a scalar (v = v * s).
         * 
         * @param s A scalar value.
         * @return A scaled vector.
         */
        Vector2D& operator *= (const T s)
        {
            x *= s;
            y *= s;

            return *this;
        }

        /**
         * Division by a scalar (v / s).
         * 
         * @param s A scalar value
         * @return A scaled vector.
         */
        Vector2D operator / (const T s) const
        {
            T rScalar = T(1.0) / s;

            return Vector2D(x * rScalar, y * rScalar);
        }

        /**
         * Division by a scalar (v = v / s).
         * 
         * @param s A scalar value
         * @return A scaled vector.
         */
        Vector2D& operator /= (const T s)
        {
            T rScalar = T(1.0) / s;

            x *= rScalar;
            y *= rScalar;

            return *this;
        }

        /**
         * Vector addition (u + v).
         * 
         * @param v A 2-dimensional vector.
         * @return The sum of @v and @this.
         */
        Vector2D operator + (const Vector2D& v) const
        {
            return Vector2D(x + v.x, y + v.y);
        }

        /**
         * Vector addition (u = u + v).
         * 
         * @param v A 2-dimensional vector.
         * @return The sum of @v and @this.
         */
        Vector2D& operator += (const Vector2D& v)
        {
            x += v.x;
            y += v.y;

            return *this;
        }

        /**
         * Vector subtraction (u - v).
         * 
         * @param v A 2-dimensional vector.
         * @return The subtraction of @this and @v.
         */
        Vector2D operator - (const Vector2D& v) const
        {
            return Vector2D(x - v.x, y - v.y);
        }

        /**
         * Vector subtraction (u = u - v).
         * 
         * @param v A 2-dimensional vector.
         * @return The subtraction of @this and @v.
         */
        Vector2D& operator -= (const Vector2D& v)
        {
            x -= v.x;
            y -= v.y;

            return *this;
        }

        /**
         * Vector additive inverse (-v).
         * 
         * @return -@this.
         */
        Vector2D operator - () const
        {
            return Vector2D(-x, -y);
        }

        /**
         * Vector comparison.
         * 
         * @param v A 2-dimensional vector.
         * @return True if @this and @v have the same coordinates based on a EPSILON
         * error. Otherwise, return false.
         */
        bool operator == ( const Vector2D& v ) const
        {
            return (std::abs(x - v.x) < EPSILON && std::abs(y - v.y) < EPSILON);
        }

        /**
         * Vector comparison.
         * 
         * @param v A 2-dimensional vector.
         * @return False if @this and @v have the same coordinates based on a EPSILON
         * error. Otherwise, return true.
         */
        bool operator != ( const Vector2D& v ) const
        {
            return (std::abs(x - v.x) > EPSILON || std::abs(y - v.y) > EPSILON);
        }



        private:

        static const T EPSILON; /**< Very small value used for vector comparisons. */
    };

    template<typename T> const Vector2D<T> Vector2D<T>::ZERO( T(0.0), T(0.0) );
    template<typename T> const Vector2D<T> Vector2D<T>::UNIT( T(1.0), T(1.0) );
    template<typename T> const Vector2D<T> Vector2D<T>::X_AXIS( T(1.0), T(0.0) );
    template<typename T> const Vector2D<T> Vector2D<T>::Y_AXIS( T(0.0), T(1.0) );
    template<typename T> const T Vector2D<T>::EPSILON = T(1e-10);
}
#endif // VECTOR2D_H
