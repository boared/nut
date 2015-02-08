/** 
 * \file Path.h
 * \brief Static class for path manipulation.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef PATH_H
#define PATH_H

#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>


namespace nut
{
    class Path
    {
        public:

        /**
         * Given a path, get the file name including extension.
         * 
         * Examples:
         * 
         * "/usr/local/lib/lib.a" returns "lib.a" as file name.
         * "/usr/local/" returns an empty string, because "local" is considered a directory not a file.
         * "/usr/local" returns "local" as file name.
         */
        static std::string getFileName( const std::string& path )
        {
            std::string name;
            bool separatorFound = false;
            int pos = path.size() - 1;

            for (std::string::const_reverse_iterator rit = path.rbegin(); rit != path.rend(); ++rit, pos--)
            {
                if ( *rit == '\\' || *rit == '/')
                {
                    separatorFound = true;
                    break;
                }
            }
            
            if ( separatorFound )
            {
                name = path.substr(pos + 1).c_str();
            }
            else
            {
                name = path;
            }

            return name;
        }

        /**
         * Get the file extension. The returned string is in lower case.
         */
        static std::string getFileExtension( const std::string& path )
        {
            std::string fileName = getFileName( path );
            std::string extension;
            bool dotFound = false;
            int pos = fileName.size() - 1;

            for (std::string::const_reverse_iterator rit = fileName.rbegin(); rit != fileName.rend(); ++rit, pos--)
            {
                if ( *rit == '.' )
                {
                    dotFound = true;
                    break;
                }
            }
            
            if ( dotFound && pos > 1 )
            {
                extension = fileName.substr(pos + 1).c_str();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            }

            return extension;
        }
    };
}
#endif // STRING_H
