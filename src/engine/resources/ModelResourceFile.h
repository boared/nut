/** 
 * \file GeometryResourceFile.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef GEOMETRY_RESOURCE_FILE_H
#define	GEOMETRY_RESOURCE_FILE_H

#include "IResourceFile.h"



namespace nut
{
    class GeometryResourceFile : public IResourceFile
    {
        public:
            
            int getNumberOfResources() const;
            
            std::string getResourceName(int index = 0) const;
            
            BYTE* getResource(int index = 0) const;
            
            static IResourceFile* createMe(const std::string& path)
            {
                return new GeometryResourceFile(path);
            }



        private:

            GeometryResourceFile(const std::string& path);

            void loadAnimations(aiAnimation** animations, unsigned int size);

            void loadCameras(aiCamera** cameras, unsigned int size);

            void loadLights(aiLight** lights, unsigned int size);

            void loadMaterials(aiMaterial** materials, unsigned int size);

            void loadMeshes(aiMesh** meshes, unsigned int size);

            void loadTextures(aiTexture** textures, unsigned int size);
    };
}
#endif	// GEOMETRY_RESOURCE_FILE_H
