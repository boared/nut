/** 
 * \file GLProgram.cpp
 * \brief This class creates and handle OpenGL programs.
 * 
 * @author: Eder A. Perez.
 */

#include <fstream>
#include "GLProgram.h"

using namespace gl;



namespace nut
{
    GLProgram::GLProgram() : _handle(0), _isLinked(false)
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

        if (shaderHandle == 0)
        {
            _log = "nut::GLProgram error: glCreateShader failed.";
            return false;
        }

        /// 2. Load and compile the shader
        
        const GLchar* c = code.c_str();
        glShaderSource(shaderHandle, 1, &c, NULL);

        glCompileShader(shaderHandle);

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
            GLint count, maxLength;

            /// 1. Retrieve the maximum length of the names of all the active uniforms
            /// and the number of active uniforms
            glGetProgramiv(_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
            glGetProgramiv(_handle, GL_ACTIVE_UNIFORMS, &count);

            /// 2. Allocate space to store each uniform variable's name
            GLchar* name = new GLchar[maxLength];

            /// 3. Retrieve information about each active uniform
            GLint size, location;
            GLsizei written;
            GLenum type;
            
            list.reserve(count);
            for (GLint i = 0; i < count; ++i)
            {
                glGetActiveUniform(_handle, i, maxLength, &written, &size, &type, name);
                location = glGetUniformLocation(_handle, name);
                
                GLSLVariable variable;
                variable.program = _handle;
                variable.location = location;
                variable.name = name;
                variable.size = size;
                variable.type = type;
                variable.isUniform = true;

                list.push_back(variable);
            }

            delete[] name;
        }
    }



    void GLProgram::getActiveAttributes(std::vector<GLSLVariable>& list) const
    {
        if (_isLinked)
        {
            GLint count, maxLength;

            /// 1. Retrieve the maximum length of the names of all the active attributes
            /// and the number of active attributes
            glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
            glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &count);

            /// 2. Allocate space to store each attribute's name
            GLchar* name = new GLchar[maxLength];

            /// 3. Retrieve information about each active uniform
            GLint size, location;
            GLsizei written;
            GLenum type;
            
            list.reserve(count);
            for (GLint i = 0; i < count; ++i)
            {
                glGetActiveAttrib(_handle, i, maxLength, &written, &size, &type, name);
                location = glGetAttribLocation(_handle, name);

                GLSLVariable variable;
                variable.program = _handle;
                variable.location = location;
                variable.name = name;
                variable.size = size;
                variable.type = type;
                variable.isUniform = false;

                list.push_back(variable);
            }

            delete[] name;
        }
    }



    void GLProgram::getActiveSubroutines(std::vector<std::string>& list, GLenum shaderType) const
    {
        GLint count;
        glGetProgramStageiv(_handle, shaderType, GL_ACTIVE_SUBROUTINES, &count);

        GLint biggerNameLength;
        glGetProgramStageiv(_handle, shaderType, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &biggerNameLength);

        if (count != GL_INVALID_ENUM && biggerNameLength != GL_INVALID_ENUM)
        {
            list.reserve(count);

            GLchar* name = new GLchar[biggerNameLength];

            for (GLuint index = 0; index < static_cast<GLuint>(count); ++index)
            {
                glGetActiveSubroutineName(_handle, shaderType, index, biggerNameLength, 0, name);

                list.push_back(std::string(name));
            }

            delete[] name;
        }
    }



    void GLProgram::getActiveSubroutineUniforms(std::vector<GLSLSubroutineUniform>& list, GLenum shaderType) const
    {
        GLint count;
        glGetProgramStageiv(_handle, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORMS, &count);

        GLint biggerNameLength;
        glGetProgramStageiv(_handle, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &biggerNameLength);

        if (count != GL_INVALID_ENUM && biggerNameLength != GL_INVALID_ENUM)
        {
            list.reserve(count);

            GLchar* name = new GLchar[biggerNameLength];

            for (GLuint index = 0; index < static_cast<GLuint>(count); ++index)
            {
                glGetActiveSubroutineUniformName(_handle, shaderType, index, biggerNameLength, 0, name);

                GLint location = glGetSubroutineUniformLocation(_handle, shaderType, name);

                GLint compatibleSubroutinesCount;
                glGetActiveSubroutineUniformiv(_handle, shaderType, index, GL_NUM_COMPATIBLE_SUBROUTINES, &compatibleSubroutinesCount);

                GLint* compatibleSubroutines = new GLint[compatibleSubroutinesCount];
                glGetActiveSubroutineUniformiv(_handle, shaderType, index, GL_COMPATIBLE_SUBROUTINES, compatibleSubroutines);

                // @uniformArraySize is 1 if subroutine uniform is not an array
                GLint uniformArraySize;
                glGetActiveSubroutineUniformiv(_handle, shaderType, index, GL_UNIFORM_SIZE, &uniformArraySize);

                GLSLSubroutineUniform subroutineUniform;

                subroutineUniform.program = _handle;
                subroutineUniform.location = location;
                subroutineUniform.shaderType = shaderType;
                subroutineUniform.name = name;
                subroutineUniform.compatibleSubroutines = std::vector<GLint>(compatibleSubroutines, compatibleSubroutines + compatibleSubroutinesCount);
                subroutineUniform.uniformArraySize = uniformArraySize;

                list.push_back(subroutineUniform);

                delete[] compatibleSubroutines;
            }

            delete[] name;
        }
    }



    bool GLProgram::_checkStatus(GLuint obj)
    {
        GLint status = static_cast<GLint>(GL_FALSE), len = 0;

        if(glIsShader(obj) == GL_TRUE)
        {
            glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
        }
        else if(glIsProgram(obj) == GL_TRUE)
        {
            glGetProgramiv(obj, GL_LINK_STATUS, &status);
        }

        if(status == static_cast<GLint>(GL_TRUE))
        {
            _log = "";
        }
        else
        {
            // Set log
            if(glIsShader(obj) == GL_TRUE)
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
            else if(glIsProgram(obj) == GL_TRUE)
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
