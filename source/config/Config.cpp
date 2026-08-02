#include "config/Config.h"

#include <Windows.h>

#include <cstdlib>

namespace {
Settings g_settings;
std::string g_iniPath;
std::string g_logPath;

std::string ModuleBasePath() {
    HMODULE module = nullptr;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<LPCSTR>(&ModuleBasePath),
        &module
    );

    char path[MAX_PATH]{};
    GetModuleFileNameA(module, path, MAX_PATH);

    std::string result(path);
    const auto extension = result.find_last_of('.');
    if (extension != std::string::npos)
        result.resize(extension);
    return result;
}

int ReadInteger(const char* section, const char* key, int fallback) {
    char value[32]{};
    GetPrivateProfileStringA(
        section, key, "", value, sizeof(value), g_iniPath.c_str()
    );

    if (!value[0])
        return fallback;

    char* end = nullptr;
    const long parsed = std::strtol(value, &end, 0);
    return end != value ? static_cast<int>(parsed) : fallback;
}
}

void Config::Initialize() {
    const std::string basePath = ModuleBasePath();
    g_iniPath = basePath + ".ini";
    g_logPath = basePath + ".log";

    g_settings.enabled = ReadInteger("Settings", "Enabled", 1) != 0;
    g_settings.keyboardKey = ReadInteger("Keyboard", "VirtualKey", 'M');
    g_settings.controllerEnabled =
        ReadInteger("Controller", "Enabled", 1) != 0;
    g_settings.controllerButton = static_cast<ControllerButton>(
        ReadInteger("Controller", "Button", 1)
    );
    g_settings.debugLogging = ReadInteger("Debug", "Logging", 0) != 0;
}

const Settings& Config::Get() {
    return g_settings;
}

const std::string& Config::LogPath() {
    return g_logPath;
}
