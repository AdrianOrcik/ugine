
-- TODO: make build system with CMake

workspace "ugine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- engine solution
project "ugine"
	location "ugine"
	kind "SharedLib" --dll
	language "C++"

	-- build directory of engine dll
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	-- objs which are not linked yet
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- files to be linked into dll lib
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cc"
	}

	-- external dependencies
	includedirs
	{
		"%{prj.name}/external_src/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On" 
		systemversion "10.0.17763.0"

		-- define solution macros
		defines
		{
			"UE_PLATFORM_WINDOWS",
			"UE_BUILD_DLL"
		}

		-- define what happend after build
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		optimize "On"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"UE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		optimize "On"