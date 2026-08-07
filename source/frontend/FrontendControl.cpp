#include "frontend/FrontendControl.h"

#include "frontend/GameFrontend.h"
#include "logging/Logger.h"

namespace {
bool g_mapOpenedByHotkey = false;
}

bool FrontendControl::IsMenuActive() {
    return GameFrontend::IsMenuActive();
}

void FrontendControl::RefreshOwnership() {
    if (!IsMenuActive())
        g_mapOpenedByHotkey = false;
}

void FrontendControl::OpenMap() {
    if (!GameFrontend::OpenMap())
        return;

    g_mapOpenedByHotkey = true;
    Log("map opened page=%d", GameFrontend::CurrentPage());
}

void FrontendControl::CloseMap() {
    if (!IsMenuActive() || !g_mapOpenedByHotkey)
        return;

    if (!GameFrontend::CloseMenu()) {
        Log("map close rejected page=%d", GameFrontend::CurrentPage());
        return;
    }

    g_mapOpenedByHotkey = false;
    Log("map closed");
}
