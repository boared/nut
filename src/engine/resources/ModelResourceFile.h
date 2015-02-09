/** 
 * \file ModelResourceFile.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef MODEL_RESOURCE_FILE_H
#define	MODEL_RESOURCE_FILE_H

#include "IResourceFile.h"

class aiMesh;


namespace nut
{

class Mesh;

class ModelResourceFile : public IResourceFile
{
    public:
        
        static IResourceFile* createMe( const std::string& path )
        {
            return new ModelResourceFile( path );
        }

        size_t getNumberOfResources() const
        {
            return m_numberOfResources;
        }

        bool hasMeshes()
        {
            return m_meshes.size() > 0;
        }
        
        size_t getNumberOfMeshes() const
        {
            return m_meshes.size();
        }


    private:

        ModelResourceFile(const std::string& path);

        void loadMeshes(aiMesh** meshes, unsigned int size);


        size_t m_numberOfResources; /**< Number of resources in this file. */
        std::vector< Mesh > m_meshes; /**< List containing all meshes in this resource file. */
};

}
#endif	// MODEL_RESOURCE_FILE_H
