# GTA Map Hotkey

[![Build and release](https://github.com/yuksel-kadir/MapHotkey/actions/workflows/release.yml/badge.svg)](https://github.com/yuksel-kadir/MapHotkey/actions/workflows/release.yml)

ASI plugins that open the pause-menu map directly in the original PC releases
of GTA III, Vice City and San Andreas. Press the configured binding again to
close the map and return to the game.

- Keyboard default: `M`
- Controller default: Select/Back
- Keyboard and controller bindings are configurable through an INI file.
- All builds target the original 32-bit 1.0 executables.

## Downloads and requirements

Install the matching ASI and INI in the game's `scripts` directory. Each game
requires an ASI loader.

| Game | Files | Additional requirement |
|---|---|---|
| GTA III 1.0 | `MapHotkeyIII.asi`, `MapHotkeyIII.ini` | `MenuMapIII.asi` must be installed and loaded |
| Vice City 1.0 | `MapHotkeyVC.asi`, `MapHotkeyVC.ini` | None; Menu Map VC remains compatible and optional |
| San Andreas 1.0 US | `MapHotkeySA.asi`, `MapHotkeySA.ini` | None |

GTA III has no native functional map page. Menu Map III repurposes its unused
no-memory-card page as the map, and Map Hotkey opens that page. If Menu Map III
is not loaded, the GTA III hotkey safely does nothing.

Vice City and San Andreas use their native map pages. When Menu Map VC is
installed, it enhances the same Vice City page without requiring a direct code
dependency from this project.

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
