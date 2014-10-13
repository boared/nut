/** 
 * \file GLSLVariable.h
 * \brief This class holds information about a GLSL attribute or uniform variable.
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLSLVARIABLE_H
#define GLSLVARIABLE_H

#include <string>
#include "glbinding/gl/gl.h"



namespace nut
{
    class GLSLVariable
    {
        public:

        gl::GLuint program; /**< An OpenGL program where this variable is specified for. */
        gl::GLint location; /**< The location of the variable. */
        std::string name; /**< The name of the variable. */
        gl::GLint size; /**< The size of the variable. */
        gl::GLenum type; /**< The type of the variable. */
        bool isUniform; /**< True if it is an uniform variable. False if it is an attribute. */



        GLSLVariable() :
            program(0),
            location(-1),
            size(0),
            type(gl::GL_INT),
            isUniform(false)
        {
        }
    };
}

#endif // GLSLVARIABLE_H
