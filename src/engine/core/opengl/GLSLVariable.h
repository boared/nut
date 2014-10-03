/** 
 * \file GLSLVariable.h
 * \brief This class holds information about a GLSL attribute or uniform variable.
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLSLVARIABLE_H
#define GLSLVARIABLE_H

#include <string>
#include "GL/glew.h"



namespace nut
{
    class GLSLVariable
    {
        public:

        GLuint program; /**< An OpenGL program where this variable is specified for. */
        GLint location; /**< The location of the variable. */
        std::string name; /**< The name of the variable. */
        GLint size; /**< The size of the variable. */
        GLenum type; /**< The type of the variable. */
        bool isUniform; /**< True if it is an uniform variable. False if it is an attribute. */



        GLSLVariable() :
            program(0),
            location(-1),
            size(0),
            type(0),
            isUniform(false)
        {
        }
    };
}

#endif // GLSLVARIABLE_H
