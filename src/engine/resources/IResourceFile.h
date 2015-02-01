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

class IResourceFile
{
    public:

        virtual ~IResourceFile()
        {
        }

        virtual int getNumberOfResources() const = 0;
};

}
#endif	// IRESOURCE_FILE_H
