#include "plugin.h"

#include "config/Config.h"
#include "frontend/FrontendControl.h"
#include "frontend/GameFrontend.h"
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

class MapHotkey {
public:
    MapHotkey() {
        Config::Initialize();
        const Settings& settings = Config::Get();

        Log(
            "MapHotkey loaded game=%s enabled=%d key=0x%X controller=%d button=%d",
            GameFrontend::Name(),
            settings.enabled,
            settings.keyboardKey,
            settings.controllerEnabled,
            static_cast<int>(settings.controllerButton)
        );

        Events::gameProcessEvent += ProcessGame;
    }
} g_mapHotkey;
