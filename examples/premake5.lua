
solution "glToolsExamples"
    configurations { "Debug" }
    location "build"

project "triangle"
    location    "build/triangle"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "../lib", "../build/Debug" }
    includedirs { "../include" }
    files       { "triangle/**.hpp", "triangle/**.cpp" }
    links       { "glTools" }

    postbuildcommands { "{COPY} ../../../build/Debug/glTools.* ../Debug/." }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "texture"
    location    "build/texture"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "../lib", "../build/Debug" }
    includedirs { "../include" }
    files       { "texture/**.hpp", "texture/**.cpp" }
    links       { "glTools" }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "multitex"
    location    "build/multitex"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "../lib", "../build/Debug" }
    includedirs { "../include" }
    files       { "multitex/**.hpp", "multitex/**.cpp" }
    links       { "glTools" }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }