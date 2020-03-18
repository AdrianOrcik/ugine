
-- TODO: make build system with CMake
-- TODO: study build systems

workspace "ugine"
	architecture "x64"
	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dir relative to root folder 
IncludeDir = {}
IncludeDir["GLFW"] = "ugine/external_src/glfw/include"
IncludeDir["Glad"] = "ugine/external_src/glad/include"
IncludeDir["ImGui"] = "ugine/external_src/imgui"

include "ugine/external_src/glfw"
include "ugine/external_src/glad"
include "ugine/external_src/imgui"

-- engine solution
project "ugine"
	location "ugine"
	kind "SharedLib" --dll
	language "C++"
	staticruntime "off"

	-- build directory of engine dll
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	-- objs which are not linked yet
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "uepch.h"
	pchsource"ugine/src/uepch.cc"

	-- files to be linked into dll lib
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cc"
	}

	-- external dependencies
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external_src/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		-- define solution macros
		defines
		{
			"UE_PLATFORM_WINDOWS",
			"UE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- define what happend after build
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "On"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cc"
	}

	-- linked on ugine solution
	includedirs
	{
		"ugine/external_src/spdlog/include",
		"ugine/src"
	}
    
	-- linked all ugine solition
	links
	{
		"ugine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "On"