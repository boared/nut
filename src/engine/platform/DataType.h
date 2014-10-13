/** 
 * \file DataType.h
 * \brief This header contains declarations of general purpose data types and some
 * functions to handle them.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef DATATYPE_H
#define DATATYPE_H

#include <cstdint>



namespace nut
{
    /// Definition of integers with specific number of bits

    typedef int8_t   I8;   /**< 8-bits signed integer. */
    typedef int16_t  I16;  /**< 16-bits signed integer. */
    typedef int32_t  I32;  /**< 32-bits signed integer. */
    typedef int64_t  I64;  /**< 64-bits signed integer. */

    typedef uint8_t  U8;   /**< 8-bits unsigned integer. */
    typedef uint16_t U16;  /**< 16-bits unsigned integer. */
    typedef uint32_t U32;  /**< 32-bits unsigned integer. */
    typedef uint64_t U64;  /**< 64-bits unsigned integer. */

    typedef intptr_t IPTR;  /**< Hold a value converted from a void pointer. */

    /**
     * \brief Represents a value both as @int and @float.
     * 
     * It's useful when one wants to manipulate the bits of a floating-point
     * number as an integer value.
     */
    union IntFloat
    {
        int   asInt;   /**< Value represented as an integer. */
        float asFloat; /**< Value represented as a floating-point number. */
    };



    /**
     * \brief Enumeration for data type.
     */
    enum class Type
    {
        UNKNOW,
        CHAR,
        INT,
        I8,
        I16,
        I32,
        I64,
        UNSIGNED_CHAR,
        UNSIGNED_INT,
        U8,
        U16,
        U32,
        U64,
        FLOAT,
        DOUBLE,
        IPTR
    };



    /**
     * \brief Operations on data types.
     */
    class DataType
    {
        public:

        /**
         * Get the size in bytes of a type.
         * 
         * @param type Input type.
         * @return Size in bytes of @type.
         */
        static size_t getSize(Type type)
        {
            size_t size = 0;

            switch (type)
            {
                case Type::CHAR:
                    size = sizeof(char);
                    break;

                case Type::INT:
                    size = sizeof(int);
                    break;

                case Type::I8:
                    size = sizeof(I8);
                    break;

                case Type::I16:
                    size = sizeof(I16);
                    break;

                case Type::I32:
                    size = sizeof(I32);
                    break;

                case Type::I64:
                    size = sizeof(I64);
                    break;

                case Type::UNSIGNED_CHAR:
                    size = sizeof(unsigned char);
                    break;
                    break;

                case Type::UNSIGNED_INT:
                    size = sizeof(unsigned int);
                    break;

                case Type::U8:
                    size = sizeof(U8);
                    break;

                case Type::U16:
                    size = sizeof(U16);
                    break;

                case Type::U32:
                    size = sizeof(U32);
                    break;

                case Type::U64:
                    size = sizeof(U64);
                    break;

                case Type::FLOAT:
                    size = sizeof(float);
                    break;

                case Type::DOUBLE:
                    size = sizeof(double);
                    break;

                case Type::IPTR:
                    size = sizeof(IPTR);
                    break;

                default:
                    break;
            }
            
            return size;
        }

        /**
         * \brief Swap between 16-bits little-endian and big-endian unsigned integers.
         * 
         * @param value A 16-bits L-endian/B-endian value.
         * @return A 16-bits B-endian/L-endian value.
         */
        static U16 endianSwapU16(U16 value)
        {
            return ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
        }

        /**
         * \brief Swap between 32-bits little-endian and big-endian unsigned integers.
         * 
         * @param value A 32-bits L-endian/B-endian value.
         * @return A 32-bits B-endian/L-endian value.
         */
        static U32 endianSwapU32(U32 value)
        {
            return ((value & 0x000000FF) << 24) |
                   ((value & 0x0000FF00) << 8)  |

                   ((value & 0x00FF0000) >> 8)  |
                   ((value & 0xFF000000) >> 24);
        }

        /**
         * \brief Swap between 64-bits little-endian and big-endian unsigned integers.
         * 
         * @param value A 64-bits L-endian/B-endian value.
         * @return A 64-bits B-endian/L-endian value.
         */
        static U64 endianSwapU64(U64 value)
        {
            return ((value & 0x00000000000000FF) << 56) |
                   ((value & 0x000000000000FF00) << 40) |
                   ((value & 0x0000000000FF0000) << 24) |
                   ((value & 0x00000000FF000000) <<  8) |

                   ((value & 0x000000FF00000000) >>  8) |
                   ((value & 0x0000FF0000000000) >> 24) |
                   ((value & 0x00FF000000000000) >> 40) |
                   ((value & 0xFF00000000000000) >> 56);
        }

        /**
         * \brief Swap between 16-bits little-endian and big-endian signed integers.
         * 
         * @param value A 16-bits L-endian/B-endian value.
         * @return A 16-bits B-endian/L-endian value.
         */
        static I16 endianSwapI16(I16 value)
        {
            return ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
        }

        /**
         * \brief Swap between 32-bits little-endian and big-endian signed integers.
         * 
         * @param value A 32-bits L-endian/B-endian value.
         * @return A 32-bits B-endian/L-endian value.
         */
        static I32 endianSwapI32(I32 value)
        {
            return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) |
                   ((value & 0x00FF0000) >> 8)  | ((value & 0xFF000000) >> 24);
        }

        /**
         * \brief Swap between 64-bits little-endian and big-endian signed integers.
         * 
         * @param A 64-bits L-endian/B-endian value.
         * @return A 64-bits L-endian/B-endian value.
         */
        static I64 endianSwapI64(I64 value)
        {
            return ((value & 0x00000000000000FF) << 56) |
                   ((value & 0x000000000000FF00) << 40) |
                   ((value & 0x0000000000FF0000) << 24) |
                   ((value & 0x00000000FF000000) <<  8) |

                   ((value & 0x000000FF00000000) >>  8) |
                   ((value & 0x0000FF0000000000) >> 24) |
                   ((value & 0x00FF000000000000) >> 40) |
                   ((value & 0xFF00000000000000) >> 56);
        }

        /**
         * \brief Swap between 32-bits little-endian and big-endian float point numbers.
         * 
         * @param value Floating-point value.
         * @return Swapped float value.
         */
        static float endianSwapFloat(float value)
        {
            IntFloat u;
            u.asFloat = value;

            if (sizeof(int) == 4)
                u.asInt = endianSwapI32(u.asInt);
            else
                u.asInt = endianSwapI64(u.asInt);

            return u.asFloat;
        }

        /**
         * \brief Type punning.
         * 
         * @param value Floating-point value.
         * @return A @int which all bits has the same values as the input float's bits
         */
        static int punning(float value)
        {
            IntFloat u;
            u.asFloat = value;
            return u.asInt;
        }
    };
}

#endif // DATATYPE_H
