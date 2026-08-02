#include "input/HotkeyInput.h"

#include <Windows.h>

#include "config/Config.h"
#include "logging/Logger.h"
#include "CMenuManager.h"
#include "CPad.h"

namespace {
constexpr unsigned int kControllerDebounceFrames = 10;

short GetButtonValue(const CControllerState& state, ControllerButton button) {
    switch (button) {
    case ControllerButton::Select:         return state.Select;
    case ControllerButton::Start:          return state.Start;
    case ControllerButton::DPadUp:         return state.DPadUp;
    case ControllerButton::DPadDown:       return state.DPadDown;
    case ControllerButton::DPadLeft:       return state.DPadLeft;
    case ControllerButton::DPadRight:      return state.DPadRight;
    case ControllerButton::Cross:          return state.ButtonCross;
    case ControllerButton::Circle:         return state.ButtonCircle;
    case ControllerButton::Square:         return state.ButtonSquare;
    case ControllerButton::Triangle:       return state.ButtonTriangle;
    case ControllerButton::LeftShoulder1:  return state.LeftShoulder1;
    case ControllerButton::RightShoulder1: return state.RightShoulder1;
    case ControllerButton::LeftShoulder2:  return state.LeftShoulder2;
    case ControllerButton::RightShoulder2: return state.RightShoulder2;
    case ControllerButton::LeftStick:      return state.ShockButtonL;
    case ControllerButton::RightStick:     return state.ShockButtonR;
    default:                               return 0;
    }
}
}

bool HotkeyInput::JustPressed() {
    const bool keyboardPressed = PollKeyboard();
    const bool controllerPressed = PollController();

    if (keyboardPressed || controllerPressed) {
        Log(
            "hotkey pressed keyboard=%d controller=%d active=%d page=%d",
            keyboardPressed,
            controllerPressed,
            FrontEndMenuManager.m_bMenuActive,
            static_cast<int>(FrontEndMenuManager.m_nCurrentMenuPage)
        );
    }

    return keyboardPressed || controllerPressed;
}

bool HotkeyInput::PollKeyboard() {
    const int key = Config::Get().keyboardKey;
    const bool down = key > 0 && (GetAsyncKeyState(key) & 0x8000) != 0;
    const bool pressed = down && !m_keyboardWasDown;
    m_keyboardWasDown = down;
    return pressed;
}

bool HotkeyInput::PollController() {
    const Settings& settings = Config::Get();
    CPad* pad = CPad::GetPad(0);
    const bool down = settings.controllerEnabled && pad &&
        GetButtonValue(pad->NewState, settings.controllerButton) != 0;

    bool pressed = false;
    if (m_controllerDebounceFrames > 0)
        --m_controllerDebounceFrames;
    else
        pressed = down && !m_controllerWasDown;

    m_controllerWasDown = down;
    if (pressed)
        m_controllerDebounceFrames = kControllerDebounceFrames;
    return pressed;
}
