/** 
 * \file Mesh.h
 * \brief This class represents a 3D triangular mesh.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef MESH_H
#define MESH_H

#include "Vertex.h"


namespace nut
{

class Mesh
{
    public:

        std::vector< Vertex >& getVertices()
        {
            return m_vertices;
        }

        std::vector< int >& getTriangulation()
        {
            return m_triangulation;
        }

    private:

        std::vector< Vertex > m_vertices;
        std::vector< int > m_triangulation;
};

}
#endif // MESH_H
