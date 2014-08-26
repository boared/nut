/** 
 * \file Matrix4x4.h
 * \brief Template class definition for create and handle 4x4 matrices.
 * 
 * @author: Eder A. Perez.
 */

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cstring>
#include <cmath>
#include "Vector4D.h"



namespace nut
{
    /**
     * Matrix4x4.
     * 
     * Represents a 4x4 matrix for general purpose. When applied to a vector,
     * the vector must be located at right side.
     * 
     * Ex.: u = M x v
     * 
     * The matrix's values access order is column-major:
     * 
     *          |  0  4  8 12 |
     * Ex.: M = |  1  5  9 13 |
     *          |  2  6 10 14 |
     *          |  3  7 11 15 |
     */
    template<typename T> class Matrix4x4
    {
        public:

        /// Constant matrices ///

        static const Matrix4x4 IDENTITY;   /**< Identity matrix. */
        static const Matrix4x4 ZERO;       /**< Zero matrix. */



        /// Constructors ///

        /**
         * Default constructor.
         * 
         * Instantiates an identity matrix.
         */
        Matrix4x4()
        {
            memset(_m, 0, sizeof(T) * 16);
            _m[0] = _m[5] = _m[10] = _m [15] = T(1.0);
        }

        /**
         * Copy constructor.
         * 
         * Instantiates a copy of input matrix.
         * 
         * @param m A Matrix4x4.
         */
        Matrix4x4(const Matrix4x4& m)
        {
            memcpy(_m, m._m, sizeof(T) * 16);
        }

        /**
         * Constructor.
         * 
         * Instatiates a matrix out of scalar values.
         * 
         * @param ann A value at position nn of matrix.
         */
        Matrix4x4(const T a11, const T a12, const T a13, const T a14,
                  const T a21, const T a22, const T a23, const T a24,
                  const T a31, const T a32, const T a33, const T a34,
                  const T a41, const T a42, const T a43, const T a44)
        {
            _m[ 0] = a11; _m[ 4] = a12; _m[ 8] = a13; _m[12] = a14;
            _m[ 1] = a21; _m[ 5] = a22; _m[ 9] = a23; _m[13] = a24;
            _m[ 2] = a31; _m[ 6] = a32; _m[10] = a33; _m[14] = a34;
            _m[ 3] = a41; _m[ 7] = a42; _m[11] = a43; _m[15] = a44;
        }



        /// Methods ///

        /**
         * Set zero to all values of the matrix.
         */
        void clear()
        {
            memset(_m, 0, sizeof(T) * 16);
        }

        /**
         * Set matrix as identity.
         */
        void setIdentity()
        {
            memset(_m, 0, sizeof(T) * 16);
            _m[0] = _m[5] = _m[10] = _m [15] = T(1.0);
        }

        /**
         * Compute the inverse matrix.
         * 
         * @return The inverse matrix if it exists. Otherwise, returns ZERO matrix.
         */
        Matrix4x4 inverse() const;

        /**
         * Compute the matrix's determinant.
         * 
         * @return The matrix's determinant.
         */
        T determinant() const
        {
            return
            _m[12]*_m[ 9]*_m[ 6]*_m[ 3] - _m[ 8]*_m[13]*_m[ 6]*_m[ 3] - _m[12]*_m[ 5]*_m[10]*_m[ 3] + _m[ 4]*_m[13]*_m[10]*_m[ 3] +
            _m[ 8]*_m[ 5]*_m[14]*_m[ 3] - _m[ 4]*_m[ 9]*_m[14]*_m[ 3] - _m[12]*_m[ 9]*_m[ 2]*_m[ 7] + _m[ 8]*_m[13]*_m[ 2]*_m[ 7] +
            _m[12]*_m[ 1]*_m[10]*_m[ 7] - _m[ 0]*_m[13]*_m[10]*_m[ 7] - _m[ 8]*_m[ 1]*_m[14]*_m[ 7] + _m[ 0]*_m[ 9]*_m[14]*_m[ 7] +
            _m[12]*_m[ 5]*_m[ 2]*_m[11] - _m[ 4]*_m[13]*_m[ 2]*_m[11] - _m[12]*_m[ 1]*_m[ 6]*_m[11] + _m[ 0]*_m[13]*_m[ 6]*_m[11] +
            _m[ 4]*_m[ 1]*_m[14]*_m[11] - _m[ 0]*_m[ 5]*_m[14]*_m[11] - _m[ 8]*_m[ 5]*_m[ 2]*_m[15] + _m[ 4]*_m[ 9]*_m[ 2]*_m[15] +
            _m[ 8]*_m[ 1]*_m[ 6]*_m[15] - _m[ 0]*_m[ 9]*_m[ 6]*_m[15] - _m[ 4]*_m[ 1]*_m[10]*_m[15] + _m[ 0]*_m[ 5]*_m[10]*_m[15];
        }

        /**
         * Compute the transposed matrix.
         * 
         * @return The transposed matrix.
         */
        Matrix4x4 transpose() const
        {
            return Matrix4x4(_m[ 0], _m[ 1], _m[ 2], _m[ 3],
                             _m[ 4], _m[ 5], _m[ 6], _m[ 7],
                             _m[ 8], _m[ 9], _m[10], _m[11],
                             _m[12], _m[13], _m[14], _m[15]);
        }

        /// Operators ///

        /**
         * Access a matrix for read and write individual values.
         * 
         * WARNING: The access is column-wise like in OpenGL.
         */
        T& operator [] (int pos)
        {
            return _m[pos];
        }

        /** 
         * Access a matrix value in constant matrices.
         * 
         * WARNING: The access is column-wise like in OpenGL.
         */
        const T operator [] (int pos) const
        {
            return _m[pos];
        }

        /**
         * Multiply a matrix by a 4D vector.
         * 
         * @param v A 4D vector.
         * @return A 4D vector resulting from the matrix multiplication by @v.
         */
        Vector4D<T> operator * (const Vector4D<T>& v) const
        {
            return Vector4D<T>(_m[ 0] * v.x + _m[ 4] * v.y + _m[ 8] * v.z + _m[12] * v.w,
                               _m[ 1] * v.x + _m[ 5] * v.y + _m[ 9] * v.z + _m[13] * v.w,
                               _m[ 2] * v.x + _m[ 6] * v.y + _m[10] * v.z + _m[14] * v.w,
                               _m[ 3] * v.x + _m[ 7] * v.y + _m[11] * v.z + _m[15] * v.w);
        }

        /**
         * Multiply a matrix by an scalar.
         * 
         * @param s A scalar value.
         * @return A matrix multiplied by a scalar.
         */
        Matrix4x4 operator * (const T s) const
        {
            return Matrix4x4(_m[ 0] *  s, _m[ 4] *  s, _m[ 8] *  s, _m[12] *  s,
                             _m[ 1] *  s, _m[ 5] *  s, _m[ 9] *  s, _m[13] *  s,
                             _m[ 2] *  s, _m[ 6] *  s, _m[10] *  s, _m[14] *  s,
                             _m[ 3] *  s, _m[ 7] *  s, _m[11] *  s, _m[15] *  s);
        }

        /**
         * Multiply a matrix by an scalar.
         * 
         * @param s A scalar value.
         * @param m An input matrix.
         * @return @m multiplied by a scalar.
         */
        friend Matrix4x4 operator * (const T s, const Matrix4x4& m)
        {
            return Matrix4x4(m._m[ 0] *  s, m._m[ 4] *  s, m._m[ 8] *  s, m._m[12] *  s,
                             m._m[ 1] *  s, m._m[ 5] *  s, m._m[ 9] *  s, m._m[13] *  s,
                             m._m[ 2] *  s, m._m[ 6] *  s, m._m[10] *  s, m._m[14] *  s,
                             m._m[ 3] *  s, m._m[ 7] *  s, m._m[11] *  s, m._m[15] *  s);
        }

        /**
         * Multiplication by an scalar.
         * 
         * @param s A scalar value.
         * @return This matrix multiplied by a scalar.
         */
        Matrix4x4& operator *= (const T s)
        {
            _m[ 0] *= s; _m[ 4] *= s; _m[ 8] *= s; _m[12] *= s;
            _m[ 1] *= s; _m[ 5] *= s; _m[ 9] *= s; _m[13] *= s;
            _m[ 2] *= s; _m[ 6] *= s; _m[10] *= s; _m[14] *= s;
            _m[ 3] *= s; _m[ 7] *= s; _m[11] *= s; _m[15] *= s;

            return *this;
        }

        /**
         * Multiply two matrices.
         * 
         * @param m A matrix.
         * @return @this * @m.
         */
        Matrix4x4 operator * (const Matrix4x4& m) const
        {
            return Matrix4x4(_m[ 0] * m._m[ 0] + _m[ 4] * m._m[ 1] + _m[ 8] * m._m[ 2] + _m[12] * m._m[ 3],
                             _m[ 0] * m._m[ 4] + _m[ 4] * m._m[ 5] + _m[ 8] * m._m[ 6] + _m[12] * m._m[ 7],
                             _m[ 0] * m._m[ 8] + _m[ 4] * m._m[ 9] + _m[ 8] * m._m[10] + _m[12] * m._m[11],
                             _m[ 0] * m._m[12] + _m[ 4] * m._m[13] + _m[ 8] * m._m[14] + _m[12] * m._m[15],

                             _m[ 1] * m._m[ 0] + _m[ 5] * m._m[ 1] + _m[ 9] * m._m[ 2] + _m[13] * m._m[ 3],
                             _m[ 1] * m._m[ 4] + _m[ 5] * m._m[ 5] + _m[ 9] * m._m[ 6] + _m[13] * m._m[ 7],
                             _m[ 1] * m._m[ 8] + _m[ 5] * m._m[ 9] + _m[ 9] * m._m[10] + _m[13] * m._m[11],
                             _m[ 1] * m._m[12] + _m[ 5] * m._m[13] + _m[ 9] * m._m[14] + _m[13] * m._m[15],

                             _m[ 2] * m._m[ 0] + _m[ 6] * m._m[ 1] + _m[10] * m._m[ 2] + _m[14] * m._m[ 3],
                             _m[ 2] * m._m[ 4] + _m[ 6] * m._m[ 5] + _m[10] * m._m[ 6] + _m[14] * m._m[ 7],
                             _m[ 2] * m._m[ 8] + _m[ 6] * m._m[ 9] + _m[10] * m._m[10] + _m[14] * m._m[11],
                             _m[ 2] * m._m[12] + _m[ 6] * m._m[13] + _m[10] * m._m[14] + _m[14] * m._m[15],

                             _m[ 3] * m._m[ 0] + _m[ 7] * m._m[ 1] + _m[11] * m._m[ 2] + _m[15] * m._m[ 3],
                             _m[ 3] * m._m[ 4] + _m[ 7] * m._m[ 5] + _m[11] * m._m[ 6] + _m[15] * m._m[ 7],
                             _m[ 3] * m._m[ 8] + _m[ 7] * m._m[ 9] + _m[11] * m._m[10] + _m[15] * m._m[11],
                             _m[ 3] * m._m[12] + _m[ 7] * m._m[13] + _m[11] * m._m[14] + _m[15] * m._m[15]);
        }

        /**
         * Multiply two matrices.
         * 
         * The order of multiplication is: m1 *= m2 <=> m1 = m1 * m2.
         * 
         * @param m A matrix.
         * @return @this * @m.
         */
        Matrix4x4& operator *= (const Matrix4x4& m)
        {
            T r[16];

            r[ 0] = _m[ 0] * m._m[ 0] + _m[ 4] * m._m[ 1] + _m[ 8] * m._m[ 2] + _m[12] * m._m[ 3];
            r[ 4] = _m[ 0] * m._m[ 4] + _m[ 4] * m._m[ 5] + _m[ 8] * m._m[ 6] + _m[12] * m._m[ 7];
            r[ 8] = _m[ 0] * m._m[ 8] + _m[ 4] * m._m[ 9] + _m[ 8] * m._m[10] + _m[12] * m._m[11];
            r[12] = _m[ 0] * m._m[12] + _m[ 4] * m._m[13] + _m[ 8] * m._m[14] + _m[12] * m._m[15];

            r[ 1] = _m[ 1] * m._m[ 0] + _m[ 5] * m._m[ 1] + _m[ 9] * m._m[ 2] + _m[13] * m._m[ 3];
            r[ 5] = _m[ 1] * m._m[ 4] + _m[ 5] * m._m[ 5] + _m[ 9] * m._m[ 6] + _m[13] * m._m[ 7];
            r[ 9] = _m[ 1] * m._m[ 8] + _m[ 5] * m._m[ 9] + _m[ 9] * m._m[10] + _m[13] * m._m[11];
            r[13] = _m[ 1] * m._m[12] + _m[ 5] * m._m[13] + _m[ 9] * m._m[14] + _m[13] * m._m[15];

            r[ 2] = _m[ 2] * m._m[ 0] + _m[ 6] * m._m[ 1] + _m[10] * m._m[ 2] + _m[14] * m._m[ 3];
            r[ 6] = _m[ 2] * m._m[ 4] + _m[ 6] * m._m[ 5] + _m[10] * m._m[ 6] + _m[14] * m._m[ 7];
            r[10] = _m[ 2] * m._m[ 8] + _m[ 6] * m._m[ 9] + _m[10] * m._m[10] + _m[14] * m._m[11];
            r[14] = _m[ 2] * m._m[12] + _m[ 6] * m._m[13] + _m[10] * m._m[14] + _m[14] * m._m[15];

            r[ 3] = _m[ 3] * m._m[ 0] + _m[ 7] * m._m[ 1] + _m[11] * m._m[ 2] + _m[15] * m._m[ 3];
            r[ 7] = _m[ 3] * m._m[ 4] + _m[ 7] * m._m[ 5] + _m[11] * m._m[ 6] + _m[15] * m._m[ 7];
            r[11] = _m[ 3] * m._m[ 8] + _m[ 7] * m._m[ 9] + _m[11] * m._m[10] + _m[15] * m._m[11];
            r[15] = _m[ 3] * m._m[12] + _m[ 7] * m._m[13] + _m[11] * m._m[14] + _m[15] * m._m[15];

            memcpy(_m, r, sizeof(T) * 16);

            return *this;
        }

        /**
         * Division by an scalar.
         * 
         * @param s A scalar value.
         * @return @this / s.
         */
        Matrix4x4 operator / (const T s) const
        {
            T rScalar = T(1.0) / s;

            return Matrix4x4(_m[ 0] * rScalar, _m[ 4] * rScalar, _m[ 8] * rScalar, _m[12] * rScalar,
                             _m[ 1] * rScalar, _m[ 5] * rScalar, _m[ 9] * rScalar, _m[13] * rScalar,
                             _m[ 2] * rScalar, _m[ 6] * rScalar, _m[10] * rScalar, _m[14] * rScalar,
                             _m[ 3] * rScalar, _m[ 7] * rScalar, _m[11] * rScalar, _m[15] * rScalar);
        }

        /**
         * Division by an scalar.
         * 
         * @param s A scalar value.
         * @return @this / s.
         */
        Matrix4x4& operator /= (const T s)
        {
            T rScalar = T(1.0) / s;

            _m[ 0] *= rScalar; _m[ 4] *= rScalar; _m[ 8] *= rScalar; _m[12] *= rScalar;
            _m[ 1] *= rScalar; _m[ 5] *= rScalar; _m[ 9] *= rScalar; _m[13] *= rScalar;
            _m[ 2] *= rScalar; _m[ 6] *= rScalar; _m[10] *= rScalar; _m[14] *= rScalar;
            _m[ 3] *= rScalar; _m[ 7] *= rScalar; _m[11] *= rScalar; _m[15] *= rScalar;

            return *this;
        }

        /**
         * Matrix addition.
         * 
         * @param m A matrix.
         * @return @this + m.
         */
        Matrix4x4 operator + (const Matrix4x4& m) const
        {
            return Matrix4x4(_m[ 0] + m[ 0], _m[ 4] + m[ 4], _m[ 8] + m[ 8], _m[12] + m[12],
                             _m[ 1] + m[ 1], _m[ 5] + m[ 5], _m[ 9] + m[ 9], _m[13] + m[13],
                             _m[ 2] + m[ 2], _m[ 6] + m[ 6], _m[10] + m[10], _m[14] + m[14],
                             _m[ 3] + m[ 3], _m[ 7] + m[ 7], _m[11] + m[11], _m[15] + m[15]);
        }

        /**
         * Matrix addition.
         * 
         * @param m A matrix.
         * @return @this + m.
         */
        Matrix4x4& operator += (const Matrix4x4& m)
        {
            _m[ 0] += m[ 0]; _m[ 4] += m[ 4]; _m[ 8] += m[ 8]; _m[12] += m[12];
            _m[ 1] += m[ 1]; _m[ 5] += m[ 5]; _m[ 9] += m[ 9]; _m[13] += m[13];
            _m[ 2] += m[ 2]; _m[ 6] += m[ 6]; _m[10] += m[10]; _m[14] += m[14];
            _m[ 3] += m[ 3]; _m[ 7] += m[ 7]; _m[11] += m[11]; _m[15] += m[15];

            return *this;
        }

        /**
         * Matrix subtraction.
         * 
         * @param m A matrix.
         * @return @this - m.
         */
        Matrix4x4 operator - (const Matrix4x4& m) const
        {
            return Matrix4x4(_m[ 0] - m[ 0], _m[ 4] - m[ 4], _m[ 8] - m[ 8], _m[12] - m[12],
                             _m[ 1] - m[ 1], _m[ 5] - m[ 5], _m[ 9] - m[ 9], _m[13] - m[13],
                             _m[ 2] - m[ 2], _m[ 6] - m[ 6], _m[10] - m[10], _m[14] - m[14],
                             _m[ 3] - m[ 3], _m[ 7] - m[ 7], _m[11] - m[11], _m[15] - m[15]);
        }

        /**
         * Matrix subtraction.
         * 
         * @param m A matrix.
         * @return @this - m.
         */
        Matrix4x4& operator -= (const Matrix4x4& m)
        {
            _m[ 0] -= m[ 0]; _m[ 4] -= m[ 4]; _m[ 8] -= m[ 8]; _m[12] -= m[12];
            _m[ 1] -= m[ 1]; _m[ 5] -= m[ 5]; _m[ 9] -= m[ 9]; _m[13] -= m[13];
            _m[ 2] -= m[ 2]; _m[ 6] -= m[ 6]; _m[10] -= m[10]; _m[14] -= m[14];
            _m[ 3] -= m[ 3]; _m[ 7] -= m[ 7]; _m[11] -= m[11]; _m[15] -= m[15];

            return *this;
        }

        /**
         * Tests two matrices for equality.
         * 
         * @param A matrix.
         */
        bool operator == ( const Matrix4x4& m ) const
        {
            return std::fabs(_m[ 0] - m[ 0]) < 1e-15 && std::fabs(_m[ 4] - m[ 4]) < 1e-15 && std::fabs(_m[ 8] - m[ 8]) < 1e-15 && std::fabs(_m[12] - m[12]) < 1e-15 &&
                   std::fabs(_m[ 1] - m[ 1]) < 1e-15 && std::fabs(_m[ 5] - m[ 5]) < 1e-15 && std::fabs(_m[ 9] - m[ 9]) < 1e-15 && std::fabs(_m[13] - m[13]) < 1e-15 &&
                   std::fabs(_m[ 2] - m[ 2]) < 1e-15 && std::fabs(_m[ 6] - m[ 6]) < 1e-15 && std::fabs(_m[10] - m[10]) < 1e-15 && std::fabs(_m[14] - m[14]) < 1e-15 &&
                   std::fabs(_m[ 3] - m[ 3]) < 1e-15 && std::fabs(_m[ 7] - m[ 7]) < 1e-15 && std::fabs(_m[11] - m[11]) < 1e-15 && std::fabs(_m[15] - m[15]) < 1e-15;
        }

        /**
         * Tests two matrices for inequality.
         * 
         * @param A matrix.
         */
        bool operator != ( const Matrix4x4& m ) const
        {
            return std::fabs(_m[ 0] - m[ 0]) >= 1e-15 || std::fabs(_m[ 4] - m[ 4]) >= 1e-15 || std::fabs(_m[ 8] - m[ 8]) >= 1e-15 || std::fabs(_m[12] - m[12]) >= 1e-15 ||
                   std::fabs(_m[ 1] - m[ 1]) >= 1e-15 || std::fabs(_m[ 5] - m[ 5]) >= 1e-15 || std::fabs(_m[ 9] - m[ 9]) >= 1e-15 || std::fabs(_m[13] - m[13]) >= 1e-15 ||
                   std::fabs(_m[ 2] - m[ 2]) >= 1e-15 || std::fabs(_m[ 6] - m[ 6]) >= 1e-15 || std::fabs(_m[10] - m[10]) >= 1e-15 || std::fabs(_m[14] - m[14]) >= 1e-15 ||
                   std::fabs(_m[ 3] - m[ 3]) >= 1e-15 || std::fabs(_m[ 7] - m[ 7]) >= 1e-15 || std::fabs(_m[11] - m[11]) >= 1e-15 || std::fabs(_m[15] - m[15]) >= 1e-15;
        }



        private:

        /// Private attributes ///

        T _m[16]; /**< Stores the sixteen values of the 4x4 matrix. */

    };

