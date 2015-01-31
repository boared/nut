/** 
 * \file Vertex.h
 * \brief This class represents a single vertex of a geometric 3D model.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef VERTEX_H
#define VERTEX_H

#include "Vector.h"


namespace nut
{
    class Vertex
    {
        public:

            Vec3f pos;
            Vec3f normal;
            Vec3f tangent;
            Vec3f bitangent;
    };
}
#endif // VERTEX_H
