/** 
 * \file GLTypeConversion.h
 * \brief This class is used for type conversion between OpenGL and nut engine.
 * 
 * @author: Eder A. Perez.
 */

#ifndef GLTYPECONVERSION_H
#define GLTYPECONVERSION_H

#include "glbinding/gl/gl.h"
#include "DataType.h"



namespace nut
{
    class GLTypeConversion
    {
        public:

        /**
         * Convert an enum class Type to a GLenum type.
         * 
         * @param type An enum class Type.
         * @return A corresponding GLenum. If there's no corresponding type,
         * returns GL_FALSE.
         */
        static gl::GLenum typeToGLenum(Type type)
        {
            gl::GLenum glType = gl::GL_INT;

            switch (type)
            {
                case Type::CHAR:
                    glType = gl::GL_BYTE;
                    break;

                case Type::INT:
                    glType = gl::GL_INT;
                    break;

                case Type::I8:
                    glType = gl::GL_BYTE;
                    break;

                case Type::I16:
                    glType = gl::GL_SHORT;
                    break;

                case Type::I32:
                    glType = gl::GL_INT;
                    break;

                case Type::UNSIGNED_CHAR:
                    glType = gl::GL_UNSIGNED_BYTE;
                    break;

                case Type::UNSIGNED_INT:
                    glType = gl::GL_UNSIGNED_INT;
                    break;

                case Type::U8:
                    glType = gl::GL_UNSIGNED_BYTE;
                    break;

                case Type::U16:
                    glType = gl::GL_UNSIGNED_SHORT;
                    break;

                case Type::U32:
                    glType = gl::GL_UNSIGNED_INT;
                    break;

                case Type::FLOAT:
                    glType = gl::GL_FLOAT;
                    break;

                case Type::DOUBLE:
                    glType = gl::GL_DOUBLE;
                    break;

                default:
                    break;
            }

            return glType;
        }
    };
}

#endif // GLTYPECONVERSION_H
