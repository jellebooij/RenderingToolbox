workspace "RenderBox"
    architecture "x86_64"

    configutations{
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-"

project "RenderBox"
    location "RenderBox"
    kind "WindowedApp"
    language "C++"

    targetdir("bin/".. outputdir .. "/%{prj.name}")
    objdir("bin-int/".. outputdir .. "/%{prj.name}")

    files{

        "%{prj.name}/src/**.h"
        "%{prj.name}/src/**.cpp"

    }

    include{
        "%{prj.name}/src/vendor/spdlog"
        "%{prj.name}/include"
    }

    filer "system::windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
    
        defines{
            "GLEW_STATIC"
        }

        links {
            "glfw3"
            "opengl32"
            "glew32s"
        }
    
