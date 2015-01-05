/** 
 * \file ResourceFileFactory.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef RESOURCEFILEFACTORY_H
#define	RESOURCEFILEFACTORY_H

#include <map>
#include <string>



namespace nut
{
    class IResourceFile;
    typedef IResourceFile* (*CreateResourceFileFunc)(const std::string& path);

    class ResourceFileFactory
    {
        public:

        static ResourceFileFactory& getInstance()
        {
            static ResourceFileFactory instance;
            return instance;
        }
        
        void registerResourceFile(const std::string& id, CreateResourceFileFunc create)
        {
            _resourceFiles[id] = create;
        }
        
        IResourceFile* create(const std::string& id, const std::string& path)
        {
            return _resourceFiles[id](path);
        }



        private:

        ResourceFileFactory();

        // Stop the compiler generating methods of copy the object
        ResourceFileFactory(ResourceFileFactory const& copy); // Not Implemented
        ResourceFileFactory& operator=(ResourceFileFactory const& copy); // Not Implemented

        std::map< std::string, CreateResourceFileFunc > _resourceFiles;
    };
}
#endif	// RESOURCEFILEFACTORY_H

