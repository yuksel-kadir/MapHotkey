#include "frontend/FrontendControl.h"

#include "logging/Logger.h"
#include "CMenuManager.h"
#include "CPad.h"

namespace {
constexpr short kPressedState = 255;
bool g_mapOpenedByHotkey = false;

class ScopedEscapePress {
public:
    explicit ScopedEscapePress(CPad& pad)
        : m_pad(pad),
          m_savedNewState(pad.NewKeyState.esc),
          m_savedOldState(pad.OldKeyState.esc) {
        m_pad.NewKeyState.esc = kPressedState;
        m_pad.OldKeyState.esc = 0;
    }

    ~ScopedEscapePress() {
        m_pad.NewKeyState.esc = m_savedNewState;
        m_pad.OldKeyState.esc = m_savedOldState;
    }

private:
    CPad& m_pad;
    short m_savedNewState;
    short m_savedOldState;
};

void InvokeNativeMenuToggle() {
    CPad* pad = CPad::GetPad(0);
    if (!pad)
        return;

    const ScopedEscapePress escapePress(*pad);
    FrontEndMenuManager.SwitchMenuOnAndOff();
}
}

bool FrontendControl::IsMenuActive() {
    return FrontEndMenuManager.m_bMenuActive;
}

void FrontendControl::RefreshOwnership() {
    if (!IsMenuActive())
        g_mapOpenedByHotkey = false;
}

void FrontendControl::OpenMap() {
    if (IsMenuActive())
        return;

    InvokeNativeMenuToggle();
    if (!IsMenuActive())
        return;

    FrontEndMenuManager.SwitchToNewScreen(MENUPAGE_MAP);
    g_mapOpenedByHotkey = true;
    Log("map opened page=%d", FrontEndMenuManager.m_nCurrentMenuPage);
}

void FrontendControl::CloseMap() {
    if (!IsMenuActive() || !g_mapOpenedByHotkey)
        return;

    const char previousPage = FrontEndMenuManager.m_nCurrentMenuPage;

    // SA 1.0 refuses an ESC close directly from its map. Routing through the
    // pause page lets the native shutdown restore every frontend subsystem.
    if (previousPage == MENUPAGE_MAP)
        FrontEndMenuManager.m_nCurrentMenuPage = MENUPAGE_PAUSE_MENU;

    InvokeNativeMenuToggle();

    if (IsMenuActive()) {
        FrontEndMenuManager.m_nCurrentMenuPage = previousPage;
        Log("map close rejected page=%d", previousPage);
        return;
    }

    g_mapOpenedByHotkey = false;
    Log("map closed");
}
