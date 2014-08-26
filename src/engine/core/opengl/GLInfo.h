/** 
 * \file GLInfo.h
 * \brief This class provides useful information about supported OpenGL API and
 * GLSL version of the current driver. Both @getVendor and @getRenderer returns
 * strings that together uniquely specify a platform. They're good to be used by
 * platform-recognition algorithms.
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLINFO_H
#define GLINFO_H

#include <string>
#include <vector>
#include <GL/glew.h>



namespace nut
{
    class GLInfo
    {
        public:

        /**
         * Get the company responsible for this GL implementation. This name does
         * not change from release to release.
         * 
         * return The name of the vendor.
         */
        static std::string getVendor()
        {
            const char *vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));

            return std::string(vendor);
        }

        /**
         * Get the name of the renderer. This name is typically specific to a
         * particular configuration of a hardware platform. It does not change
         * from release to release.
         * 
         * return The name of the renderer.
         */
        static std::string getRenderer()
        {
            const char *renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));

            return std::string(renderer);
        }

        /**
         * Get a version or release number for this OpenGL API.
         * 
         * return A version or release number.
         */
        static std::string getVersion()
        {
            const char *version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

            return std::string(version);
        }

        /**
         * Get a version or release number for the shading language.
         * 
         * return A version or release number for the shading language.
         */
        static std::string getGLSLVersion()
        {
            const char *glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

            return std::string(glslVersion);
        }

        /**
         * Get a version or release number for this OpenGL API in integer format.
         * 
         * @param major The major version number of the OpenGL API supported by
         * the current context.
         * @param minor The minor version number of the OpenGL API supported by
         * the current context.
         */
        static void getVersion(GLint& major, GLint& minor)
        {
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MINOR_VERSION, &minor);
        }

        /**
         * Get a list of all supported extensions of the current OpenGL implementation
         * 
         * @param extensions A list that will hold all supported extension names.
         */
        static void getExtensions(std::vector<std::string>& extensions)
        {
            GLint nExtensions;

            glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

            extensions.clear();
            extensions.reserve(nExtensions);

            for (int i = 0; i < nExtensions; ++i)
            {
                const char* extension = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));

                extensions.push_back(std::string(extension));
            }
        }
    };
}

#endif // GLINFO_H
