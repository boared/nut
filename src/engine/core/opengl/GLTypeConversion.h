/** 
 * \file GLTypeConversion.h
 * \brief This class is used for type conversion between OpenGL and nut engine.
 * 
 * @author: Eder A. Perez.
 */

#ifndef GLTYPECONVERSION_H
#define GLTYPECONVERSION_H

#include "GL/glew.h"
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
         * @return A corresponding GLenum. Default is GL_FLOAT.
         */
        static GLenum typeToGLenum(Type type)
        {
            GLenum glType;

            switch (type)
            {
                case Type::CHAR:
                    glType = GL_BYTE;
                    break;

                case Type::INT:
                    glType = GL_INT;
                    break;

                case Type::I8:
                    glType = GL_BYTE;
                    break;

                case Type::I16:
                    glType = GL_SHORT;
                    break;

                case Type::I32:
                    glType = GL_INT;
                    break;

                case Type::UNSIGNED_CHAR:
                    glType = GL_UNSIGNED_BYTE;
                    break;
                    break;

                case Type::UNSIGNED_INT:
                    glType = GL_UNSIGNED_INT;
                    break;

                case Type::U8:
                    glType = GL_UNSIGNED_BYTE;
                    break;

                case Type::U16:
                    glType = GL_UNSIGNED_SHORT;
                    break;

                case Type::U32:
                    glType = GL_UNSIGNED_INT;
                    break;

                case Type::FLOAT:
                    glType = GL_FLOAT;
                    break;

                case Type::DOUBLE:
                    glType = GL_DOUBLE;
                    break;

                default:
                    glType = GL_FLOAT;
                    break;
            }

            return glType;
        }
    };
}

#endif // GLTYPECONVERSION_H
