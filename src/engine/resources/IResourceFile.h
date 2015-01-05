/** 
 * \file IResourceFile.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef IRESOURCEFILE_H
#define	IRESOURCEFILE_H

#include <string>



namespace nut
{
    typedef IResourceFile* (*CreateResourceFileFunc)(const std::string& path);

    class IResourceFile
    {
        public:
            
            virtual ~IResourceFile() {}

            virtual bool open() = 0;
            
            virtual int getNumberOfResources() const = 0;
            
            virtual std::string getResourceName(int index) const = 0;
            
            virtual I8* getResource(/* A parameter must be passed */) const = 0;
            
            virtual static IResourceFile* createMe(const std::string& path) = 0;
    };
}
#endif	// IRESOURCEFILE_H

