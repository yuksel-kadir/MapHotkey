workspace "map-hotkey"
    configurations { "ReleaseSA", "DebugSA" }
    location "project_files"

project "map-hotkey"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    architecture "x86"
    targetdir "output/asi"
    objdir "output/obj/%{cfg.buildcfg}"
    targetname "MapHotkeySA"
    targetextension ".asi"
    characterset "MBCS"

    files { "source/**.cpp", "source/**.h" }

    includedirs {
        "source",
        "$(PLUGIN_SDK_DIR)/shared",
        "$(PLUGIN_SDK_DIR)/shared/game",
        "$(PLUGIN_SDK_DIR)/plugin_sa",
        "$(PLUGIN_SDK_DIR)/plugin_sa/game_sa",
        "$(PLUGIN_SDK_DIR)/plugin_sa/game_sa/enums",
        "$(PLUGIN_SDK_DIR)/plugin_sa/game_sa/rw"
    }

    libdirs { "$(PLUGIN_SDK_DIR)/output/lib" }
    defines { "_CRT_SECURE_NO_WARNINGS", "_CRT_NON_CONFORMING_SWPRINTFS", "RW", "GTASA", "PLUGIN_SGV_10US" }
    buildoptions { "/permissive", "/Zc:threadSafeInit-" }
    linkoptions { "/SAFESEH:NO" }
    staticruntime "on"

    filter "configurations:ReleaseSA"
        defines { "NDEBUG" }
        optimize "On"
        symbols "off"
        links { "plugin" }

    filter "configurations:DebugSA"
        defines { "DEBUG" }
        optimize "Off"
        symbols "on"
        links { "plugin_d" }

    filter {}
