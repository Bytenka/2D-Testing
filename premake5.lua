workspace "TESTLIAS"
configurations {"Debug", "Release"}

project "TESTLIAS"
kind "ConsoleApp"
language "C++"
cppdialect "C++14"

files {"src/**.h", "src/**.hpp", "src/**.c", "src/**.cpp"}
links {"stdc++", "glfw", "GL", "png", "pthread", "dl"}
buildoptions {"-Wall", "-Winvalid-pch"}

objdir("obj")
targetdir("bin/%{cfg.buildcfg}")
targetname "program.out"

pchheader "pch.h"
pchsource "pch.cpp"

includedirs {
    "src", -- Needed for precompiled headers
    "vendor/spdlog/include", -- git submodule add https://github.com/gabime/spdlog.git
    "vendor/glm", -- git submodule add -b stable https://github.com/g-truc/glm.git
    "../../../../Dropbox/OpenGL/Libraries/Includes"
}

filter {"configurations:Debug"}
defines {"DEBUG"}
symbols "On"
optimize "Off"

filter {"configurations:Release"}
defines {"NDEBUG"}
optimize "On"

filter {"files:**.c"}
flags {"NoPCH"}

filter {"action:vs*"}
defines {"_CRT_SECURE_NO_WARNINGS"}
