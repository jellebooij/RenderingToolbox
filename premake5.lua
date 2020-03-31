workspace "RenderBox"
    architecture "x86"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }

    buildoptions "/MD"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "RenderBox"
    location "RenderBox"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/".. outputdir .. "/%{prj.name}")
    objdir ("bin-int/".. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src/vendor/spdlog",
        "%{prj.name}/include",
        "%{prj.name}/src/Vendor",
        "%{prj.name}/src"
    }

    libdirs 
    { 
        "%{prj.name}/lib" 
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"
    
        defines
        {
            "PLATFORM_WINDOWS",
            "BUILD_DLL",
            "GLEW_STATIC",
            "_MBCS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
        }

        links 
        {
            "glfw3.lib",
            "opengl32.lib",
            "glew32s.lib"
        }

    filter "configurations:Debug" 
        symbols "On"
        runtime "Debug"
        staticruntime "off"



     
    
project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "RenderBox/src",
        "RenderBox/src/Vendor",
        "RenderBox/include",
    }
    
    links
    {
        "RenderBox"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "PLATFORM_WINDOWS"
        }
    
        filter "configurations:Debug"
        symbols "On"
    
        filter "configurations:Release"
        optimize "On"
    
        filter "configurations:Dist"
        optimize "On"