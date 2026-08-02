# Map Hotkey SA

GTA San Andreas 1.0 US ASI plugin that opens the native pause-menu map directly.
Press the configured binding again to close the menu and return to the game.

- Keyboard default: `M`
- Controller default: Select/Back
- Both bindings and the mod itself are configurable in `MapHotkeySA.ini`.

Copy `MapHotkeySA.asi` and `MapHotkeySA.ini` to the game's `scripts` directory.
The game needs an ASI loader. This build targets the original 32-bit 1.0 US
executable (`PLUGIN_SGV_10US`), not Steam or the Definitive Edition.

## Source layout

```text
source/
|-- Main.cpp                 Plugin initialization and frame coordination
|-- config/                  INI settings and module-relative paths
|-- frontend/                Native SA frontend map open/close behavior
|-- input/                   Keyboard and controller edge detection
`-- logging/                 Optional diagnostic logging
```

## Build

Generate the VS2022 solution with Premake, then build `ReleaseSA|Win32` against
the workspace Plugin SDK. The output is `output/asi/MapHotkeySA.asi`.
