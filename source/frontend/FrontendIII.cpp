#ifdef GTA3

#include "frontend/GameFrontend.h"

#include <Windows.h>

#include "logging/Logger.h"
#include "CMenuManager.h"

namespace {
constexpr int kMenuMapPage = MENUPAGE_NO_MEMORY_CARD;

bool IsMenuMapLoaded() {
    return GetModuleHandleA("MenuMapIII.asi") != nullptr;
}
}

const char* GameFrontend::Name() {
    return "GTA III";
}

bool GameFrontend::IsMenuActive() {
    return FrontEndMenuManager.m_bMenuActive;
}

int GameFrontend::CurrentPage() {
    return FrontEndMenuManager.m_nCurrentMenuPage;
}

bool GameFrontend::OpenMap() {
    if (IsMenuActive() || !IsMenuMapLoaded()) {
        if (!IsMenuMapLoaded())
            Log("MenuMapIII.asi is not loaded; map hotkey ignored");
        return false;
    }

    FrontEndMenuManager.RequestFrontEndStartUp();
    FrontEndMenuManager.SwitchMenuOnAndOff();
    if (!IsMenuActive())
        return false;

    // Menu Map replaces GTA III's unused no-memory-card page with its map.
    FrontEndMenuManager.m_nPreviousMenuPage = MENUPAGE_PAUSE_MENU;
    FrontEndMenuManager.m_nCurrentMenuPage = kMenuMapPage;
    FrontEndMenuManager.m_nCurrentMenuEntry = 0;
    return true;
}

bool GameFrontend::CloseMenu() {
    if (!IsMenuActive())
        return true;

    FrontEndMenuManager.RequestFrontEndShutDown();
    FrontEndMenuManager.SwitchMenuOnAndOff();
    return !IsMenuActive();
}

#endif
