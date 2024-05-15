workspace "Grafika"
    configurations { "Debug", "Release" }
    startproject "Grafika"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

group ""
project "Grafika"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}/grafika"
    objdir "obj/%{cfg.buildcfg}/grafika"

    includedirs { 
	    "src/",
	    "vendor/glad/include/",
	    "vendor/glfw/include/",
		"vendor/glm/",
        "vendor/stb/include",
        "vendor/assimp/include"
    }
    
    files { 
	    "src/*.cpp",
	    "src/*.h",
		"src/*.hpp"
    }

    links { "GLFW", "GLAD", "GLM", "assimp-vc143-mt" }
    libdirs {"vendor/assimp/lib/x64"}

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11", "STB_IMAGE_IMPLEMENTATION", "GLM_ENABLE_EXPERIMENTAL" }

    filter "system:windows"
        defines { "_WINDOWS", "STB_IMAGE_IMPLEMENTATION", "GLM_ENABLE_EXPERIMENTAL" }

    postbuildcommands {
        "{COPY} \"vendor/assimp/bin/x64/assimp-vc143-mt.dll\" bin/%{cfg.buildcfg}/grafika"
    }

group "Dependencies"
    include "vendor/glfw.lua"
    include "vendor/glad.lua"
	include "vendor/glm.lua"
