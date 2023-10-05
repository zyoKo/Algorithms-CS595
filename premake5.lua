workspace "Algorithms"
    architecture "x86_64"
    startproject "ConvexHull"

    configurations
    {
        "Debug",
        "Release"
    }

    filter "system:windows"
        systemversion "latest"
        defines "WINDOWS"

    filter "system:linux"
        systemversion "latest"
        defines "LINUX"

    sourcedir = "./src"
    vendordir = "./vendor"
    outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    include "ConvexHull"
    include "JT_Permutations"
    include "Lexical_Permutation"
    include "Knapsack_BruteForce_Min_Change"

newaction
{
    trigger = "clean",
    description = "Remove all binaries, intermediate binaries, and VS Files.",
    execute = function()
        print("Removing binaries & intermediate binaries")
        os.rmdir("./ConvexHull/build")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}