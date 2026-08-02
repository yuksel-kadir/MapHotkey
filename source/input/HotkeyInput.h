#pragma once

// Maintains keyboard/controller edges independently of game pause state.

class HotkeyInput {
public:
    bool JustPressed();

private:
    bool PollKeyboard();
    bool PollController();

    bool m_keyboardWasDown = false;
    bool m_controllerWasDown = false;
    unsigned int m_controllerDebounceFrames = 0;
};
