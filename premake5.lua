workspace "Parallax"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"ReleaseNoAudio"
	}

	startproject "Sandbox"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "hypermath"
		location "hypermath"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"

		targetdir ("build/bin/" .. outputdir .. "/hypermath")
		objdir("build/obj/" .. outputdir .. "/hypermath")

		files {
			"hypermath/**.h",
			"hypermath/**.cpp"
		}

		filter "system:windows"
			staticruntime "off"
			systemversion "10.0.17763.0"	

		filter "configurations:Debug"
			symbols "On"
			inlining "Disabled"

		filter "configurations:Release*"
			optimize "Speed"
			inlining "Auto"
			floatingpoint "Fast"

		filter {"system:windows", "configurations:Release"}

			buildoptions {
				"/Ot",
				"/GL"
			}

		filter {}

	project "parallax"
		location "parallax"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"

		targetdir ("build/bin/" .. outputdir .. "/parallax")
		objdir ("build/obj/" .. outputdir .. "/parallax")

		files {
			"parallax/src/**.h",
			"parallax/src/**.cpp",
			"parallax/src/**.inl",
			"parallax/src/**.c",
			"vendor/gl3w/src/gl3w.c"
		}

		includedirs {
			"vendor/freetype-2.9.1/include",
			"vendor/glfw-3.2.1/include",
			"vendor/gl3w/include",
			"hypermath/src/",
			"parallax/src/ext/"
		}

		filter "system:windows"
			staticruntime "off"
			systemversion "10.0.17763.0"	

		filter "configurations:not ReleaseNoAudio"
			defines {
				"PARALLAX_ENABLE_AUDIO"
			}

		filter "configurations:Debug"
			symbols "On"
			inlining "Disabled"

			defines {
				"PARALLAX_DEBUG",
				"PARALLAX_API_OPENGL",
				"PARALLAX_USING_IMGUI",
				"PARALLAX_ENABLE_MEMORY_LOGGING",
				"_CRT_SECURE_NO_WARNINGS",
				"_CRT_NONSTDC_NO_DEPRECATE",
				"IMGUI_IMPL_OPENGL_LOADER_GL3W"
			}

		filter {"configurations:Release*"}
			optimize "Speed"
			inlining "Auto"
			floatingpoint "Fast"

			defines {
				"_CRT_SECURE_NO_WARNINGS",
				"_CRT_NONSTDC_NO_DEPRECATE",
				"PARALLAX_API_OPENGL",
				"IMGUI_IMPL_OPENGL_LOADER_GL3W"
			}

		filter {"system:windows", "configurations:Release*"}

			buildoptions {
				"/Ot",
				"/GL"
			}

		filter {}

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"

		targetdir ("build/bin/" .. outputdir .. "/Sandbox")
		objdir ("build/obj/" .. outputdir .. "/Sandbox")

		files {
			"Sandbox/**.cpp",
			"Sandbox/**.h"
		}

		includedirs {
			"parallax/src/",
			"hypermath/src/",
			"vendor/glfw-3.2.1/include",
			"vendor/gl3w/include",
		}

		libdirs {
			"parallax/lib"
		}

		links {
			"freetype",
			"opengl32",
			"glfw3",
			"parallax",
			"hypermath"
		}

		filter "configurations:Release"
			links {"OpenAL32", "gorilla"}

		filter "configurations:Debug"
			links {"OpenAL32", "gorilla"}

		filter "system:windows"
			staticruntime "off"
			systemversion "10.0.17763.0"	

		filter "configurations:not ReleaseNoAudio"
		defines {
			"PARALLAX_ENABLE_AUDIO"
		}

		filter "configurations:Debug"
			symbols "On"
			inlining "Disabled"

			defines {
				"PARALLAX_DEBUG",
				"PARALLAX_API_OPENGL",
				"PARALLAX_ENABLE_MEMORY_LOGGING",
			}

		filter "configurations:Release*"
			optimize "Speed"
			inlining "Auto"
			floatingpoint "Fast"

		defines {
			"PARALLAX_API_OPENGL"
		}

		filter {"system:windows", "configurations:Release*"}

			buildoptions {
				"/Ot",
				"/GL"
			}

		filter {}