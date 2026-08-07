workspace "map-hotkey"
    configurations {
        "ReleaseIII", "DebugIII",
        "ReleaseVC", "DebugVC",
        "ReleaseSA", "DebugSA"
    }
    location "project_files"

project "map-hotkey"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    architecture "x86"
    targetdir "output/asi"
    objdir "output/obj/%{cfg.buildcfg}"
    targetextension ".asi"
    characterset "MBCS"

    files { "source/**.cpp", "source/**.h" }

    includedirs {
        "source",
        "$(PLUGIN_SDK_DIR)/shared",
        "$(PLUGIN_SDK_DIR)/shared/game"
    }

    libdirs { "$(PLUGIN_SDK_DIR)/output/lib" }
    defines { "_CRT_SECURE_NO_WARNINGS", "_CRT_NON_CONFORMING_SWPRINTFS", "RW" }
    buildoptions { "/permissive", "/Zc:threadSafeInit-" }
    linkoptions { "/SAFESEH:NO" }
    staticruntime "on"

    filter "configurations:*III"
        defines { "GTA3", "PLUGIN_SGV_10EN" }
        includedirs {
            "$(PLUGIN_SDK_DIR)/plugin_III",
            "$(PLUGIN_SDK_DIR)/plugin_III/game_III",
            "$(PLUGIN_SDK_DIR)/plugin_III/game_III/enums",
            "$(PLUGIN_SDK_DIR)/plugin_III/game_III/rw"
        }
        targetname "MapHotkeyIII"

    filter "configurations:*VC"
        defines { "GTAVC", "PLUGIN_SGV_10EN" }
        includedirs {
            "$(PLUGIN_SDK_DIR)/plugin_vc",
            "$(PLUGIN_SDK_DIR)/plugin_vc/game_vc",
            "$(PLUGIN_SDK_DIR)/plugin_vc/game_vc/enums",
            "$(PLUGIN_SDK_DIR)/plugin_vc/game_vc/rw"
        }
        targetname "MapHotkeyVC"

    filter "configurations:*SA"
        defines { "GTASA", "PLUGIN_SGV_10US" }
        includedirs {
            "$(PLUGIN_SDK_DIR)/plugin_sa",
            "$(PLUGIN_SDK_DIR)/plugin_sa/game_sa",
            "$(PLUGIN_SDK_DIR)/plugin_sa/game_sa/enums",
            "$(PLUGIN_SDK_DIR)/plugin_sa/game_sa/rw"
        }
        targetname "MapHotkeySA"

    filter "configurations:Release*"
        defines { "NDEBUG" }
        optimize "On"
        symbols "off"

    filter "configurations:Debug*"
        defines { "DEBUG" }
        optimize "Off"
        symbols "on"

    filter "configurations:ReleaseIII"
        links { "plugin_iii" }
    filter "configurations:DebugIII"
        links { "plugin_iii_d" }
    filter "configurations:ReleaseVC"
        links { "plugin_vc" }
    filter "configurations:DebugVC"
        links { "plugin_vc_d" }
    filter "configurations:ReleaseSA"
        links { "plugin" }
    filter "configurations:DebugSA"
        links { "plugin_d" }

    filter {}
