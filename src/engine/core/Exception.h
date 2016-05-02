/**
 * \file Exception.h
 * \brief This header contains declarations for error handling.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>


namespace nut
{
    class Exception
    {
        public:
            /*
             * \brief Reports an exception message to standard error.
             */
            static void reportException( const std::string& message, const std::string& file, int line, const std::string& function )
            {
                std::cerr << "nut: " << file << ":" << line << ": " << function << ": " << message << std::endl;
            }
            
            /**
             * \brief Exceptions definitions.
             */
            enum class Type
            {
                NUT_SUCCESS = 0x00000000,   /**< Success. */
                ERR_UNDEFINED,              /**< Undefined exception. */
                ERR_UNDEFINED_REFERENCE,    /**< Undefined reference to an object. */
                ERR_INVALID_PARAMETERS,     /**< Some parameters are invalid. */
                ERR_NOT_IMPLEMENTED,        /**< Function not implemented. */
                ERR_CANNOT_WRITE_TO_FILE,   /**< File cannot be written. */
                ERR_CANNOT_READ_FROM_FILE,  /**< File cannot be read. */
                ERR_FILE_NOT_FOUND          /**< File not found. */
            };
    };
}

#endif
