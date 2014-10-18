solution "nut"

    local buildPath = "build"
    local includePath
    local action
    local cxxstd -- C++ standard



    if _ACTION then
        action = _ACTION
    end



    -- Setting C++11 standard
    if _ACTION == "gmake" then
        cxxstd = "-std=c++11"
    elseif _ACTION == "vs2013" or _ACTION == "vs2012" or
        _ACTION == "vs2010" or _ACTION == "vs2008" then
        cxxstd = ""
    else
        print("Error: Could not set C++11 standard.")
        cxxstd = ""
    end



    -- Creating include dir and copying headers
    includePath = buildPath .. "/" .. action .. "/include"
    print "Creating include directory."
    os.mkdir(includePath)
    print "Copying headers to include directory."
    os.copyfile("src/engine/*.h", includePath)
    includeDirs = os.matchdirs("src/engine/**");
    for count = 1, #includeDirs do
        os.copyfile(includeDirs[count] .. "/*.h", includePath)
    end



    -- Setting solution options
    configurations { "ReleaseStatic", "ReleaseShared", "DebugStatic", "DebugShared" }
    location (buildPath .. "/" .. action)
    buildoptions { cxxstd }



    -- Compiles nut engine either as static or shared (DLL) library
    project "nut"
        targetname "nut"
        targetdir(buildPath .. "/" .. action .. "/lib")
        location(buildPath .. "/" .. action)
        includedirs { "src/engine/**" }
        includedirs { "extlibs/glbinding/glbinding-1.0.2/include/" }
        libdirs { "extlibs/glbinding/glbinding-1.0.2/lib/" }
        links { "glbinding" }
        files { "src/engine/**.h", "src/engine/**.cpp" }
        flags { "ExtraWarnings" }

        configuration "ReleaseStatic"
            flags { "Optimize" }
            kind "StaticLib"
            language "C++"

        configuration "ReleaseShared"
            flags { "Optimize" }
            kind "SharedLib"
            language "C++"

        configuration "DebugStatic"
            flags { "Symbols" }
            kind "StaticLib"
            language "C++"

        configuration "DebugShared"
            flags { "Symbols" }
            kind "SharedLib"
            language "C++"
