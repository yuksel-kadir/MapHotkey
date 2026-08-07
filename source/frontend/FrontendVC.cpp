#ifdef GTAVC

#include "frontend/GameFrontend.h"

#include "CMenuManager.h"

const char* GameFrontend::Name() {
    return "Vice City";
}

bool GameFrontend::IsMenuActive() {
    return FrontEndMenuManager.m_bMenuActive;
}

int GameFrontend::CurrentPage() {
    return FrontEndMenuManager.m_nCurrentMenuPage;
}

bool GameFrontend::OpenMap() {
    if (IsMenuActive())
        return false;

    FrontEndMenuManager.RequestFrontEndStartUp();
    FrontEndMenuManager.SwitchMenuOnAndOff();
    if (!IsMenuActive())
        return false;

    FrontEndMenuManager.SwitchToNewScreen(MENUPAGE_MAP);
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
