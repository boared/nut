/** 
 * \file Matrix3x3.h
 * \brief Template class definition for create and handle 3x3 matrices.
 * 
 * @author: Eder A. Perez.
 */

#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <cstring>
#include <cmath>
#include "Vector3D.h"



namespace nut
{
    /**
     * Matrix3x3.
     * 
     * Represents a 3x3 matrix for general purpose. When applied to a vector,
     * the vector must be located at right side.
     * 
     * Ex.: u = M x v
     * 
     * The matrix's values access order is column-major:
     * 
     *          | 0  3  6 |
     * Ex.: M = | 1  4  7 |
     *          | 2  5  8 |
     */
    template<typename T> class Matrix3x3
    {
        public:

        /// Constant matrices ///

        static const Matrix3x3 IDENTITY;   /**< Identity matrix. */
        static const Matrix3x3 ZERO;       /**< Zero matrix. */



        /// Constructors ///

        /**
         * Default constructor.
         * 
         * Instantiates an identity matrix.
         */
        Matrix3x3()
        {
            memset(_m, 0, sizeof(T) * 9);
            _m[0] = _m[4] = _m[8] = T(1.0);
        }

        /**
         * Copy constructor.
         * 
         * Instantiates a copy of input matrix.
         * 
         * @param m A Matrix3x3.
         */
        Matrix3x3(const Matrix3x3& m)
        {
            memcpy(_m, m._m, sizeof(T) * 9);
        }

        /**
         * Constructor.
         * 
         * Instatiates a matrix out of scalar values.
         * 
         * @param ann A value at position nn of matrix.
         */
        Matrix3x3(const T a11, const T a12, const T a13,
                  const T a21, const T a22, const T a23,
                  const T a31, const T a32, const T a33 )
        {
            _m[0] = a11; _m[3] = a12; _m[6] = a13;
            _m[1] = a21; _m[4] = a22; _m[7] = a23;
            _m[2] = a31; _m[5] = a32; _m[8] = a33;
        }



        /// Methods ///

        /**
         * Set zero to all values of the matrix.
         */
        void clear()
        {
            memset(_m, 0, sizeof(T) * 9);
        }

        /**
         * Set matrix as identity.
         */
        void setIdentity()
        {
            memset(_m, 0, sizeof(T) * 9);
            _m[0] = _m[4] = _m[8] = T(1.0);
        }

        /**
         * Compute the inverse matrix.
         * 
         * @return The inverse matrix if it exists. Otherwise, returns ZERO matrix.
         */
        Matrix3x3 inverse() const;

        /**
         * Compute the matrix's determinant.
         * 
         * @return The matrix's determinant.
         */
        T determinant() const
        {
            return
            _m[0] * (_m[4]*_m[8] - _m[7]*_m[5]) -
            _m[3] * (_m[1]*_m[8] - _m[7]*_m[2]) +
            _m[6] * (_m[1]*_m[5] - _m[4]*_m[2]);
        }

        /**
         * Compute the transposed matrix.
         * 
         * @return The transposed matrix.
         */
        Matrix3x3 transpose() const
        {
            return Matrix3x3(_m[0], _m[1], _m[2],
                             _m[3], _m[4], _m[5],
                             _m[6], _m[7], _m[8]);
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
         * Multiply a matrix by a 3D vector.
         * 
         * @param v A 3D vector.
         * @return A 3D vector resulting from the matrix multiplication by @v.
         */
        Vector3D<T> operator * (const Vector3D<T>& v) const
        {
            return Vector3D<T>(_m[0] * v.x + _m[3] * v.y + _m[6] * v.z,
                               _m[1] * v.x + _m[4] * v.y + _m[7] * v.z,
                               _m[2] * v.x + _m[5] * v.y + _m[8] * v.z);
        }

        /**
         * Multiply a matrix by an scalar.
         * 
         * @param s A scalar value.
         * @return A matrix multiplied by a scalar.
         */
        Matrix3x3 operator * (const T s) const
        {
            return Matrix3x3(_m[0] *  s, _m[3] *  s, _m[6] *  s,
                             _m[1] *  s, _m[4] *  s, _m[7] *  s,
                             _m[2] *  s, _m[5] *  s, _m[8] *  s);
        }

        /**
         * Multiply a matrix by an scalar.
         * 
         * @param s A scalar value.
         * @param m An input matrix.
         * @return @m multiplied by a scalar.
         */
        friend Matrix3x3 operator * (const T s, const Matrix3x3& m)
        {
            return Matrix3x3(m._m[0] *  s, m._m[3] *  s, m._m[6] *  s,
                             m._m[1] *  s, m._m[4] *  s, m._m[7] *  s,
                             m._m[2] *  s, m._m[5] *  s, m._m[8] *  s);
        }

        /**
         * Multiplication by an scalar.
         * 
         * @param s A scalar value.
         * @return This matrix multiplied by a scalar.
         */
        Matrix3x3& operator *= (const T s)
        {
            _m[0] *= s; _m[3] *= s; _m[6] *= s;
            _m[1] *= s; _m[4] *= s; _m[7] *= s;
            _m[2] *= s; _m[5] *= s; _m[8] *= s;

            return *this;
        }

        /**
         * Multiply two matrices.
         * 
         * @param m A matrix.
         * @return @this * @m.
         */
        Matrix3x3 operator * (const Matrix3x3& m) const
        {
            return Matrix3x3(_m[0] * m._m[0] + _m[3] * m._m[1] + _m[6] * m._m[2],
                             _m[0] * m._m[3] + _m[3] * m._m[4] + _m[6] * m._m[5],
                             _m[0] * m._m[6] + _m[3] * m._m[7] + _m[6] * m._m[8],

                             _m[1] * m._m[0] + _m[4] * m._m[1] + _m[7] * m._m[2],
                             _m[1] * m._m[3] + _m[4] * m._m[4] + _m[7] * m._m[5],
                             _m[1] * m._m[6] + _m[4] * m._m[7] + _m[7] * m._m[8],

                             _m[2] * m._m[0] + _m[5] * m._m[1] + _m[8] * m._m[2],
                             _m[2] * m._m[3] + _m[5] * m._m[4] + _m[8] * m._m[5],
                             _m[2] * m._m[6] + _m[5] * m._m[7] + _m[8] * m._m[8]);
        }

        /**
         * Multiply two matrices.
         * 
         * The order of multiplication is: m1 *= m2 <=> m1 = m1 * m2.
         * 
         * @param m A matrix.
         * @return @this * @m.
         */
        Matrix3x3& operator *= (const Matrix3x3& m)
        {
            T r[9];

            r[0] = _m[0] * m._m[0] + _m[3] * m._m[1] + _m[6] * m._m[2];
            r[3] = _m[0] * m._m[3] + _m[3] * m._m[4] + _m[6] * m._m[5];
            r[6] = _m[0] * m._m[6] + _m[3] * m._m[7] + _m[6] * m._m[8];

            r[1] = _m[1] * m._m[0] + _m[4] * m._m[1] + _m[7] * m._m[2];
            r[4] = _m[1] * m._m[3] + _m[4] * m._m[4] + _m[7] * m._m[5];
            r[7] = _m[1] * m._m[6] + _m[4] * m._m[7] + _m[7] * m._m[8];

            r[2] = _m[2] * m._m[0] + _m[5] * m._m[1] + _m[8] * m._m[2];
            r[5] = _m[2] * m._m[3] + _m[5] * m._m[4] + _m[8] * m._m[5];
            r[8] = _m[2] * m._m[6] + _m[5] * m._m[7] + _m[8] * m._m[8];

            memcpy(_m, r, sizeof(T) * 9);

            return *this;
        }

        /**
         * Division by an scalar.
         * 
         * @param s A scalar value.
         * @return @this / s.
         */
        Matrix3x3 operator / (const T s) const
        {
            T rScalar = T(1.0) / s;

            return Matrix3x3(_m[0] * rScalar, _m[3] * rScalar, _m[6] * rScalar,
                             _m[1] * rScalar, _m[4] * rScalar, _m[7] * rScalar,
                             _m[2] * rScalar, _m[5] * rScalar, _m[8] * rScalar);
        }

        /**
         * Division by an scalar.
         * 
         * @param s A scalar value.
         * @return @this / s.
         */
        Matrix3x3& operator /= (const T s)
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
        Matrix3x3 operator + (const Matrix3x3& m) const
        {
            return Matrix3x3(_m[0] + m[0], _m[3] + m[3], _m[6] + m[6],
                             _m[1] + m[1], _m[4] + m[4], _m[7] + m[7],
                             _m[2] + m[2], _m[5] + m[5], _m[8] + m[8]);
        }

        /**
         * Matrix addition.
         * 
         * @param m A matrix.
         * @return @this + m.
         */
        Matrix3x3& operator += (const Matrix3x3& m)
        {
            _m[0] += m[0]; _m[3] += m[3]; _m[6] += m[6];
            _m[1] += m[1]; _m[4] += m[4]; _m[7] += m[7];
            _m[2] += m[2]; _m[5] += m[5]; _m[8] += m[8];

            return *this;
        }

        /**
         * Matrix subtraction.
         * 
         * @param m A matrix.
         * @return @this - m.
         */
        Matrix3x3 operator - (const Matrix3x3& m) const
        {
            return Matrix3x3(_m[0] - m[0], _m[3] - m[3], _m[6] - m[6],
                             _m[1] - m[1], _m[4] - m[4], _m[7] - m[7],
                             _m[2] - m[2], _m[5] - m[5], _m[8] - m[8]);
        }

        /**
         * Matrix subtraction.
         * 
         * @param m A matrix.
         * @return @this - m.
         */
        Matrix3x3& operator -= (const Matrix3x3& m)
        {
            _m[0] -= m[0]; _m[3] -= m[3]; _m[6] -= m[6];
            _m[1] -= m[1]; _m[4] -= m[4]; _m[7] -= m[7];
            _m[2] -= m[2]; _m[5] -= m[5]; _m[8] -= m[8];

            return *this;
        }

        /**
         * Tests two matrices for equality.
         * 
         * @param A matrix.
         */
        bool operator == ( const Matrix3x3& m ) const
        {
            return std::fabs(_m[0] - m[0]) < 1e-15 && std::fabs(_m[3] - m[3]) < 1e-15 && std::fabs(_m[6] - m[6]) < 1e-15 &&
                   std::fabs(_m[1] - m[1]) < 1e-15 && std::fabs(_m[4] - m[4]) < 1e-15 && std::fabs(_m[7] - m[7]) < 1e-15 &&
                   std::fabs(_m[2] - m[2]) < 1e-15 && std::fabs(_m[5] - m[5]) < 1e-15 && std::fabs(_m[8] - m[8]) < 1e-15;
        }

        /**
         * Tests two matrices for inequality.
         * 
         * @param A matrix.
         */
        bool operator != ( const Matrix3x3& m ) const
        {
            return std::fabs(_m[0] - m[0]) < 1e-15 || std::fabs(_m[3] - m[3]) < 1e-15 || std::fabs(_m[6] - m[6]) < 1e-15 ||
                   std::fabs(_m[1] - m[1]) < 1e-15 || std::fabs(_m[4] - m[4]) < 1e-15 || std::fabs(_m[7] - m[7]) < 1e-15 ||
                   std::fabs(_m[2] - m[2]) < 1e-15 || std::fabs(_m[5] - m[5]) < 1e-15 || std::fabs(_m[8] - m[8]) < 1e-15;
        }



        private:

        /// Private attributes ///

        T _m[9]; /**< Stores the sixteen values of the 3x3 matrix. */

    };

    template<typename T> const Matrix3x3<T> Matrix3x3<T>::IDENTITY(T(1.0), T(0.0), T(0.0),
                                                                   T(0.0), T(1.0), T(0.0),
                                                                   T(0.0), T(0.0), T(1.0));

    template<typename T> const Matrix3x3<T> Matrix3x3<T>::ZERO(T(0.0), T(0.0), T(0.0),
                                                               T(0.0), T(0.0), T(0.0),
                                                               T(0.0), T(0.0), T(0.0));

    template<typename T> Matrix3x3<T> Matrix3x3<T>::inverse() const
    {
        T det = determinant();

        if (fabs(det) < 1e-15)
            return Matrix3x3<T>::ZERO;

        T invDet = T(1.0) / det;

        return Matrix3x3( invDet * (_m[4]*_m[8] - _m[7]*_m[5]),
                          invDet * (_m[6]*_m[5] - _m[3]*_m[8]),
                          invDet * (_m[3]*_m[7] - _m[6]*_m[4]),
                         
                          invDet * (_m[7]*_m[2] - _m[1]*_m[8]),
                          invDet * (_m[0]*_m[8] - _m[6]*_m[2]),
                          invDet * (_m[6]*_m[1] - _m[0]*_m[7]),
                         
                          invDet * (_m[1]*_m[5] - _m[4]*_m[2]),
                          invDet * (_m[3]*_m[2] - _m[0]*_m[5]),
                          invDet * (_m[0]*_m[4] - _m[3]*_m[1]) );
    }
}
#endif // MATRIX3X3_H
