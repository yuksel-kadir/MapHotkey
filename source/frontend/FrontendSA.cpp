#ifdef GTASA

#include "frontend/GameFrontend.h"

#include "CMenuManager.h"
#include "CPad.h"

namespace {
constexpr short kPressedState = 255;

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

const char* GameFrontend::Name() {
    return "San Andreas";
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

    InvokeNativeMenuToggle();
    if (!IsMenuActive())
        return false;

    FrontEndMenuManager.SwitchToNewScreen(MENUPAGE_MAP);
    return true;
}

bool GameFrontend::CloseMenu() {
    if (!IsMenuActive())
        return true;

    const char previousPage = FrontEndMenuManager.m_nCurrentMenuPage;
    if (previousPage == MENUPAGE_MAP)
        FrontEndMenuManager.m_nCurrentMenuPage = MENUPAGE_PAUSE_MENU;

    InvokeNativeMenuToggle();
    if (!IsMenuActive())
        return true;

    FrontEndMenuManager.m_nCurrentMenuPage = previousPage;
    return false;
}

#endif
