/** 
 * \file String.h
 * \brief Static class for string manipulation.
 * 
 * @author: Eder A. Perez.
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <sstream>



namespace nut
{
    class String
    {
        public:

        /**
         * Split a string based on a delimiter.
         * 
         * @param str Input string.
         * @param delim Delimiter.
         * @return A vector of split strings.
         */
        static std::vector<std::string> split(const std::string& str, char delim)
        {
            std::vector<std::string> elems;
            std::stringstream ss(str);
            std::string item;

            while (std::getline(ss, item, delim))
            {
                elems.push_back(item);
            }

            return elems;
        }
    };
}
#endif // __STRING_H__
