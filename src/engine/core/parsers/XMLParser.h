/** 
 * \file XMLParser.h
 * \brief Class definition for parsing XML data.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder Perez.
 */

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include "pugixml.hpp"



namespace nut
{
    class XMLParser
    {
        public:

        /**
         * Default constructor.
         */
        XMLParser()
        {
        }
        
        /**
         * Load xml data from file.
         * 
         * @param path Contains a file path to xml data.
         * @return True if xml was successfully loaded, false otherwise.
         */
        bool load(const char* path);
        
        /**
         * Load xml data from buffer.
         * 
         * @param xml Xml data.
         * @param size Size in bytes of @xml.
         * @return True if @xml was successfully loaded, false otherwise.
         */
        bool load(const char* xml, size_t size);

        /**
         * Write xml data to a file.
         * 
         * @param path The output file path.
         * @return True if xml was successfully saved, false otherwise.
         */
        bool save(const char* path);

        /**
         * Copy xml data to a string.
         * 
         * @param xml The output string where xml data will be copied to.
         * @param indent True for indented data, false for raw data (saves memory but is less human readable).
         */
        void copy(std::string& xml, bool indent);



        private:

        pugi::xml_document _document;

    };
}
#endif // XMLPARSER_H
