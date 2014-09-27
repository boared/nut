/** 
 * \file GLProgram.cpp
 * \brief This class creates and handle OpenGL programs.
 * 
 * @author: Eder A. Perez.
 */

#include <fstream>
#include "GLProgram.h"



namespace nut
{
    GLProgram::GLProgram() : _handle(0), _isLinked(false), _log("")
    {
    }



    GLProgram::~GLProgram()
    {
        GLint currentProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        
        // Stop program execution before deleting it
        if (currentProgram == static_cast<GLint>(_handle))
        {
            glUseProgram(0);            
        }

        glDeleteProgram(_handle);
    }



    bool GLProgram::compileShader(const char* shader, GLenum type, bool isFilePath)
    {
        // Create an OpenGL program if it doesn't exist already
        if (_handle == 0)
        {
            _handle = glCreateProgram();

            if (_handle == 0)
            {
                _log = "nut::GLProgram error: glCreateProgram failed.";
                return false;
            }
        }

        std::string code;

        // Load shader from file or...
        if (isFilePath)
        {
            std::ifstream in(shader, std::ios::in | std::ios::binary);

            // Put all text-file content in a string
            if (in.is_open())
            {
                in.seekg(0, std::ios::end);
                size_t size = in.tellg();
                in.seekg(0, std::ios::beg);
                code.resize(size);
                in.read(&code[0], size);
                in.close();
            }
        }
        // ... the string contains shader code
        else
        {
            code = shader;
        }

        /// 1. Create a shader object

        GLuint shaderHandle = glCreateShader(type);

        // Check for error
        if (shaderHandle == 0)
        {
            _log = "nut::GLProgram error: glCreateShader failed.";
            return false;
        }

        /// 2. Load and compile the shader
        
        const GLchar* c = code.c_str();
        glShaderSource(shaderHandle, 1, &c, NULL);

        glCompileShader(shaderHandle);

        // Check compilation status and set log in case of error
        if (!_checkStatus(shaderHandle))
        {
            return false;
        }

        /// 3. Attach shader to program

        glAttachShader(_handle, shaderHandle);

        glDeleteShader(shaderHandle);
        
        return true;
    }



    bool GLProgram::link()
    {
        glLinkProgram(_handle);

        if (_checkStatus(_handle))
        {
            _isLinked = true;
        }
        else
        {
            _isLinked = false;
        }

        return _isLinked;
    }



    void GLProgram::getActiveUniforms(std::vector<GLSLVariable>& list) const
    {
        if (_isLinked)
        {
            GLint nUniforms, maxLength;

            /// 1. Retrieve the maximum length of the names of all the active uniforms
            /// and the number of active uniforms
            glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
            glGetProgramiv(_handle, GL_ACTIVE_UNIFORMS, &nUniforms);

            /// 2. Allocate space to store each uniform variable's name
            GLchar* name = new GLchar[maxLength];

            /// 3. Retrieve information about each active uniform
            GLint size, location;
            GLsizei written;
            GLenum type;
            for (GLint i = 0; i < nUniforms; ++i)
            {
                glGetActiveUniform(_handle, i, maxLength, &written, &size, &type, name);
                location = glGetUniformLocation(_handle, name);
                
                GLSLVariable variable(_handle, location, size, type, name, true);

                list.push_back(variable);
            }

            delete[] name;
        }
    }



    void GLProgram::getActiveAttributes(std::vector<GLSLVariable>& list) const
    {
        if (_isLinked)
        {
            GLint nAttribs, maxLength;

            /// 1. Retrieve the maximum length of the names of all the active attributes
            /// and the number of active attributes
            glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
            glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

            /// 2. Allocate space to store each attribute's name
            GLchar* name = new GLchar[maxLength];

            /// 3. Retrieve information about each active uniform
            GLint size, location;
            GLsizei written;
            GLenum type;
            for (GLint i = 0; i < nAttribs; ++i)
            {
                glGetActiveAttrib(_handle, i, maxLength, &written, &size, &type, name);
                location = glGetAttribLocation(_handle, name);
                
                GLSLVariable variable(_handle, location, size, type, name, false);

                list.push_back(variable);
            }

            delete[] name;
        }
    }



    void GLProgram::setUniform(const char* name, float val) const
    {
        GLint loc = getUniform(name);
        
        if (loc != -1)
        {
            setUniform(loc, val);
        }
    }
    
    
    
    void GLProgram::setUniform(const char* name, int val) const
    {
        GLint loc = getUniform(name);
        
        if (loc != -1)
        {
            setUniform(loc, val);
        }
    }
    
    
    
    void GLProgram::setUniform(const char* name, const Vector2D<float>& v) const
    {
        GLint loc = getUniform(name);
        
        if (loc != -1)
        {
            setUniform(loc, v);
        }
    }



    void GLProgram::setUniform(const char* name, const Vector3D<float>& v) const
    {
        GLint loc = getUniform(name);
        
        if (loc != -1)
        {
            setUniform(loc, v);
        }
    }


    
    void GLProgram::setUniform(const char* name, const Vector4D<float>& v) const
    {
        GLint loc = getUniform(name);
        
        if (loc != -1)
        {
            setUniform(loc, v);
        }
    }


    
    void GLProgram::setUniform(const char* name, Matrix3x3<float>& m) const
    {
        GLint loc = getUniform(name);
        
        if (loc != -1)
        {
            setUniform(loc, m);
        }
    }


    
    void GLProgram::setUniform(const char* name, Matrix4x4<float>& m) const
    {
        GLint loc = getUniform(name);

        if (loc != -1)
        {
            setUniform(loc, m);
        }
    }



    void GLProgram::setUniform(const char* name, GLMatrix<float>& m) const
    {
        GLint loc = getUniform(name);

        if (loc != -1)
        {
            setUniform(loc, m);
        }
    }



    bool GLProgram::_checkStatus(GLuint obj)
    {
        GLint status = GL_FALSE, len = 0;

        if(glIsShader(obj))
        {
            glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
        }
        else if(glIsProgram(obj))
        {
            glGetProgramiv(obj, GL_LINK_STATUS, &status);
        }

        if(status == GL_TRUE)
        {
            _log = "";
        }
        else
        {
            // Set log
            if(glIsShader(obj))
            {
                glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len);

                if (len > 0)
                {
                    GLchar* l = new GLchar[len];

                    glGetShaderInfoLog(obj, len, NULL, l);

                    _log = l;

                    delete[] l;
                }
            }
            else if(glIsProgram(obj))
            {
                glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len);

                if (len > 0)
                {
                    GLchar* l = new GLchar[len];

                    glGetProgramInfoLog(obj, len, NULL, l);

                    _log = l;

                    delete[] l;
                }
            }
        }

        return status;
    }
}
