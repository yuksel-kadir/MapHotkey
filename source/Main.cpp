#include "plugin.h"

#include "config/Config.h"
#include "frontend/FrontendControl.h"
#include "input/HotkeyInput.h"
#include "logging/Logger.h"

using namespace plugin;

namespace {
HotkeyInput g_hotkey;

void ProcessGame() {
    FrontendControl::RefreshOwnership();

    if (!Config::Get().enabled || !g_hotkey.JustPressed())
        return;

    if (FrontendControl::IsMenuActive())
        FrontendControl::CloseMap();
    else
        FrontendControl::OpenMap();
}
}

class MapHotkeySA {
public:
    MapHotkeySA() {
        Config::Initialize();
        const Settings& settings = Config::Get();

        Log(
            "MapHotkeySA loaded enabled=%d key=0x%X controller=%d button=%d",
            settings.enabled,
            settings.keyboardKey,
            settings.controllerEnabled,
            static_cast<int>(settings.controllerButton)
        );

        Events::gameProcessEvent += ProcessGame;
    }
} g_mapHotkeySA;
