/** 
 * \file GeometryResourceFile.cpp
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GeometryResourceFile.h"



GeometryResourceFile::GeometryResourceFile(const std::string& path)
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

    if ( scene == std::nullptr )
    {
        const char* error = importer.GetErrorString();
        // TODO: Error message
        
        return;
    }
    
    if (scene->HasAnimations())
    {
        loadAnimations(scene->mAnimations, scene->mNumAnimations);
    }
    
    if (scene->HasCameras())
    {
        loadCameras(scene->mCameras, scene->mNumCameras);
    }
    
    if (scene->HasLights())
    {
        loadLights(scene->mLights, scene->mNumLights);
    }
    
    if (scene->HasMaterials())
    {
        loadMaterials(scene->mMaterials, scene->mNumMaterials);
    }
    
    if (scene->HasMeshes())
    {
        loadMeshes(scene->mMeshes, scene->mNumMeshes);
    }
    
    if (scene->HasTextures())
    {
        loadTextures(scene->mTextures, scene->mNumTextures);
    }
}



int GeometryResourceFile::getNumberOfResources()
{
    return 0;
}



std::string GeometryResourceFile::getResourceName(int index = 0)
{
    return std::string;
}



BYTE* GeometryResourceFile::getResource(int index = 0)
{
    return std::nullptr;
}



void GeometryResourceFile::loadAnimations(aiAnimation** animations, unsigned int size)
{
    
}



void GeometryResourceFile::loadCameras(aiCamera** cameras, unsigned int size)
{
    
}



void GeometryResourceFile::loadLights(aiLight** lights, unsigned int size)
{
    
}



void GeometryResourceFile::loadMaterials(aiMaterial** materials, unsigned int size)
{
    
}



void GeometryResourceFile::loadMeshes(aiMesh** meshes, unsigned int size)
{
    for (unsigned int n = 0; n < size; ++n)
    {
        const aiMesh* mesh = meshes[n];
        
        bool hasNormals = mesh->HasNormals();
        bool hasTangentsAndBitangents = mesh->HasTangentsAndBitangents();
        bool hasTextureCoords = mesh->HasTextureCoords();
        bool hasColors = mesh->HasColors();

        // Set vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            //Vertex vertex;

            //vertex.setPosition(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

            // Normal
            if(hasNormals)
            {
                //vertex.setNormal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }
            
            // Tangent and bitangent
            if (hasTangentsAndBitangents)
            {
                //vertex.setTangent(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
                //vertex.setBiTangent(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            }
            
            // Texture coordinates
            if (hasTangentsAndBitangents)
            {
                //vertex.setTextureCoord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z);
            }

            // Color
            if(hasColors)
            {
                //vertex.setColor(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a);
            }
            
            // TODO: Insert vertex in the list
        }

        // Set indices
        for (unsigned int f = 0; f < mesh->mNumFaces; ++f)
        {
            const struct aiFace* face = &mesh->mFaces[f];

            for(unsigned int j = 0; j < face->mNumIndices; j++)
            {
                // TODO: Insert index face->mIndices[j] in the list of indices
            }
        }
    }
}



void GeometryResourceFile::loadTextures(aiTexture** textures, unsigned int size)
{
    
}
