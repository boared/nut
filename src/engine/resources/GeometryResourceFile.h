/** 
 * \file ModelResourceFile.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef MODELRESOURCEFILE_H
#define	MODELRESOURCEFILE_H

#include "IResourceFile.h"



namespace nut
{
    class ModelResourceFile : public IResourceFile
    {
        public:
            
            bool open();
            
            int getNumberOfResources() const;
            
            std::string getResourceName(int index) const;
            
            I8* getResource(/* A parameter must be passed */) const;
            
            static IResourceFile* createMe(const std::string& path)
            {
                return new ModelResourceFile(path);
            }



        private:
            
            ModelResourceFile(const std::string& path);

            std::string _metaDataXML;
    };
}
#endif	// MODELRESOURCEFILE_H

