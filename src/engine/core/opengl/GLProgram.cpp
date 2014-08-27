/** 
 * \file GLProgram.cpp
 * \brief This class create OpenGL programs.
 * 
 * @author: Eder A. Perez.
 */

#include <iostream>
#include <fstream>
#include "GLProgram.h"



namespace nut
{
    GLuint GLProgram::load(const std::vector< std::pair< GLenum, std::string> >& shaders, bool isFilePath)
    {
        // Check parameters
        if (shaders.size() == 0)
        {
            std::cerr << "GLShader: load error." << std::endl;
            return 0;
        }

        // Create program
        GLuint program = glCreateProgram();
        std::string log = "";
        std::vector<std::string> codes;

        if (program == 0)
        {
            std::cerr << "GLShader: glCreateProgram error." << std::endl;
            return 0;
        }

        // Load shaders from files
        if ( isFilePath )
        {
            for (size_t i = 0; i < shaders.size(); ++i)
            {
                std::ifstream in( shaders[i].second.c_str(), std::ios::in | std::ios::binary );

                // Put all text-file content in a string
                if (in.is_open())
                {
                    std::string shader;

                    in.seekg(0, std::ios::end);
                    size_t size = in.tellg();
                    in.seekg(0, std::ios::beg);
                    shader.resize(size);
                    in.read(&shader[0], size);
                    in.close();

                    codes.push_back(shader);
                }
            }
        }
        // Shaders' codes are in strings
        else
        {
            for (size_t i = 0; i < shaders.size(); ++i)
            {
                codes.push_back(shaders[i].second);
            }
        }

        // Attach shaders
        for (size_t i = 0; i < codes.size(); ++i)
        {
            GLuint shader = glCreateShader(shaders[i].first);

            // Load and compiles the shader
            const char* sdr = codes[i].c_str();
            glShaderSource(shader, 1, &sdr, NULL);
            glCompileShader(shader);

            // Check shader's status
            if ( !_checkStatus(shader, log) )
            {
                std::cerr << "GLShader::load: shaders[" << i << "] not attached." << std::endl;
                std::cerr << log;
                continue;
            }

            // Attach shader to program
            glAttachShader(program, shader);
            glDeleteShader(shader);
        }

        glLinkProgram(program);

        if ( !_checkStatus(program, log) )
        {
            glDeleteProgram(program);
            program = 0;

            std::cerr << "GLShader::load: Cannot load shaders." << std::endl;
            std::cerr << log;
        }

        return program;
    }



    bool GLProgram::_checkStatus(GLuint obj, std::string& log)
    {
        GLint status = GL_FALSE, len = 0;

        if( glIsShader(obj) )
        {
            glGetShaderiv( obj, GL_COMPILE_STATUS, &status );
        }
        else if( glIsProgram(obj) )
        {
            glGetProgramiv( obj, GL_LINK_STATUS, &status );
        }

        if( status == GL_TRUE )
        {
            log = "";
        }
        else
        {
            // Set log
            if( glIsShader(obj) )
            {
                glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &len );

                if (len > 0)
                {
                    GLchar* l = new GLchar[len];

                    glGetShaderInfoLog( obj, len, NULL, l );

                    log = l;

                    delete[] l;
                }
            }
            else if( glIsProgram(obj) )
            {
                glGetProgramiv( obj, GL_INFO_LOG_LENGTH, &len );

                if (len > 0)
                {
                    GLchar* l = new GLchar[len];

                    glGetProgramInfoLog( obj, len, NULL, l );

                    log = l;

                    delete[] l;
                }
            }
        }

        return status;
    }
}
