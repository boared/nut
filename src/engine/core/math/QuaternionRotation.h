/** 
 * \file QuaternionRotation.h
 * \brief Class definition for a rotation quaternion.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __QUATERNIONROTATION_H__
#define __QUATERNIONROTATION_H__

#include <cstring>
#include "Math.h"



namespace nut
{
	/**
     * \brief Quaternion rotation.
     * 
     * This class represents only unit quaternions representing rotations.
     * Rotations' direction follows the right-hand rule.
     * 
     * A quaternion q is represented by:
     *      q = <v * sin(a/2), cos(a/2)>,
     * where 'v' is a unit 3D vector and 'a' is the angle of rotation in radians.
     */
	template<typename T> class QuaternionRotation
	{
		public:

		/// Constructors ///

		/**
         * \brief Default constructor.
         */
		QuaternionRotation()
        {
            // Identity quaternion (zero rotation and length = 1)
            _q[0] = _q[1] = _q[2] = 0;
            _q[3] = 1;
        }

        /**
         * \brief Copy constructor.
         */
		QuaternionRotation(const QuaternionRotation& q)
        {
            _q[0] = q._q[0];
            _q[1] = q._q[1];
            _q[2] = q._q[2];
            _q[3] = q._q[3];
        }



        /// Methods ///

        /**
         * \brief Sets a rotation quaternion.
         * 
         * The angles are given in radians. If axis is zero-length, nothing is
         * changed.
         * 
         * @param axisX X-coordinate of rotation axis.
         * @param axisY Y-coordinate of rotation axis.
         * @param axisZ Z-coordinate of rotation axis.
         * @param angle Angle of rotation (in radians).
         */
        void setRotation(T axisX, T axisY, T axisZ, T angle)
        {
            // Check if axis is zero-length
            if (std::abs(axisX) > Math<T>::EPSILON || std::abs(axisY) > Math<T>::EPSILON || std::abs(axisZ) > Math<T>::EPSILON)
            {
                // Normalize axis
                T sqrLength = axisX * axisX + axisY * axisY + axisZ * axisZ;
                
                if ( Math<T>::abs( T(1.0) - sqrLength) > Math<T>::EPSILON)
                {
			        T rLength = T(1.0) / std::sqrt(sqrLength);

                    axisX *= rLength;
			        axisY *= rLength;
                    axisZ *= rLength;
                }

                angle *= T(0.5);

                T angleSin = sin(angle);
                _q[0] = axisX * angleSin;
                _q[1] = axisY * angleSin;
                _q[2] = axisZ * angleSin;
                _q[3] = cos(angle);
            }
        }

        /**
         * \brief Sets a rotation quaternion from euler's angles.
         * 
         * The angles are given in radians and the rotation is executed in the
         * order Y-axis => Z-axis => X-axis.
         * 
         * Source: euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.html (visited at 09/2013)
         * 
         * @param heading First rotation to be executed (in Y-axis).
         * @param attitude Second rotation to be executed (in Z-axis).
         * @param bank Third rotation to be executed (in X-axis).
         */
		void setRotation(T heading, T attitude, T bank)
        {
            T half_h = heading  * T(0.5);
            T half_a = attitude * T(0.5);
            T half_b = bank     * T(0.5);

            T c_hh = std::cos(half_h);
            T c_ha = std::cos(half_a);
            T c_hb = std::cos(half_b);

            T s_hh = std::sin(half_h);
            T s_ha = std::sin(half_a);
            T s_hb = std::sin(half_b);

            _q[0] = s_hh*s_ha*c_hb + c_hh*c_ha*s_hb;
            _q[1] = s_hh*c_ha*c_hb + c_hh*s_ha*s_hb;
            _q[2] = c_hh*s_ha*c_hb - s_hh*c_ha*s_hb;
            _q[3] = c_hh*c_ha*c_hb - s_hh*s_ha*s_hb;
        }

        /**
         * \brief Gets the rotation angle in radians.
         * 
         * @return The rotation angle in radians.
         */
        T getRotationAngle() const
        {
            return T(2.0) * std::acos(_q[3]);
        }

        /**
         * \brief Apply a rotation on a 3D vector.
         * 
         * @param x Vector x-coordinate.
         * @param y Vector y-coordinate.
         * @param z Vector z-coordinate.
         */
		void rotate(T& x, T& y, T& z) const
        {
            // q*V
            T qV[4];
            qV[0] =   _q[3] * x + _q[1] * z - _q[2] * y;
            qV[1] =   _q[3] * y + _q[2] * x - _q[0] * z;
            qV[2] =   _q[3] * z + _q[0] * y - _q[1] * x;
            qV[3] = - _q[0] * x - _q[1] * y - _q[2] * z;

            // q*V*q_
            x = -qV[3] * _q[0] + _q[3] * qV[0] + (qV[2] * _q[1] - qV[1] * _q[2]);
            y = -qV[3] * _q[1] + _q[3] * qV[1] + (qV[0] * _q[2] - qV[2] * _q[0]);
            z = -qV[3] * _q[2] + _q[3] * qV[2] + (qV[1] * _q[0] - qV[0] * _q[1]);
        }

        /**
         * \brief Returns the inverse quaternion.
         * 
         * The inverse of a unit rotation quaternion is its conjugate.
         */
        QuaternionRotation inverse() const
        {
            QuaternionRotation r;

            r._q[0] = -_q[0];
            r._q[1] = -_q[1];
            r._q[2] = -_q[2];
            r._q[3] =  _q[3];

            return r;
        }



		/// Class methods ///

        /**
         * \brief Computes the rotational interpolation between two quaternions.
         * 
         * @param qa First quaternion.
         * @param qb Second quaternion.
         * @param t Interpolation parameter.
         * @return The interpolated quaternion.
         */
        static QuaternionRotation lerp(const QuaternionRotation& qa, const QuaternionRotation& qb, T t)
        {
            QuaternionRotation q;

            q._q[0] = ( T(1.0) - t)*qa._q[0] + t*qb._q[0];
            q._q[1] = ( T(1.0) - t)*qa._q[1] + t*qb._q[1];
            q._q[2] = ( T(1.0) - t)*qa._q[2] + t*qb._q[2];
            q._q[3] = ( T(1.0) - t)*qa._q[3] + t*qb._q[3];

            // Normalize
            T rLength = T(1.0) / (std::sqrt(q._q[0] * q._q[0] + q._q[1] * q._q[1] + q._q[2] * q._q[2] + q._q[3] * q._q[3]));

            q._q[0] *= rLength;
            q._q[1] *= rLength;
            q._q[2] *= rLength;
            q._q[3] *= rLength;

            return q;
        }

        /**
         * \brief Computes the spherical interpolation between two quaternions.
         * 
         * @param qa First quaternion.
         * @param qb Second quaternion.
         * @param t Interpolation parameter.
         * @return The interpolated quaternion.
         */
        static QuaternionRotation slerp(const QuaternionRotation& q1, const QuaternionRotation& q2, T t)
        {
            QuaternionRotation q;

            T cos_q1  = q1._q[0] * q2._q[0] + q1._q[1] * q2._q[1] + q1._q[2] * q2._q[2] + q1._q[3] * q2._q[3];
            T acos_q1 = std::acos(cos_q1);

            T sin_q1 = std::sin(acos_q1);
            T wq1 = std::sin(( T(1.0) - t) * acos_q1) / sin_q1;
            T wq2 = std::sin(t * acos_q1) / sin_q1;

            q._q[0] = wq1*q1._q[0] + wq2*q2._q[0];
            q._q[1] = wq1*q1._q[1] + wq2*q2._q[1];
            q._q[2] = wq1*q1._q[2] + wq2*q2._q[2];
            q._q[3] = wq1*q1._q[3] + wq2*q2._q[3];

            // Normalize
            T rLength = T(1.0) / std::sqrt(q._q[0] * q._q[0] + q._q[1] * q._q[1] + q._q[2] * q._q[2] + q._q[3] * q._q[3]);

            q._q[0] *= rLength;
            q._q[1] *= rLength;
            q._q[2] *= rLength;
            q._q[3] *= rLength;

            return q;
        }



		/// Operators ///
        
        /**
         * \brief Quaternion multiplication.
         * 
         * This operation represents a composite rotation. So,
         * p * q means a q rotation followed by a p rotation.
         */
		QuaternionRotation operator * (const QuaternionRotation& q) const
		{
            // Formula: p*q = [(pS*qV + qS*pV + pV x qV) (pS*qS - pV.qV)]
            // Where pS represents the scalar part (_q[3]) and pV represents
            // the vector part (_q[0], _q[1], _q[2]).

            QuaternionRotation r;

            r._q[0] = _q[3] * q._q[0] + q._q[3] * _q[0] + (_q[1] * q._q[2] - _q[2] * q._q[1]);
            r._q[1] = _q[3] * q._q[1] + q._q[3] * _q[1] + (_q[2] * q._q[0] - _q[0] * q._q[2]);
            r._q[2] = _q[3] * q._q[2] + q._q[3] * _q[2] + (_q[0] * q._q[1] - _q[1] * q._q[0]);
            r._q[3] = _q[3] * q._q[3] - (_q[0] * q._q[0] + _q[1] * q._q[1] + _q[2] * q._q[2]);

            return r;
		}



		private:

        T _q[4]; /**< Stores the four values of the quaternion. */
	};
}
#endif // __QUATERNIONROTATION_H__
