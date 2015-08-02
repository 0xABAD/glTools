
solution "glTools"
    configurations { "Debug", "Release" }
    location "build"

project "glTools"
    location    "build/glTools"
    language    "C++"
    kind        "SharedLib"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "lib" }
    includedirs { "include" }
    files       { "include/glt/**.hpp", "src/**.cpp" }
    defines     { "GLT_EXPORTS" }

    postbuildcommands { "{COPY} ../../lib/glfw3.dll ../Debug/." }

    filter "system:windows"
        links   { "glfw3dll", "opengl32" }
        libdirs { os.findlib("opengl32") }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }

project "glToolsTest"
    location    "build/glToolsTest"
    language    "C++"
    kind        "ConsoleApp"
    targetdir   "build/%{cfg.buildcfg}"
    libdirs     { "lib" }
    includedirs { "include", "test" }
    files       { "test/**.cpp" }
    links       { "glTools" }

    filter "configurations:Debug*"
        defines { "DEBUG" }
        flags   { "Symbols" }
