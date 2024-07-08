workspace "HEngine"
	architecture "x86_64"
	startproject "Test"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

	defines
	{
		"UNICODE"
	}

	include "HEngine"
	include "Test"
