# Baka Framework

A small plugin that exposes some new data to other mods, and fixes a few bugs.

- [Nexus](https://www.nexusmods.com/fallout4/mods/43627)
- [VR](https://www.nexusmods.com/fallout4/mods/85713)

## Requirements

- Any terminal of your choice (e.g., PowerShell)
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [CMake](https://cmake.org/)
  - Edit the `PATH` environment variable and add the cmake.exe install path as a new value
  - Instructions for finding and editing the `PATH` environment variable can be found [here](https://www.java.com/en/download/help/path.html)
- [Git](https://git-scm.com/downloads)
  - Edit the `PATH` environment variable and add the Git.exe install path as a new value
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Install vcpkg using the directions in vcpkg's [Quick Start Guide](https://github.com/microsoft/vcpkg#quick-start-windows)
  - After install, add a new environment variable named `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
- [Steamworkds SDK](https://partner.steamgames.com/downloads/list)
  - Currently need Version 1.60. Other versions require changing [x64-windows-baka-steam.cmake](/Plugin/cmake/triplets/x64-windows-baka-steam.cmake)
  - Environment variable `STEAMWORKS_SDK` pointing to root directory where Steamworks SDK installed. For example, if in `C:\steamworks_sdk_160`, the value should be `C:\`. PS command:

```ps
   $env:STEAMWORKS_SDK = 'C:\
```

## User Requirements

- [Address Library for F4SE](https://www.nexusmods.com/fallout4/mods/47327)
  - Needed for SSE/AE
- [VR Address Library for F4SEVR](https://www.nexusmods.com/fallout4/mods/64879)
  - Needed for VR

## Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

## Clone and Build

Open terminal (e.g., PowerShell) and run the following commands:

```ps
git clone https://github.com/alandtse/BakaFramework --recursive
cd BakaFramework
.\update-submodule.bat
.\make-sln-msvc.bat
.\build-msvc.bat
```

## License

[GPL-3.0-or-later](COPYING) WITH [Modding Exception AND GPL-3.0 Linking Exception (with Corresponding Source)](EXCEPTIONS).  
Specifically, the Modded Code is Fallout 4 (and its variants) and Modding Libraries include [F4SE/VR](https://f4se.silverlock.org/), [CommonlibF4](https://github.com/alandtse/CommonLibF4) (and variants), and [DKUtil](https://github.com/gottyduke/DKUtil).

## Credits

Forked from https://github.com/shad0wshayd3-FO4/BakaFramework
