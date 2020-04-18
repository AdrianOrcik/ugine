
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
IncludeDir["glm"] = "ugine/external_src/glm"
IncludeDir["stb_image"] = "ugine/external_src/stb_image"
IncludeDir["tweeny"] = "ugine/external_src/tweeny/include"

include "ugine/external_src/glfw"
include "ugine/external_src/glad"
include "ugine/external_src/imgui"

-- engine solution
project "ugine"
	location "ugine"
	kind "staticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{prj.name}/src/**.cc",
		"%{prj.name}/external_src/stb_image/**.h",
		"%{prj.name}/external_src/stb_image/**.cc",
		"%{prj.name}/external_src/tweeny/include/**.h",
		"%{prj.name}/external_src/glm/glm/**.hpp",
		"%{prj.name}/external_src/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	-- external dependencies
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external_src/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.tweeny}"
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

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "on"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"ugine/external_src/tweeny/include",
		"ugine/src",
		"ugine/external_src",
		"%{IncludeDir.glm}"
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
		symbols "on"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "on"