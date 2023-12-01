project "Dynamic_Knapsack"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
    staticruntime "on"

    targetdir("./build/bin/" .. outputdir .. "/%{prj.name}")
    objdir("./build/obj/" .. outputdir .. "/%{prj.name}")

    files 
    {
        sourcedir .. "/**.cpp",
        sourcedir .. "/**.h"
    }

    includedirs 
    {
        sourcedir
    }

    filter { "configurations:Debug" }
        buildoptions "/MTd"
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        buildoptions "/MT"
        runtime "Release"
        optimize "on"