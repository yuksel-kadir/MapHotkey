#pragma once

// Module-relative paths and INI-backed settings.

#include <string>

enum class ControllerButton : int {
    None = 0,
    Select,
    Start,
    DPadUp,
    DPadDown,
    DPadLeft,
    DPadRight,
    Cross,
    Circle,
    Square,
    Triangle,
    LeftShoulder1,
    RightShoulder1,
    LeftShoulder2,
    RightShoulder2,
    LeftStick,
    RightStick,
};

struct Settings {
    bool enabled = true;
    int keyboardKey = 'M';
    bool controllerEnabled = true;
    ControllerButton controllerButton = ControllerButton::Select;
    bool debugLogging = false;
};

namespace Config {
void Initialize();
const Settings& Get();
const std::string& LogPath();
}
