project "HEngine"
	kind "StaticLib"
	language "c++"
	cppdialect "c++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/HEngine/Source"
	}

	links
	{
		"gdi32.lib"
	}	

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
