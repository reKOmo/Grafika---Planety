project "STB"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"

	targetdir "../bin/%{cfg.buildcfg}/stb"
	objdir "../obj/%{cfg.buildcfg}/stb"
	
	includedirs { "glm/" }

	files
	{
		"stb/**"
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"STB_IMAGE_IMPLEMENTATION"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"STB_IMAGE_IMPLEMENTATION"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"