    template<typename T> const Matrix4x4<T> Matrix4x4<T>::IDENTITY( T(1.0), T(0.0), T(0.0), T(0.0),
                                                                    T(0.0), T(1.0), T(0.0), T(0.0),
                                                                    T(0.0), T(0.0), T(1.0), T(0.0),
                                                                    T(0.0), T(0.0), T(0.0), T(1.0) );

    template<typename T> const Matrix4x4<T> Matrix4x4<T>::ZERO( T(0.0), T(0.0), T(0.0), T(0.0),
                                                                T(0.0), T(0.0), T(0.0), T(0.0),
                                                                T(0.0), T(0.0), T(0.0), T(0.0),
                                                                T(0.0), T(0.0), T(0.0), T(0.0) );

    template<typename T> Matrix4x4<T> Matrix4x4<T>::inverse() const
    {
        T det = determinant();

        if (fabs(det) < 1e-15)
            return Matrix4x4<T>::ZERO;

        Matrix4x4 inv;
        T invDet = T(1.0) / det;

        inv._m[ 0] = invDet * (_m[ 9]*_m[14]*_m[ 7] - _m[13]*_m[10]*_m[ 7] + _m[13]*_m[ 6]*_m[11] - _m[ 5]*_m[14]*_m[11] - _m[ 9]*_m[ 6]*_m[15] + _m[ 5]*_m[10]*_m[15]);
        inv._m[ 4] = invDet * (_m[12]*_m[10]*_m[ 7] - _m[ 8]*_m[14]*_m[ 7] - _m[12]*_m[ 6]*_m[11] + _m[ 4]*_m[14]*_m[11] + _m[ 8]*_m[ 6]*_m[15] - _m[ 4]*_m[10]*_m[15]);
        inv._m[ 8] = invDet * (_m[ 8]*_m[13]*_m[ 7] - _m[12]*_m[ 9]*_m[ 7] + _m[12]*_m[ 5]*_m[11] - _m[ 4]*_m[13]*_m[11] - _m[ 8]*_m[ 5]*_m[15] + _m[ 4]*_m[ 9]*_m[15]);
        inv._m[12] = invDet * (_m[12]*_m[ 9]*_m[ 6] - _m[ 8]*_m[13]*_m[ 6] - _m[12]*_m[ 5]*_m[10] + _m[ 4]*_m[13]*_m[10] + _m[ 8]*_m[ 5]*_m[14] - _m[ 4]*_m[ 9]*_m[14]);

        inv._m[ 1] = invDet * (_m[13]*_m[10]*_m[ 3] - _m[ 9]*_m[14]*_m[ 3] - _m[13]*_m[ 2]*_m[11] + _m[ 1]*_m[14]*_m[11] + _m[ 9]*_m[ 2]*_m[15] - _m[ 1]*_m[10]*_m[15]);
        inv._m[ 5] = invDet * (_m[ 8]*_m[14]*_m[ 3] - _m[12]*_m[10]*_m[ 3] + _m[12]*_m[ 2]*_m[11] - _m[ 0]*_m[14]*_m[11] - _m[ 8]*_m[ 2]*_m[15] + _m[ 0]*_m[10]*_m[15]);
        inv._m[ 9] = invDet * (_m[12]*_m[ 9]*_m[ 3] - _m[ 8]*_m[13]*_m[ 3] - _m[12]*_m[ 1]*_m[11] + _m[ 0]*_m[13]*_m[11] + _m[ 8]*_m[ 1]*_m[15] - _m[ 0]*_m[ 9]*_m[15]);
        inv._m[13] = invDet * (_m[ 8]*_m[13]*_m[ 2] - _m[12]*_m[ 9]*_m[ 2] + _m[12]*_m[ 1]*_m[10] - _m[ 0]*_m[13]*_m[10] - _m[ 8]*_m[ 1]*_m[14] + _m[ 0]*_m[ 9]*_m[14]);

        inv._m[ 2] = invDet * (_m[ 5]*_m[14]*_m[ 3] - _m[13]*_m[ 6]*_m[ 3] + _m[13]*_m[ 2]*_m[ 7] - _m[ 1]*_m[14]*_m[ 7] - _m[ 5]*_m[ 2]*_m[15] + _m[ 1]*_m[ 6]*_m[15]);
        inv._m[ 6] = invDet * (_m[12]*_m[ 6]*_m[ 3] - _m[ 4]*_m[14]*_m[ 3] - _m[12]*_m[ 2]*_m[ 7] + _m[ 0]*_m[14]*_m[ 7] + _m[ 4]*_m[ 2]*_m[15] - _m[ 0]*_m[ 6]*_m[15]);
        inv._m[10] = invDet * (_m[ 4]*_m[13]*_m[ 3] - _m[12]*_m[ 5]*_m[ 3] + _m[12]*_m[ 1]*_m[ 7] - _m[ 0]*_m[13]*_m[ 7] - _m[ 4]*_m[ 1]*_m[15] + _m[ 0]*_m[ 5]*_m[15]);
        inv._m[14] = invDet * (_m[12]*_m[ 5]*_m[ 2] - _m[ 4]*_m[13]*_m[ 2] - _m[12]*_m[ 1]*_m[ 6] + _m[ 0]*_m[13]*_m[ 6] + _m[ 4]*_m[ 1]*_m[14] - _m[ 0]*_m[ 5]*_m[14]);

        inv._m[ 3] = invDet * (_m[ 9]*_m[ 6]*_m[ 3] - _m[ 5]*_m[10]*_m[ 3] - _m[ 9]*_m[ 2]*_m[ 7] + _m[ 1]*_m[10]*_m[ 7] + _m[ 5]*_m[ 2]*_m[11] - _m[ 1]*_m[ 6]*_m[11]);
        inv._m[ 7] = invDet * (_m[ 4]*_m[10]*_m[ 3] - _m[ 8]*_m[ 6]*_m[ 3] + _m[ 8]*_m[ 2]*_m[ 7] - _m[ 0]*_m[10]*_m[ 7] - _m[ 4]*_m[ 2]*_m[11] + _m[ 0]*_m[ 6]*_m[11]);
        inv._m[11] = invDet * (_m[ 8]*_m[ 5]*_m[ 3] - _m[ 4]*_m[ 9]*_m[ 3] - _m[ 8]*_m[ 1]*_m[ 7] + _m[ 0]*_m[ 9]*_m[ 7] + _m[ 4]*_m[ 1]*_m[11] - _m[ 0]*_m[ 5]*_m[11]);
        inv._m[15] = invDet * (_m[ 4]*_m[ 9]*_m[ 2] - _m[ 8]*_m[ 5]*_m[ 2] + _m[ 8]*_m[ 1]*_m[ 6] - _m[ 0]*_m[ 9]*_m[ 6] - _m[ 4]*_m[ 1]*_m[10] + _m[ 0]*_m[ 5]*_m[10]);

        return inv;
    }
}
#endif // MATRIX4X4_H
