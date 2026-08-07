# MapHotkey

[![Build and release](https://github.com/yuksel-kadir/MapHotkey/actions/workflows/release.yml/badge.svg)](https://github.com/yuksel-kadir/MapHotkey/actions/workflows/release.yml)

Configurable ASI plugins that open and close the pause-menu map with one hotkey
in the original PC releases of GTA III, Grand Theft Auto: Vice City, and Grand
Theft Auto: San Andreas.

- Keyboard default: `M`
- Controller default: Select/Back
- Press the same binding again to close the map and return to the game.
- Keyboard and controller bindings are configurable through each game's INI.
- All builds target the original 32-bit 1.0 PC executables.

## Supported games

Download the ZIP for your game from the [latest release](https://github.com/yuksel-kadir/MapHotkey/releases/latest),
then extract its ASI and INI files into the game's `scripts` directory. Every
game requires an ASI loader.

| Game | Files | Additional requirement |
|---|---|---|
| GTA III 1.0 | `MapHotkeyIII.asi`, `MapHotkeyIII.ini` | [Menu Map III](https://github.com/gennariarmando/menu-map) must be installed and loaded |
| Vice City 1.0 | `MapHotkeyVC.asi`, `MapHotkeyVC.ini` | None; Menu Map VC is compatible and optional |
| San Andreas 1.0 US | `MapHotkeySA.asi`, `MapHotkeySA.ini` | None |

GTA III has no native functional map page. Menu Map III repurposes its unused
no-memory-card page as the map, and Map Hotkey opens that page. If Menu Map III
is not loaded, the GTA III hotkey safely does nothing.

Vice City and San Andreas use their native map pages. When Menu Map VC is
installed, it enhances the same Vice City page without requiring a direct code
dependency from this project.

Steam, Rockstar Games Launcher, and Definitive Edition executables are not
supported.

## Configuration

Edit the INI matching your game to enable or disable the mod, change the
keyboard virtual-key code, choose the controller button, enable controller
input, or turn on diagnostic logging. The supplied defaults use `M` and
Select/Back.

## Source layout

```text
source/
|-- Main.cpp                 Plugin initialization and frame coordination
|-- config/                  INI settings and module-relative paths
|-- frontend/                Shared control plus III, VC and SA adapters
|-- input/                   Keyboard and controller edge detection
`-- logging/                 Optional diagnostic logging
```

## Build

Set `PLUGIN_SDK_DIR` to a compatible Plugin SDK checkout, generate the VS2022
solution with Premake, and build one or more `Win32` configurations:

```text
ReleaseIII  -> output/asi/MapHotkeyIII.asi
ReleaseVC   -> output/asi/MapHotkeyVC.asi
ReleaseSA   -> output/asi/MapHotkeySA.asi
```

The current upstream Plugin SDK has a stale VC offset assertion in
`plugin_vc/game_vc/CRunningScript.h`: it validates `m_bAwake`, although the
field is named `m_bSkipWakeTime`. The automated build applies that one-line
compatibility correction before compiling `Plugin_VC.lib`.

## Automated releases

Pull requests build and package all three variants. Pushing a tag whose name
starts with `v` publishes three independent downloads so users only need the
archive for their game:

```text
MapHotkeyIII.zip
MapHotkeyVC.zip
MapHotkeySA.zip
```

To create a release:

```powershell
git tag v1.1.0
git push origin v1.1.0
```

Manual workflow runs upload the three ZIPs as separate Actions artifacts
without creating a GitHub Release.
