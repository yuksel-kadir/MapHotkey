#pragma once

// Owns interaction with GTA SA's native pause-menu frontend.

namespace FrontendControl {
bool IsMenuActive();
void RefreshOwnership();
void OpenMap();
void CloseMap();
}
