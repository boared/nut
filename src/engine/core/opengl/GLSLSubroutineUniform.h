/** 
 * \file GLSLSubroutineUniform.h
 * \brief This class holds information about a GLSL subroutine uniform.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLSLSUBROUTINEUNIFORM_H
#define GLSLSUBROUTINEUNIFORM_H

#include <string>
#include <vector>
#include "glbinding/gl/gl.h"



namespace nut
{
    class GLSLSubroutineUniform
    {
        public:

        gl::GLuint program; /**< An OpenGL program where this subroutine uniform is specified for. */
        gl::GLint location; /**< The location of the subroutine uniform. If this subroutine uniform is an array, the location in the i-th index is location + i. */
        gl::GLenum shaderType; /**< A subroutine uniform is always associated to only one shader stage. */
        std::string name; /**< The name of the subroutine uniform. */
        std::vector<gl::GLint> compatibleSubroutines; /**< List with indices of all compatible subroutines. */
        gl::GLint uniformArraySize; /*< Number of elements in case this subroutine uniform is an array, 1 if it is not. */



        GLSLSubroutineUniform() :
            program(0),
            location(-1),
            shaderType(gl::GL_INVALID_ENUM),
            compatibleSubroutines(),
            uniformArraySize(0)
        {
        }
    };
}

#endif // GLSLSUBROUTINEUNIFORM_H
