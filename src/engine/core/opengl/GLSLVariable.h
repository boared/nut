/** 
 * \file GLProgram.h
 * \brief This class stores information about a GLSL attribute or uniform variable.
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

        GLSLVariable() :
            program(0),
            location(-1),
            size(0),
            type(0),
            name(0),
            isUniform(false)
        {
        }

        GLSLVariable(GLuint program, GLint location, GLint size, GLenum type, const char* name, bool isUniform) :
            program(program),
            location(location),
            size(size),
            type(type),
            name(name),
            isUniform(isUniform)
        {
        }
        
        const GLuint program; /**< An OpenGL program where this variable is specified for. */
        const GLint location; /**< The location of the variable. */
        const GLint size; /**< The size of the variable. */
        const GLenum type; /**< The type of the variable. */
        const std::string name; /**< The name of the variable. */
        const bool isUniform; /**< True if it is an uniform variable. False if it is an attribute. */
    };
}

#endif // GLSLVARIABLE_H
