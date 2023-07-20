project "HEngine"
	kind "StaticLib"
	language "C++"
	targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" ..outputdir.. "/%{prj.name}")

files {
	"include/**.h",
	"src/**.cpp"
}

includedirs {
	"include"
}