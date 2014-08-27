/** 
 * \file GLProgram.h
 * \brief This class create and handle OpenGL programs.
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <string>
#include <vector>
#include <GL/glew.h>



namespace nut
{
    class GLProgram
    {
        public:

        /**
         * Load shaders either by codes in files or strings containing the codes.
         * 
         * @param shaders A list containing a pair of shader type and shader code.
         * The shader code can be either paths to shaders files or strings containing
         * shaders codes.
         * @param isFilePath True if the list of shaders contains path.
         * False if the list contains shaders programs in strings.
         * @return An OpenGL program index, or zero in case of error.
         */
        static GLuint load(const std::vector< std::pair< GLenum, std::string> >& shaders, bool isFilePath);



        private:

        /**
         * Check if either a program or a shader was correctly created.
         * 
         * @param obj It can be either a shader or program index.
         * @param log A string containing details about the error or an empty string if no errors.
         * @return True if the status is OK. Otherwise, returns false and fill the log string with information from OpenGL.
         */
        static bool _checkStatus(GLuint obj, std::string& log);

    };
}

#endif // GLPROGRAM_H
