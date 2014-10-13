/** 
 * \file INIFilesHandler.cpp
 * \brief Class definition for read/write INI files.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#include <iostream>
#include <vector>
#include "INIFilesHandler.h"
#include "String.h"



namespace nut
{
    INIFilesHandler::INIFilesHandler() : _readOnly(true)
    {
        // Add a section representing "no" section. This section will be written
        // first when saving the file. It represents key/value pairs with no
        // section associated with them.
        _Section s;
        s.section = "[0]";
        _sections.push_back(s);
    }



    INIFilesHandler::~INIFilesHandler()
    {
        // Save data and close the INI file
        close();
    }



    bool INIFilesHandler::open(const std::string& path, bool readOnly)
    {
        // Firstly, open the file and read all its content
        _file.open(path.c_str(), std::fstream::in);

        // If file exists, read all its content and close it
        if (_file.is_open())
        {
            _readFile();

            _file.close();
        }

        if (!readOnly)
        {
            // Secondly, open for write a new file
            _file.open(path.c_str(), std::fstream::out | std::fstream::trunc);
        }

        _readOnly = readOnly;

        return _file.is_open();
    }



    void INIFilesHandler::close()
    {
        _save();
        _file.close();
        clear();
    }



    void INIFilesHandler::clear()
    {
        _sections.clear();

        // Add a section representing "no" section. This section will be written
        // first when saving the file. It represents key/value pairs with no
        // section associated with them.
        _Section s;
        s.section = "[0]";
        _sections.push_back(s);
    }



    void INIFilesHandler::setSection(const std::string& section)
    {
        if (!_readOnly)
        {
            bool exist = false;

            for (size_t i = 1; i < _sections.size(); ++i)
            {
                if (_sections[i].section == section)
                {
                    exist = true;
                    break;
                }
            }

            if (!exist)
            {
                _Section s;
                s.section = section;
                _sections.push_back(s);
            }
        }
    }



    void INIFilesHandler::setKeyValue(const std::string* section, const std::string& key, const std::string& value)
    {
        if (!_readOnly)
        {
            int index = -1;

            // Look for an existing section
            if (section)
            {
                for (size_t i = 1; i < _sections.size(); ++i)
                {
                    if (_sections[i].section == *section)
                    {
                        index = i;
                        break;
                    }
                }
            }
            // If section is NULL key/value has no associated section
            else
            {
                index = 0;
            }

            if (index != -1)
            {
                bool keyExist = false;

                for (size_t i = 0; i < _sections[index].keyValues.size(); ++i)
                {
                    if (_sections[index].keyValues[i].first == key)
                    {
                        _sections[index].keyValues[i].second = value;
                        keyExist = true;
                        break;
                    }
                }

                if (!keyExist)
                {
                    _sections[index].keyValues.push_back(std::pair<std::string, std::string>(key, value));
                }
            }
        }
    }



    std::string INIFilesHandler::getValue(const std::string* section, const std::string& key)
    {
        int index = -1;

        // Look for an existing section
        if (section)
        {
            for (size_t i = 1; i < _sections.size(); ++i)
            {
                if (_sections[i].section == *section)
                {
                    index = i;
                    break;
                }
            }
        }
        // If section is NULL key/value has no associated section
        else
        {
            index = 0;
        }

        if (index != -1)
        {
            for (size_t i = 0; i < _sections[index].keyValues.size(); ++i)
            {
                if (_sections[index].keyValues[i].first == key)
                {
                    return _sections[index].keyValues[i].second;
                }
            }
        }

        return "";
    }



    void INIFilesHandler::_readFile()
    {
        std::string section;
        std::string* ptrSection = 0;

        if (_file.is_open())
        {
            while (!_file.eof())
            {
                std::string line;

                _file >> line;

                if (line.size() > 0)
                {
                    // Is [section]
                    if (line[0] == '[')
                    {
                        section = line.substr(1, line.size()-2);
                        ptrSection = &section;

                        setSection(section);
                    }
                    // Escape comments but not key=value
                    else if (line[0] != ';')
                    {
                        std::vector<std::string> split = String::split(line, '=');

                        if (split.size() == 2)
                        {
                            setKeyValue(ptrSection, split[0], split[1]);
                        }
                    }
                }
            }
        }
    }



    void INIFilesHandler::_save()
    {
        if (_file.is_open())
        {
            // Write key-values with no sections
            for (size_t j = 0; j < _sections[0].keyValues.size(); ++j)
            {
                _file << _sections[0].keyValues[j].first << "=" << _sections[0].keyValues[j].second << "\n";
            }

            // Write sections and key-values
            for (size_t i = 1; i < _sections.size(); ++i)
            {
                std::string section = _sections[i].section;

                _file << "[" << section << "]\n";

                for (size_t j = 0; j < _sections[i].keyValues.size(); ++j)
                {
                    _file << _sections[i].keyValues[j].first << "=" << _sections[i].keyValues[j].second << "\n";
                }
            }
        }
    }
}
