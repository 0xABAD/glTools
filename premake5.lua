
solution "glTools"
    configurations { "Debug", "Release" }
    location "build"

project "glTools"
    location    "build/glTools"
    language    "C++"
    kind        "StaticLib"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "lib" }
    includedirs { "include" }
    files       { "include/glt/**.hpp", "src/**.cpp" }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "glToolsTest"
    location    "build/glToolsTest"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "lib", "build/%{cfg.buildcfg}" }
    includedirs { "include", "test" }
    files       { "test/**.cpp" }
    links       { "glTools", "opengl32", "glfw3" }

    filter "system:windows"
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }
