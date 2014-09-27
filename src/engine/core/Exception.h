/**
 * \file Exception.h
 * \brief This header contains declarations for error handling, exceptions and assertions.
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>



namespace nut
{
    void reportException(std::string expr, std::string file, int line)
    {
        std::cerr << "Error at " << expr << ", " << file << ", line " << line << std::endl;
    }



    #ifndef ASSERTIONS_ENABLED
        /**
         * \def ASSERTIONS_ENABLED
         * \brief  Enables or disables assertions.
         */
        #define ASSERTIONS_ENABLED 1
    #endif



	/**
     * Assertion.
     * When an assertion occurs, the program breaks and print a message to the stderr.
     */
    #if ASSERTIONS_ENABLED
        /**
         * \def DEBUG_BREAK()
         * \brief Define some inline assembly that causes a break
         * into the debugger. This will be different on each
         * target CPU.
         */
        #if defined(_M_IX86) || defined(_X86_)
            // The target architecture is x86
            #define DEBUG_BREAK() __asm { int 3 }    
        #else
            // The target architecture is something else
            #define DEBUG_BREAK()
        #endif

        /**
         * \def NUT_ASSERT(expr)
         * \brief Check the expression and fail if it is false.
         */
        #define NUT_ASSERT(expr) \
                if (expr) { } \
                else \
                { \
                    reportException(#expr, __FILE__, __LINE__); \
                    DEBUG_BREAK(); \
                }
    #else
        #define NUT_ASSERT(exp)	// Evaluate to nothing
    #endif



    /**
     * \brief Exceptions definitions.
     * An exception is represented by a 32-bits value. The success state is represented by zero.
     */
	enum EXCEPTIONS
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



    /**
     * \def REPORT_EXCEPTION(expr, file, line)
     * \brief Reports an exception to standard error output.
     * 
     * @param file The file name where the error has occurred.
     * @param line The line number where the error has occurred.
     */
    #define REPORT_EXCEPTION(file, line) reportException("", (__FILE__), (__LINE__))
}

#endif // EXCEPTION_H
