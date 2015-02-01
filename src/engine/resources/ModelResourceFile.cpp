/** 
 * \file ModelResourceFile.cpp
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ModelResourceFile.h"
#include "Mesh.h"


namespace nut
{

ModelResourceFile::ModelResourceFile( const std::string& path )
{
    Assimp::Importer importer;
    
    // Set importer to normalize all vertex components into the [-1, 1] range
    importer.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE, true);	

    const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | // If normals are presented, calculates the tangents and bitangents for the imported meshes
                                                   aiProcess_GenSmoothNormals | // Generates smooth normals for all vertices in the mesh
                                                   aiProcess_JoinIdenticalVertices | // Identifies and joins identical vertex data sets within all imported meshes
                                                   aiProcess_Triangulate | // Triangulates all faces of all meshes, points and lines primitives are not modified
                                                   aiProcess_GenUVCoords | // Converts non-UV mappings (such as spherical or cylindrical mapping) to proper texture coordinate channels
                                                   aiProcess_SortByPType); // This step splits meshes with more than one primitive type in homogeneous sub-meshes

    if ( scene != nullptr )
    {
        m_numberOfResources = scene->mNumMeshes;// +
//                              scene->mNumAnimations +
//                              scene->mNumCameras +
//                              scene->mNumLights +
//                              scene->mNumMaterials +
//                              scene->mNumTextures;

        if ( scene->HasMeshes() )
        {
            m_meshes.reserve( scene->mNumMeshes );
            loadMeshes(scene->mMeshes, scene->mNumMeshes);
        }

//        if (scene->HasAnimations())
//        {
//            loadAnimations(scene->mAnimations, scene->mNumAnimations);
//        }
//        
//        if (scene->HasCameras())
//        {
//            loadCameras(scene->mCameras, scene->mNumCameras);
//        }
//
//        if (scene->HasLights())
//        {
//            loadLights(scene->mLights, scene->mNumLights);
//        }
//
//        if (scene->HasMaterials())
//        {
//            loadMaterials(scene->mMaterials, scene->mNumMaterials);
//        }
//
//        if (scene->HasTextures())
//        {
//            loadTextures(scene->mTextures, scene->mNumTextures);
//        }
    }
    else
    {
        const char* error = importer.GetErrorString();
        std::cerr << "nut::ModelResourceFile error: " << error << "\n";
    }
}



void ModelResourceFile::loadMeshes( aiMesh** meshes, unsigned int size )
{
    for (unsigned int n = 0; n < size; ++n)
    {
        const aiMesh* mesh = meshes[n];
        bool hasNormals = mesh->HasNormals();
        bool hasTangentsAndBitangents = mesh->HasTangentsAndBitangents();

        Mesh nutMesh;

        std::vector< Vertex >& vertices = nutMesh.getVertices();
        vertices.reserve( mesh->mNumVertices );

        // Set vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            Vertex nutVertex;
            
            nutVertex.pos.x = mesh->mVertices[i].x;
            nutVertex.pos.y = mesh->mVertices[i].y;
            nutVertex.pos.z = mesh->mVertices[i].z;

            if( hasNormals )
            {
                nutVertex.normal.x = mesh->mNormals[i].x;
                nutVertex.normal.y = mesh->mNormals[i].y;
                nutVertex.normal.z = mesh->mNormals[i].z;
            }
            
            // Tangent and bitangent
            if ( hasTangentsAndBitangents )
            {
                nutVertex.tangent.x = mesh->mTangents[i].x;
                nutVertex.tangent.y = mesh->mTangents[i].y;
                nutVertex.tangent.z = mesh->mTangents[i].z;

                nutVertex.bitangent.x = mesh->mBitangents[i].x;
                nutVertex.bitangent.y = mesh->mBitangents[i].y;
                nutVertex.bitangent.z = mesh->mBitangents[i].z;
            }

            vertices.push_back( nutVertex );
        }

        // Set triangulation
        std::vector< int >& indices = nutMesh.getIndices();
        indices.reserve( mesh->mNumFaces * 3 );
        
        for (unsigned int f = 0; f < mesh->mNumFaces; ++f)
        {
            const struct aiFace* face = &mesh->mFaces[f];
            
            indices.push_back( face->mIndices[0] );
            indices.push_back( face->mIndices[1] );
            indices.push_back( face->mIndices[2] );
        }

        m_meshes.push_back( nutMesh );
    }
}

} // End namespace