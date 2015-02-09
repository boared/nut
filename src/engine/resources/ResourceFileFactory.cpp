/** 
 * \file ResourceFileFactory.cpp
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include "ResourceFileFactory.h"
#include "Path.h"


namespace nut
{

IResourceFile* ResourceFileFactory::createResourceFile(const std::string& path)
{
    std::string extension = Path::getFileExtension(path);
    
    ResourceFileId id = getResourceFileIdByExtension(extension);
    
    if ( m_resourceFiles.find(id) != m_resourceFiles.end() )
    {
        return m_resourceFiles[id](path);
    }
    
    return nullptr;
}


ResourceFileId ResourceFileFactory::getResourceFileIdByExtension(const std::string& extension)
{
    // 3D model files
    if ( extension == "obj" || // Wavefront Object
         extension == "ply" || // Stanford Polygon Library
         extension == "off" || // Object File Format
         extension == "dae" || // Collada
         extension == "ter" )  // Terragen Terrain
       
    {
        return ResourceFileId::Model;

    }

    return ResourceFileId::Unknown;
}

}