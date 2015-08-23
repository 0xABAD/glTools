
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
    links       { "glTools", "opengl32", "glfw3" }
    
    filter "system:windows"
        libdirs { os.findlib("opengl32") }

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
    links       { "glTools", "opengl32", "glfw3" }
    
    filter "system:windows"
        libdirs { os.findlib("opengl32") }

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
    links       { "glTools", "opengl32", "glfw3" }
    
    filter "system:windows"
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "spincube"
    location    "build/spincube"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "../lib", "../build/Debug" }
    includedirs { "../include" }
    files       { "spincube/**.hpp", "spincube/**.cpp" }
    links       { "glTools", "opengl32", "glfw3" }
    
    filter "system:windows"
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "textfont"
    location    "build/textfont"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "../lib", "../build/Debug" }
    includedirs { "../include" }
    files       { "textfont/**.hpp", "textfont/**.cpp" }
    links       { "glTools", "opengl32", "glfw3" }
    
    filter "system:windows"
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "callbacks"
    location    "build/callbacks"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "../lib", "../build/Debug" }
    includedirs { "../include" }
    files       { "callbacks/**.hpp", "callbacks/**.cpp" }
    links       { "glTools", "opengl32", "glfw3" }
    
    filter "system:windows"
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }