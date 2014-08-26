/** 
 * \file INIFilesHandler.h
 * \brief Class definition for read/write INI files.
 * 
 * @author: Eder A. Perez.
 */

#ifndef INIFILESHANDLER_H
#define INIFILESHANDLER_H

#include <fstream>
#include <vector>



namespace nut
{
    class INIFilesHandler
    {
        public:

        /// Constructors ///

        /**
         * Default constructor.
         */
        INIFilesHandler();

        /**
         * Destructor.
         */
        ~INIFilesHandler();



        /// Methods ///

        /**
         * Open an INI file for read/write. If file exists, all data will be
         * read to an internal data structure. Otherwise, a new file is created.
         * In any case, data is read from or write to the internal data structure
         * before written down to the file by calling method @save().
         * 
         * @param path Path to the INI file.
         * @param readOnly True if the file will be open for read only. False otherwise.
         * @return True if file has been successfully opened, false otherwise.
         */
        bool open(const std::string& path, bool readOnly);

        /**
         * Close the INI file.
         */
        void close();

        /**
         * Clear all the content.
         */
        void clear();

        /**
         * Add a section.
         * 
         * @param section Section name without brackets.
         */
        void setSection(const std::string& section);

        /**
         * Add/update a key-value.
         * 
         * If @key exists, its @value is just updated. Otherwise, a new key/value
         * entry is added.
         * 
         * @param section Section name without brackets. The key/value is associated
         * to a specific section. If @section is NULL, key/value pair will be put
         * at the beginning of the file and is not associated to any section.
         * If @section doesn't exist, it will be created.
         * @param key String representing the key.
         * @param value String representing the Value.
         */
        void setKeyValue(const std::string* section, const std::string& key, const std::string& value);

        /**
         * Given a @section and a @key, gets an associated value.
         * 
         * @param section Section name. 0 if there's no section associated.
         * @param key Key value.
         * @return An string representing the value associated to a key. If the
         * section or the key are invalid, returns an empty string.
         */
        std::string getValue(const std::string* section, const std::string& key);



        private:

        /**
         * This class holds a list of key/values by section.
         */
        class _Section
        {
            public:
            std::string section;
            std::vector< std::pair<std::string, std::string> > keyValues;
        };

        std::vector<_Section> _sections; /**< Data read from, or to be stored to, the file. */
        std::fstream _file; /**< Handle to the file. */
        bool _readOnly;



        /// Private methods ///

        /**
         * Read all data in the INI file (comments are avoided) and stores them
         * internally in the @_sections list.
         */
        void _readFile();

        /**
         * Write all data to the file.
         */
        void _save();
    };
}

#endif // INIFILESHANDLER_H
