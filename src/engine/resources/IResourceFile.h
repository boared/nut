/** 
 * \file IResourceFile.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef IRESOURCE_FILE_H
#define	IRESOURCE_FILE_H

#include <string>



namespace nut
{
    typedef IResourceFile* (*CreateResourceFileFunc)(const std::string& path);

    class IResourceFile
    {
        public:
            
            virtual ~IResourceFile()
            {
            }

            virtual int getNumberOfResources() const = 0;
            
            virtual std::string getResourceName(int index = 0) const = 0;
            
            virtual BYTE* getResource(int index = 0) const = 0;
            
            virtual static IResourceFile* createMe(const std::string& path) = 0;
    };
}
#endif	// IRESOURCE_FILE_H
