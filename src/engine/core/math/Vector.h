/** 
 * \file Vector.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

namespace nut
{

typedef Vector2D< float > Vec2f;
typedef Vector3D< float > Vec3f;
typedef Vector4D< float > Vec4f;

typedef Vector2D< double > Vec2d;
typedef Vector3D< double > Vec3d;
typedef Vector4D< double > Vec4d;

typedef Vector2D< int > Vec2i;
typedef Vector3D< int > Vec3i;
typedef Vector4D< int > Vec4i;

}
#endif // VECTOR_H
