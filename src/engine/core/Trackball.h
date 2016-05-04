/** 
 * \file Trackball.h
 * \brief This class implements a virtual trackball.
 * 
 * A virtual trackball is a device for controlling 3D rotations by moving a 2D mouse.
 * This implementation is based on Shoemake's arcball and Holroyd method.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <cmath>
#include "Math.h"
#include "Vector3D.h"
#include "GLMatrix.h"


namespace nut
{
    class Trackball
    {
        public:

        Trackball() : mRadius( 1.0f ) {}

        Trackball( float radius ) : Trackball()
        {
            setRadius( radius );
        }

        /**
         * Change radius' value.
         * 
         * @param radius New radius.
         */
        void setRadius( float radius )
        {
            if ( radius > 0.0f )
            {
                mRadius = radius;
            }
        }

        /**
         * Compute the first point projected onto a sphere.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         */
        void startDrag( float x, float y )
        {
            setProjectedPoint( mPa, x, y );
        }

        /**
         * Compute the second point projected onto a sphere.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         */
        void drag( float x, float y )
        {
            setProjectedPoint( mPc, x, y );

            // Update rotation matrix
            Vector3D<float> u = mPa.cross( mPc );
            float theta = atan( u.length() / ( mPa * mPc ) );

            mRotationMatrix.rotate( u.x, u.y, u.z, theta );
        }
        
        /**
         * Reset trackball.
         */
        void reset()
        {
            mRotationMatrix.setIdentity();
        }
        
        /**
         * Get a @GLMatrix representing the current rotation.
         * 
         * @return A @GLMatrix representing the current rotation.
         */
        const GLMatrix<float>& getRotation()
        {
            return mRotationMatrix;
        }


        private:

        void setProjectedPoint( Vector3D<float>& p, float x, float y )
        {
            float r = std::sqrt( x * x + y * y );

            // Compute projected point using Holroyd's method
            p.x = x;
            p.y = y;
            if ( r <= ( mRadius / Math<float>::SQRT_2 ) )
            {
                p.z = std::sqrt( mRadius * mRadius - ( x * x + y * y ) );
            }
            else
            {
                p.z = ( mRadius * mRadius ) / ( 2.0f * r );
            }
        }
        

        float mRadius;
        Vector3D<float> mPa;
        Vector3D<float> mPc;
        GLMatrix<float> mRotationMatrix;
    };
}

#endif // TRACKBALL_H
