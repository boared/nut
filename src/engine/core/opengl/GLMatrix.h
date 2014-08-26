/** 
 * \file GLMatrix.h
 * \brief Template class definition for create and handle 4x4 matrices used in an
 * OpenGL program.
 * 
 * @author: Eder A. Perez.
 */

#ifndef GLMATRIX_H
#define GLMATRIX_H

#include <cstring>
#include <cmath>
#include "Vector3D.h"
#include "Vector4D.h"



namespace nut
{
    /**
     * GLMatrix.
     * 
     * Represents a 4x4 matrix for use in OpenGL for operations like rotation, scale,
     * translation, projection, etc.
     * 
     * When using this class as an affine matrix, the axis vectors are in columns.
     * 
     *                        | Xx Yx Zx Tx |
     * Ex.: Affine matrix M = | Xy Yy Zy Ty |
     *                        | Xz Yz Zz Tz |
     *                        |  0  0  0  1 |
     * where,
     * 
     * X-axis = (Xx, Xy, Xz)
     * Y-axis = (Yx, Yy, Yz)
     * Z-axis = (Zx, Zy, Zz)
     * and a translation is represented by (Tx, Ty, Tz).
     * 
     * When applied to a vector, the vector must be located at right side.
     * 
     * Ex.: u = M x v
     * 
     * The matrix's values access order is column-major like in OpenGL:
     * 
     *          |  0  4  8 12 |
     * Ex.: M = |  1  5  9 13 |
     *          |  2  6 10 14 |
     *          |  3  7 11 15 |
     */
    template<typename T> class GLMatrix
    {
        public:

        /// Constant matrices ///

        static const GLMatrix IDENTITY;   /**< Identity matrix. */
        static const GLMatrix ZERO;       /**< Zero matrix. */
        static const GLMatrix ZEROAFFINE; /**< Zero affine matrix. */



        /// Constructors ///

        /**
         * Default constructor.
         * 
         * Instantiates an identity matrix.
         */
        GLMatrix()
        {
            memset(_m, 0, sizeof(T) * 16);
            _m[0] = _m[5] = _m[10] = _m [15] = T(1.0);
        }

        /**
         * Copy constructor.
         * 
         * Instantiates a copy of input matrix.
         * 
         * @param m A GLMatrix.
         */
        GLMatrix(const GLMatrix& m)
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
        GLMatrix(const T a11, const T a12, const T a13, const T a14,
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
         * Verify if the matrix is an affine matrix.
         * 
         * @return True if matrix is affine, false otherwise.
         */
        bool isAffine() const
        {
            return _m[ 3] == T(0.0) && _m[ 7] == T(0.0) && _m[11] == T(0.0) && _m[15] == T(1.0);
        }

        /**
         * Compute the inverse matrix.
         * 
         * @return The inverse matrix if it exists. Otherwise, returns ZERO matrix.
         */
        GLMatrix inverse() const
        {
            T det = determinant();

            // If matrix is affine, compute inverse in a cheaper way
            if (isAffine())
            {
                return _affineInverse(det);
            }
            // Otherwise, compute inverse for a general matrix
            else
            {
                return _generalInverse(det);
            }
        }

        /**
         * Compute the matrix's determinant.
         * 
         * @return The matrix's determinant.
         */
        T determinant() const
        {
            if ( isAffine() )
            {
                return _m[ 4]*_m[ 9]*_m[ 2] - _m[ 8]*_m[ 5]*_m[ 2] +
                       _m[ 8]*_m[ 1]*_m[ 6] - _m[ 0]*_m[ 9]*_m[ 6] +
                       _m[ 0]*_m[ 5]*_m[10] - _m[ 4]*_m[ 1]*_m[10];
            }
            else
            {
                return
                _m[12]*_m[ 9]*_m[ 6]*_m[ 3] - _m[ 8]*_m[13]*_m[ 6]*_m[ 3] - _m[12]*_m[ 5]*_m[10]*_m[ 3] + _m[ 4]*_m[13]*_m[10]*_m[ 3] +
                _m[ 8]*_m[ 5]*_m[14]*_m[ 3] - _m[ 4]*_m[ 9]*_m[14]*_m[ 3] - _m[12]*_m[ 9]*_m[ 2]*_m[ 7] + _m[ 8]*_m[13]*_m[ 2]*_m[ 7] +
                _m[12]*_m[ 1]*_m[10]*_m[ 7] - _m[ 0]*_m[13]*_m[10]*_m[ 7] - _m[ 8]*_m[ 1]*_m[14]*_m[ 7] + _m[ 0]*_m[ 9]*_m[14]*_m[ 7] +
                _m[12]*_m[ 5]*_m[ 2]*_m[11] - _m[ 4]*_m[13]*_m[ 2]*_m[11] - _m[12]*_m[ 1]*_m[ 6]*_m[11] + _m[ 0]*_m[13]*_m[ 6]*_m[11] +
                _m[ 4]*_m[ 1]*_m[14]*_m[11] - _m[ 0]*_m[ 5]*_m[14]*_m[11] - _m[ 8]*_m[ 5]*_m[ 2]*_m[15] + _m[ 4]*_m[ 9]*_m[ 2]*_m[15] +
                _m[ 8]*_m[ 1]*_m[ 6]*_m[15] - _m[ 0]*_m[ 9]*_m[ 6]*_m[15] - _m[ 4]*_m[ 1]*_m[10]*_m[15] + _m[ 0]*_m[ 5]*_m[10]*_m[15];
            }
        }

        /**
         * Compute the transposed matrix.
         * 
         * @return The transposed matrix.
         */
        GLMatrix transpose() const
        {
            return GLMatrix(_m[ 0], _m[ 1], _m[ 2], _m[ 3],
                            _m[ 4], _m[ 5], _m[ 6], _m[ 7],
                            _m[ 8], _m[ 9], _m[10], _m[11],
                            _m[12], _m[13], _m[14], _m[15]);
        }

        /**
         * Set a rotation matrix.
         * 
         * The angles are given in radians and the rotation is executed in the order X->Y->Z.
         * 
         * @param rx Rotation angle in X-axis.
         * @param ry Rotation angle in Y-axis.
         * @param rz Rotation angle in Z-axis.
         */
        void setRotation(T rx, T ry, T rz);

        /**
         * Set a scale matrix.
         * 
         * @param sx Scale factor in X-axis.
         * @param sy Scale factor in Y-axis.
         * @param sz Scale factor in Z-axis.
         */
        void setScale(T sx, T sy, T sz)
        {
            setIdentity();
            _m[ 0] = sx;
            _m[ 5] = sy;
            _m[10] = sz;
        }

        /**
         * Set a translation matrix.
         * 
         * @param tx Translation in X-axis.
         * @param ty Translation in Y-axis.
         * @param tz Translation in Z-axis.
         */
        void setTranslation(T tx, T ty, T tz)
        {
            setIdentity();
            _m[12] = tx;
            _m[13] = ty;
            _m[14] = tz;
        }

        /**
         * Append a rotation matrix to the current matrix.
         * 
         * The angles are given in radians and the rotation is executed in the order X->Y->Z.
         * 
         * @param rx Rotation angle in X-axis.
         * @param ry Rotation angle in Y-axis.
         * @param rz Rotation angle in Z-axis.
         */
        void rotate(T rx, T ry, T rz);

        /**
         * Append a scale matrix to the current matrix.
         * 
         * If you don't want to apply a scale in some axis, put its value to 1.
         * Appending zero values scales vectors to zero in its components.
         * 
         * @param sx Scale factor in X-axis.
         * @param sy Scale factor in Y-axis.
         * @param sz Scale factor in Z-axis.
         */
        void scale(T sx, T sy, T sz)
        {
            _m[ 0] *= sx;
            _m[ 5] *= sy;
            _m[10] *= sz;
        }

        /**
         * Append a translation matrix to the current matrix.
         * 
         * @param tx Translation in X-axis.
         * @param ty Translation in Y-axis.
         * @param tz Translation in Z-axis.
         */
        void translate(T tx, T ty, T tz)
        {
            _m[12] += tx;
            _m[13] += ty;
            _m[14] += tz;
        }

        /**
         * Set the camera configuration.
         * 
         * source: http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
         * 
         * @param (eyeX, eyeY, eyeZ) Specifies the position of the eye point.
         * @param (centerX, centerY, centerY) Specifies the position of the reference point.
         * @param (upX, upY, upZ) Specifies the direction of the up vector.
         */
        void setLookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ);

        /**
         * Set a frustum matrix.
         * 
         * From OpenGL Programming Guide: The Official Guide to Programming OpenGL,
         * version 4.3 page 227.
         * 
         * WARNING: If parameters are not conformed, the identity matrix is set.
         * 
         * @param left, right Specify the coordinates for the left and right vertical clipping planes.
         * @param bottom, top Specify the coordinates for the bottom and top horizontal clipping planes.
         * @param zNear, zFar Specify the distances to the near and far depth clipping planes. Both
         * distances must be positive.
         */
        void setFrustum(T left, T right, T bottom, T top, T zNear, T zFar)
        {
            if ( (right == left) || (top == bottom) || (zNear == zFar) || (zNear < T(0.0)) || (zFar < T(0.0)) )
            {
                setIdentity();
                return;
            }

            clear();
            _m[ 0] = (zNear + zNear) / (right - left);
            _m[ 8] = (right + left) / (right - left);
            _m[ 5] = (zNear + zNear) / (top - bottom);
            _m[ 9] = (top + bottom) / (top - bottom);
            _m[10] = -(zFar + zNear) / (zFar - zNear);
            _m[14] = (-2.0 * zFar * zNear) / (zFar - zNear);
            _m[11] = -1.0;
        }

        /**
         * Set an orthographic matrix.
         * 
         * From OpenGL Programming Guide: The Official Guide to Programming OpenGL,
         * version 4.3 page 230.
         * 
         * WARNING: If parameters are not conformed, the identity matrix is set.
         * 
         * @param left, right Specify the coordinates for the left and right vertical clipping planes.
         * @param bottom, top Specify the coordinates for the bottom and top horizontal clipping planes.
         * @param zNear, zFar Specify the distances to the nearer and farther depth clipping planes.
         * These values are negative if the plane is to be behind the viewer.
         */
        void setOrtho(T left, T right, T bottom, T top, T zNear, T zFar)
        {
            if ( (right == left) || (top == bottom) || (zNear == zFar) )
            {
                setIdentity();
                return;
            }

            clear();
            _m[ 0] = 2.0 / (right - left);
            _m[12] = -(right + left) / (right - left);
            _m[ 5] = 2.0 / (top - bottom);
            _m[13] = -(top + bottom) / (top - bottom);
            _m[10] = -2.0 / (zFar - zNear);
            _m[14] = -(zFar + zNear) / (zFar - zNear);
            _m[15] = 1.0;
        }

        /**
         * Set a perspective projection matrix.
         * 
         * WARNING: If parameters are not conformed, the identity matrix is set.
         * 
         * @param fovy Specifies the field of view angle, in DEGREES, in the y direction.
         * @param aspect Specifies the aspect ratio that determines the field of view
         * in the x direction. The aspect ratio is the ratio of x (width) to y (height).
         * @param zNear Specifies the distance from the viewer to the near clipping plane (always positive).
         * @param zFar Specifies the distance from the viewer to the far clipping plane (always positive).
         */
        void setPerspective(T fovY, T aspect, T zNear, T zFar)
        {
            // The constant value 0.01745329251994329576923690768489 represents pi / 180
            T top = zNear * tan( fovY * T(0.5 * 0.01745329251994329576923690768489) );
            T right = top * aspect;
            setFrustum(-right, right, -top, top, zNear, zFar);
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
         * Multiply a matrix by a 3D vector. In order to multiply to a 4x4 matrix,
         * a vector must has four components. In this case, the fourth vector
         * component is always considered as having one as its value.
         * 
         * @param v A 3D vector.
         * @return A 3D vector resulting from the matrix multiplication by @v.
         */
        Vector3D<T> operator * (const Vector3D<T>& v) const
        {
            return Vector3D<T>(_m[ 0] * v.x + _m[ 4] * v.y + _m[ 8] * v.z + _m[12],
                               _m[ 1] * v.x + _m[ 5] * v.y + _m[ 9] * v.z + _m[13],
                               _m[ 2] * v.x + _m[ 6] * v.y + _m[10] * v.z + _m[14]);
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
        GLMatrix operator * (const T s) const
        {
            return GLMatrix(_m[ 0] *  s, _m[ 4] *  s, _m[ 8] *  s, _m[12] *  s,
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
        friend GLMatrix operator * (const T s, const GLMatrix& m)
        {
            return GLMatrix(m._m[ 0] *  s, m._m[ 4] *  s, m._m[ 8] *  s, m._m[12] *  s,
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
        GLMatrix& operator *= (const T s)
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
        GLMatrix operator * (const GLMatrix& m) const
        {
            return GLMatrix(_m[ 0] * m._m[ 0] + _m[ 4] * m._m[ 1] + _m[ 8] * m._m[ 2] + _m[12] * m._m[ 3],
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
        GLMatrix& operator *= (const GLMatrix& m)
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
        GLMatrix operator / (const T s) const
        {
            T rScalar = T(1.0) / s;

            return GLMatrix(_m[ 0] * rScalar, _m[ 4] * rScalar, _m[ 8] * rScalar, _m[12] * rScalar,
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
        GLMatrix& operator /= (const T s)
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
        GLMatrix operator + (const GLMatrix& m) const
        {
            return GLMatrix(_m[ 0] + m[ 0], _m[ 4] + m[ 4], _m[ 8] + m[ 8], _m[12] + m[12],
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
        GLMatrix& operator += (const GLMatrix& m)
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
        GLMatrix operator - (const GLMatrix& m) const
        {
            return GLMatrix(_m[ 0] - m[ 0], _m[ 4] - m[ 4], _m[ 8] - m[ 8], _m[12] - m[12],
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
        GLMatrix& operator -= (const GLMatrix& m)
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
        bool operator == ( const GLMatrix& m ) const
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
        bool operator != ( const GLMatrix& m ) const
        {
            return std::fabs(_m[ 0] - m[ 0]) >= 1e-15 || std::fabs(_m[ 4] - m[ 4]) >= 1e-15 || std::fabs(_m[ 8] - m[ 8]) >= 1e-15 || std::fabs(_m[12] - m[12]) >= 1e-15 ||
                   std::fabs(_m[ 1] - m[ 1]) >= 1e-15 || std::fabs(_m[ 5] - m[ 5]) >= 1e-15 || std::fabs(_m[ 9] - m[ 9]) >= 1e-15 || std::fabs(_m[13] - m[13]) >= 1e-15 ||
                   std::fabs(_m[ 2] - m[ 2]) >= 1e-15 || std::fabs(_m[ 6] - m[ 6]) >= 1e-15 || std::fabs(_m[10] - m[10]) >= 1e-15 || std::fabs(_m[14] - m[14]) >= 1e-15 ||
                   std::fabs(_m[ 3] - m[ 3]) >= 1e-15 || std::fabs(_m[ 7] - m[ 7]) >= 1e-15 || std::fabs(_m[11] - m[11]) >= 1e-15 || std::fabs(_m[15] - m[15]) >= 1e-15;
        }



        private:

        /// Private attributes ///

        T _m[16]; /**< Stores the sixteen values of the 4x4 matrix. */



        /// Private methods ///

        /**
         * Computes the inverse matrix of a general 4x4 matrix.
         * 
         * @param determinant Matrix's determinant.
         * @return The inverse matrix if it exists. Otherwise, returns ZERO matrix.
         */
        GLMatrix _generalInverse(T determinant) const;

        /**
         * Computes the inverse matrix of an affine 4x4 matrix.
         * 
         * @param determinant Matrix's determinant.
         * @return The inverse matrix if it exists. Otherwise, returns ZERO matrix.
         */
        GLMatrix _affineInverse(T determinant) const;

    };

    template<typename T> const GLMatrix<T> GLMatrix<T>::IDENTITY( T(1.0), T(0.0), T(0.0), T(0.0),
                                                                  T(0.0), T(1.0), T(0.0), T(0.0),
                                                                  T(0.0), T(0.0), T(1.0), T(0.0),
                                                                  T(0.0), T(0.0), T(0.0), T(1.0) );

    template<typename T> const GLMatrix<T> GLMatrix<T>::ZERO( T(0.0), T(0.0), T(0.0), T(0.0),
                                                              T(0.0), T(0.0), T(0.0), T(0.0),
                                                              T(0.0), T(0.0), T(0.0), T(0.0),
                                                              T(0.0), T(0.0), T(0.0), T(0.0) );

    template<typename T> const GLMatrix<T> GLMatrix<T>::ZEROAFFINE( T(0.0), T(0.0), T(0.0), T(0.0),
                                                                    T(0.0), T(0.0), T(0.0), T(0.0),
                                                                    T(0.0), T(0.0), T(0.0), T(0.0),
                                                                    T(0.0), T(0.0), T(0.0), T(1.0) );



    template<typename T> void GLMatrix<T>::setLookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
    {
        // Set vectors
        T f[3] = { centerX - eyeX, centerY - eyeY, centerZ - eyeZ };
        T up[3] = { upX, upY, upZ };

        T fLength = sqrt( f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
        T upLength = sqrt( up[0] * up[0] + up[1] * up[1] + up[2] * up[2]);

        f[0] = f[0] / fLength;
        f[1] = f[1] / fLength;
        f[2] = f[2] / fLength;

        up[0] = up[0] / upLength;
        up[1] = up[1] / upLength;
        up[2] = up[2] / upLength;

        // s is the crossproduct f X up
        T s[3] = { f[1] * up[2] - f[2] * up[1],
                   f[2] * up[0] - f[0] * up[2],
                   f[0] * up[1] - f[1] * up[0] };

        T sLength = sqrt( s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);

        T unitS[3] = { s[0] / sLength, s[1] / sLength, s[2] / sLength };
        T u[3] = { unitS[1] * f[2] - unitS[2] * f[1],
                   unitS[2] * f[0] - unitS[0] * f[2],
                   unitS[0] * f[1] - unitS[1] * f[0] };

        _m[ 0] = unitS[0];
        _m[ 4] = unitS[1];
        _m[ 8] = unitS[2];
        _m[12] = T(0.0);

        _m[ 1] = u[0];
        _m[ 5] = u[1];
        _m[ 9] = u[2];
        _m[13] = T(0.0);

        _m[ 2] = -f[0];
        _m[ 6] = -f[1];
        _m[10] = -f[2];
        _m[14] = T(0.0);

        _m[ 3] = T(0.0);
        _m[ 7] = T(0.0);
        _m[11] = T(0.0);
        _m[15] = T(1.0);

        translate(-eyeX, -eyeY, -eyeZ);
    }



    template<typename T> void GLMatrix<T>::setRotation(T rx, T ry, T rz)
    {
        T cosx = cos(rx);
        T cosy = cos(ry);
        T cosz = cos(rz);

        T sinx = sin(rx);
        T siny = sin(ry);
        T sinz = sin(rz);

        _m[ 0] = cosz * cosy;
        _m[ 4] = cosz * siny * sinx - sinz * cosx;
        _m[ 8] = cosz * siny * cosx + sinz * sinx;
        _m[12] = T(0.0);

        _m[ 1] = sinz * cosy;
        _m[ 5] = sinz * siny * sinx + cosz * cosx;
        _m[ 9] = sinz * siny * cosx - cosz * sinx;
        _m[13] = T(0.0);

        _m[ 2] = -siny;
        _m[ 6] = cosy * sinx;
        _m[10] = cosy * cosx;
        _m[14] = T(0.0);

        _m[ 3] = T(0.0);
        _m[ 7] = T(0.0);
        _m[11] = T(0.0);
        _m[15] = T(1.0);
    }



    template<typename T> void GLMatrix<T>::rotate(T rx, T ry, T rz)
    {
        T r[16];

        T cosx = cos(rx);
        T cosy = cos(ry);
        T cosz = cos(rz);

        T sinx = sin(rx);
        T siny = sin(ry);
        T sinz = sin(rz);

        r[ 0] = cosz * cosy * _m[ 0] + (cosz * siny * sinx - sinz * cosx) * _m[ 1] + (cosz * siny * cosx + sinz * sinx) * _m[ 2];
        r[ 4] = cosz * cosy * _m[ 4] + (cosz * siny * sinx - sinz * cosx) * _m[ 5] + (cosz * siny * cosx + sinz * sinx) * _m[ 6];
        r[ 8] = cosz * cosy * _m[ 8] + (cosz * siny * sinx - sinz * cosx) * _m[ 9] + (cosz * siny * cosx + sinz * sinx) * _m[10];
        r[12] = cosz * cosy * _m[12] + (cosz * siny * sinx - sinz * cosx) * _m[13] + (cosz * siny * cosx + sinz * sinx) * _m[14];

        r[ 1] = sinz * cosy * _m[ 0] + (sinz * siny * sinx + cosz * cosx) * _m[ 1] + (sinz * siny * cosx - cosz * sinx) * _m[ 2];
        r[ 5] = sinz * cosy * _m[ 4] + (sinz * siny * sinx + cosz * cosx) * _m[ 5] + (sinz * siny * cosx - cosz * sinx) * _m[ 6];
        r[ 9] = sinz * cosy * _m[ 8] + (sinz * siny * sinx + cosz * cosx) * _m[ 9] + (sinz * siny * cosx - cosz * sinx) * _m[10];
        r[13] = sinz * cosy * _m[12] + (sinz * siny * sinx + cosz * cosx) * _m[13] + (sinz * siny * cosx - cosz * sinx) * _m[14];

        r[ 2] = (-siny) * _m[ 0] + cosy * sinx * _m[ 1] + cosy * cosx * _m[ 2];
        r[ 6] = (-siny) * _m[ 4] + cosy * sinx * _m[ 5] + cosy * cosx * _m[ 6];
        r[10] = (-siny) * _m[ 8] + cosy * sinx * _m[ 9] + cosy * cosx * _m[10];
        r[14] = (-siny) * _m[12] + cosy * sinx * _m[13] + cosy * cosx * _m[14];

        r[ 3] = T(0.0);
        r[ 7] = T(0.0);
        r[11] = T(0.0);
        r[15] = T(1.0);

        memcpy(_m, r, sizeof(T) * 16);
    }



    template<typename T> GLMatrix<T> GLMatrix<T>::_generalInverse(T determinant) const
    {
        if (fabs(determinant) < 1e-15)
            return GLMatrix<T>::ZERO;

        GLMatrix inv;

        inv._m[ 0] = _m[ 9]*_m[14]*_m[ 7] - _m[13]*_m[10]*_m[ 7] + _m[13]*_m[ 6]*_m[11] - _m[ 5]*_m[14]*_m[11] - _m[ 9]*_m[ 6]*_m[15] + _m[ 5]*_m[10]*_m[15];
        inv._m[ 4] = _m[12]*_m[10]*_m[ 7] - _m[ 8]*_m[14]*_m[ 7] - _m[12]*_m[ 6]*_m[11] + _m[ 4]*_m[14]*_m[11] + _m[ 8]*_m[ 6]*_m[15] - _m[ 4]*_m[10]*_m[15];
        inv._m[ 8] = _m[ 8]*_m[13]*_m[ 7] - _m[12]*_m[ 9]*_m[ 7] + _m[12]*_m[ 5]*_m[11] - _m[ 4]*_m[13]*_m[11] - _m[ 8]*_m[ 5]*_m[15] + _m[ 4]*_m[ 9]*_m[15];
        inv._m[12] = _m[12]*_m[ 9]*_m[ 6] - _m[ 8]*_m[13]*_m[ 6] - _m[12]*_m[ 5]*_m[10] + _m[ 4]*_m[13]*_m[10] + _m[ 8]*_m[ 5]*_m[14] - _m[ 4]*_m[ 9]*_m[14];

        inv._m[ 1] = _m[13]*_m[10]*_m[ 3] - _m[ 9]*_m[14]*_m[ 3] - _m[13]*_m[ 2]*_m[11] + _m[ 1]*_m[14]*_m[11] + _m[ 9]*_m[ 2]*_m[15] - _m[ 1]*_m[10]*_m[15];
        inv._m[ 5] = _m[ 8]*_m[14]*_m[ 3] - _m[12]*_m[10]*_m[ 3] + _m[12]*_m[ 2]*_m[11] - _m[ 0]*_m[14]*_m[11] - _m[ 8]*_m[ 2]*_m[15] + _m[ 0]*_m[10]*_m[15];
        inv._m[ 9] = _m[12]*_m[ 9]*_m[ 3] - _m[ 8]*_m[13]*_m[ 3] - _m[12]*_m[ 1]*_m[11] + _m[ 0]*_m[13]*_m[11] + _m[ 8]*_m[ 1]*_m[15] - _m[ 0]*_m[ 9]*_m[15];
        inv._m[13] = _m[ 8]*_m[13]*_m[ 2] - _m[12]*_m[ 9]*_m[ 2] + _m[12]*_m[ 1]*_m[10] - _m[ 0]*_m[13]*_m[10] - _m[ 8]*_m[ 1]*_m[14] + _m[ 0]*_m[ 9]*_m[14];

        inv._m[ 2] = _m[ 5]*_m[14]*_m[ 3] - _m[13]*_m[ 6]*_m[ 3] + _m[13]*_m[ 2]*_m[ 7] - _m[ 1]*_m[14]*_m[ 7] - _m[ 5]*_m[ 2]*_m[15] + _m[ 1]*_m[ 6]*_m[15];
        inv._m[ 6] = _m[12]*_m[ 6]*_m[ 3] - _m[ 4]*_m[14]*_m[ 3] - _m[12]*_m[ 2]*_m[ 7] + _m[ 0]*_m[14]*_m[ 7] + _m[ 4]*_m[ 2]*_m[15] - _m[ 0]*_m[ 6]*_m[15];
        inv._m[10] = _m[ 4]*_m[13]*_m[ 3] - _m[12]*_m[ 5]*_m[ 3] + _m[12]*_m[ 1]*_m[ 7] - _m[ 0]*_m[13]*_m[ 7] - _m[ 4]*_m[ 1]*_m[15] + _m[ 0]*_m[ 5]*_m[15];
        inv._m[14] = _m[12]*_m[ 5]*_m[ 2] - _m[ 4]*_m[13]*_m[ 2] - _m[12]*_m[ 1]*_m[ 6] + _m[ 0]*_m[13]*_m[ 6] + _m[ 4]*_m[ 1]*_m[14] - _m[ 0]*_m[ 5]*_m[14];

        inv._m[ 3] = _m[ 9]*_m[ 6]*_m[ 3] - _m[ 5]*_m[10]*_m[ 3] - _m[ 9]*_m[ 2]*_m[ 7] + _m[ 1]*_m[10]*_m[ 7] + _m[ 5]*_m[ 2]*_m[11] - _m[ 1]*_m[ 6]*_m[11];
        inv._m[ 7] = _m[ 4]*_m[10]*_m[ 3] - _m[ 8]*_m[ 6]*_m[ 3] + _m[ 8]*_m[ 2]*_m[ 7] - _m[ 0]*_m[10]*_m[ 7] - _m[ 4]*_m[ 2]*_m[11] + _m[ 0]*_m[ 6]*_m[11];
        inv._m[11] = _m[ 8]*_m[ 5]*_m[ 3] - _m[ 4]*_m[ 9]*_m[ 3] - _m[ 8]*_m[ 1]*_m[ 7] + _m[ 0]*_m[ 9]*_m[ 7] + _m[ 4]*_m[ 1]*_m[11] - _m[ 0]*_m[ 5]*_m[11];
        inv._m[15] = _m[ 4]*_m[ 9]*_m[ 2] - _m[ 8]*_m[ 5]*_m[ 2] + _m[ 8]*_m[ 1]*_m[ 6] - _m[ 0]*_m[ 9]*_m[ 6] - _m[ 4]*_m[ 1]*_m[10] + _m[ 0]*_m[ 5]*_m[10];

        return inv * ( T(1.0) / determinant );
    }



    template<typename T> GLMatrix<T> GLMatrix<T>::_affineInverse(T determinant) const
    {
        if (fabs(determinant) < 1e-15)
            return GLMatrix<T>::ZERO;

        GLMatrix inv;

        inv._m[ 0] = _m[ 5]*_m[10] - _m[ 9]*_m[ 6];
        inv._m[ 4] = _m[ 8]*_m[ 6] - _m[ 4]*_m[10];
        inv._m[ 8] = _m[ 4]*_m[ 9] - _m[ 8]*_m[ 5];
        inv._m[12] = _m[12]*_m[ 9]*_m[ 6] - _m[ 8]*_m[13]*_m[ 6] - _m[12]*_m[ 5]*_m[10] + _m[ 4]*_m[13]*_m[10] + _m[ 8]*_m[ 5]*_m[14] - _m[ 4]*_m[ 9]*_m[14];
        inv._m[ 1] = _m[ 9]*_m[ 2] - _m[ 1]*_m[10];
        inv._m[ 5] = _m[ 0]*_m[10] - _m[ 8]*_m[ 2];
        inv._m[ 9] = _m[ 8]*_m[ 1] - _m[ 0]*_m[ 9];
        inv._m[13] = _m[ 8]*_m[13]*_m[ 2] - _m[12]*_m[ 9]*_m[ 2] + _m[12]*_m[ 1]*_m[10] - _m[ 0]*_m[13]*_m[10] - _m[ 8]*_m[ 1]*_m[14] + _m[ 0]*_m[ 9]*_m[14];
        inv._m[ 2] = _m[ 1]*_m[ 6] - _m[ 5]*_m[ 2];
        inv._m[ 6] = _m[ 4]*_m[ 2] - _m[ 0]*_m[ 6];
        inv._m[10] = _m[ 0]*_m[ 5] - _m[ 4]*_m[ 1];
        inv._m[14] = _m[12]*_m[ 5]*_m[ 2] - _m[ 4]*_m[13]*_m[ 2] - _m[12]*_m[ 1]*_m[ 6] + _m[ 0]*_m[13]*_m[ 6] + _m[ 4]*_m[ 1]*_m[14] - _m[ 0]*_m[ 5]*_m[14];
        inv._m[ 3] = T(0.0);
        inv._m[ 7] = T(0.0);
        inv._m[11] = T(0.0);
        inv._m[15] = _m[ 4]*_m[ 9]*_m[ 2] - _m[ 8]*_m[ 5]*_m[ 2] + _m[ 8]*_m[ 1]*_m[ 6] - _m[ 0]*_m[ 9]*_m[ 6] - _m[ 4]*_m[ 1]*_m[10] + _m[ 0]*_m[ 5]*_m[10];

        return inv * ( T(1.0) / determinant );
    }
}
#endif // GLMATRIX_H
