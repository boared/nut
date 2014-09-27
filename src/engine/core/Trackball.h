/** 
 * \file Trackball.h
 * \brief This class implements a virtual trackball.
 * 
 * A virtual trackball is a device for controlling 3D rotations by moving a 2D mouse.
 * This implentation is based on Shoemake's arcball and Holroyd method.
 * 
 * @author: Eder A. Perez.
 */

#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <cmath>
#include "QuaternionRotation.h"
#include "Math.h"
#include "Vector3D.h"
#include "GLMatrix.h"



namespace nut
{
    class Trackball
    {
        public:

        /**
         * Default constructor.
         * 
         * Set radius to 1.
         */
        Trackball() : _radius(1.0f) {}

        /**
         * Constructor.
         * 
         * @param radius Sphere's radius.
         */
        Trackball(float radius)
        {
            if (radius > 0.0f)
            {
                _radius = radius;
            }
            else
            {
                _radius = 1.0f;
            }
        }



        /**
         * Change radius' value.
         * 
         * @param radius New radius.
         */
        void setRadius(float radius)
        {
            if (radius > 0.0f)
                _radius = radius;
        }

        /**
         * Compute the first point projected onto a sphere.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         */
        void startDrag(float x, float y)
        {
            _setProjectedPoint(_Pa, x, y);
        }

        /**
         * Compute the second point projected onto a sphere.
         * 
         * @param x X-coordinate.
         * @param y Y-coordinate.
         */
        void drag(float x, float y)
        {
            _setProjectedPoint(_Pc, x, y);

            // Update rotation matrix
            Vector3D<float> u = _Pa.cross(_Pc);
            float theta = atan( u.length() / (_Pa * _Pc) );

            _m.rotate(u.x, u.y, u.z, theta);
        }
        
        /**
         * Reset trackball.
         */
        void reset()
        {
            _m.setIdentity();
        }
        
        /**
         * Get a @GLMatrix representing the current rotation.
         * 
         * @return A @GLMatrix representing the current rotation.
         */
        GLMatrix<float> getRotation()
        {
            return _m;
        }



        private:

        float _radius;
        Vector3D<float> _Pa;
        Vector3D<float> _Pc;
        GLMatrix<float> _m;
        
        /**
         * 
         * @param p
         * @param x
         * @param y
         */
        void _setProjectedPoint(Vector3D<float>& p, float x, float y)
        {
            float r = std::sqrt(x * x + y * y);

            // Compute projected point using Holroyd's method
            p.x = x;
            p.y = y;
            if (r <= (_radius / Math<float>::SQRT_2))
            {
                p.z = std::sqrt(_radius * _radius - (x * x + y * y));
            }
            else
            {
                p.z = (_radius * _radius) / (2.0f * r);
            }
        }
    };
}
#endif // TRACKBALL_H
