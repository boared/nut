/** 
 * \file XMLParser.cpp
 * \brief Class definition for parsing XML data.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder Perez.
 */

#include <iostream>
#include <sstream>
#include "pugixml.cpp"
#include "XMLParser.h"



namespace nut
{
    bool XMLParser::load(const char* path)
    {
        if (path == nullptr)
        {
            std::cerr << "nut::XMLParser::load error. Invalid path.\n";

            return false;
        }

        pugi::xml_parse_result result;

        result = _document.load_file(path);

        if (!result)
        {
            std::cerr << "nut::XMLParser::load error. " << result.description() << "\n";
        }

        return result;
    }



    bool XMLParser::load(const char* xml, size_t size)
    {
        if (xml == nullptr)
        {
            std::cerr << "nut::XMLParser::load error. Invalid path.\n";

            return false;
        }

        char* buffer = static_cast<char*>(pugi::get_memory_allocation_function()(size));
        memcpy(buffer, xml, size);

        pugi::xml_parse_result result = _document.load_buffer_inplace_own(buffer, size);

        if (!result)
        {
            std::cerr << "nut::XMLParser::load error. " << result.description() << "\n";
        }

        return result;
    }



    bool XMLParser::save(const char* path)
    {
        if (path == nullptr)
        {
            std::cerr << "nut::XMLParser::save error. Invalid path.\n";

            return false;
        }

        bool status = _document.save_file(path);
        if (!status)
        {
            std::cerr << "nut::XMLParser::save error.\n";
        }

        return status;
    }



    void XMLParser::copy(std::string& xml, bool indent)
    {
        std::ostringstream output;

        if (indent)
        {
            _document.save(output, "    ");
        }
        else
        {
            _document.save(output, "", pugi::format_raw);
        }
        
        xml = output.str();
    }
}
