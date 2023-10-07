[![Latest version](https://img.shields.io/badge/latest-v0.4--dev-red.svg)](https://img.shields.io/badge/latest-v0.4--dev-red.svg) [![Build status](https://ci.appveyor.com/api/projects/status/v043naykgplkj42s?svg=true)](https://ci.appveyor.com/project/BearishSun/bansheeengine) [![Discord](https://img.shields.io/discord/572359664528916490.svg?logo=discord)](https://discord.gg/8Xyf5gF)

# Preserving Banshee3D...
This repository is a fork of the latest public release from Banshee 3D, which was removed from the original author.

#### Changes
Integrated bsf, bsf examples and made the project compilable.

#### HowTo
- Clone the repository: git clone <url> <target>
- Open the Folder with Visual Studio 2022 17.7 or later
- Wait for CMake to prepare the project
- Switch to CMake Targets View
- Select startup project: Banshee3D.exe
- Press the play button and enjoy

#### Note
Every change from now (2023-08-15) is licensed under the MIT license, expect the original source files that are under the LGPL 3.0.

My main goal is to preserve this project, nothing more, so there could be some minor bugfixes around the build system.

# Disclaimer
"I would like to emphasize that this fork is not intended for commercial use and will adhere to the terms of the original GPL3 license agreement. My aim is solely to preserve the original work for educational and research purposes."

### Why have you crated this issue?

I was unsure about any legal consequences so I made some research, after a odyssee on the internet I found the last statements from the original author on his discord channel. After reading everything carefully I didn't find any sign which would point to a real reason why the project was switched private, only something wage, which doesn't made sense.

So I decided to switch my fork public and made it buildable again. I like it a lot and I think it should be preserved. I am not the original copyright holder, neither I want to have any to do with it. I am only a "preserver" nothing more, nothing less.

##### Details

The original author said that he had to switch his original repository private due to legal reasons, but never stated why, he also wrote that we can use existing forks. The project itself is under GPL3, also there are more people who contributed to it.

Original Statement:
<img width="1527" alt="image" src="https://github.com/larioteo/BansheeEngine/assets/12191559/e1d6552f-63a8-43ec-985b-99597354273e">

Also he stated around two years later that he will not continue the project in its current state:
<img width="1466" alt="image" src="https://github.com/larioteo/BansheeEngine/assets/12191559/4cc8759a-e70e-4c8e-813c-a8913ccedb42">

So as you see the original author said we should use existing forks, never wrote anything against it.

# What was Banshee? 
Banshee was a high-quality and modern game development toolkit. It provides a **high-performance, multi-threaded game engine** written in C++14. The engine includes math and utility libraries, Vulkan, DirectX 11 and OpenGL support, handles common tasks such as input, GUI, physics, audio, animation and scripting, and supports many popular resource formats (e.g. FBX, PNG, PSD, TTF, OGG, WAV).

Banshee provides an intuitive and customizable **editor** that can be used to manage assets, build levels, compile scripts, and to test and publish your game. The editor can be extended or customized with scripts to meet the exact needs of your project.

Banshee's **C# scripting** system comes with an extensive API that ensures development can be completed without ever needing to touch the engine's C++ core. C# scripting simplifies development by providing access to the entire .NET library, plus a wide variety of other managed libraries. The scripting system is fully integrated with the Banshee editor and external tools, such as Visual Studio. Fast compilation ensures iteration times between scripting and testing are minimized.

Banshee can also be used as a **low-level framework**, or as a powerful foundation to build new technologies upon. The engine can be easily customized for any game-specific needs. It uses a layered, plugin-based design that allows its functionality and systems to be upgraded, removed, or replaced as required. Banshee's code is modern, uses clean interfaces, and is easy to learn and maintain. Platform-specific functionality is kept at a minimum to make porting as easy as possible. It is fully documented with an extensive API reference. Introductory manuals are supplied for most major systems.

**WARNING: Banshee is still in development and should not be used in production.**

# Features
* [Core features](https://github.com/OmniVortexStudios/BansheeEngine/blob/master/Source/bsf/Documentation/GitHub/features.md) - A list of all core engine features.
* [Editor features](https://github.com/OmniVortexStudios/BansheeEngine/blob/master/Documentation/GitHub/features.md) - A list of all editor specific features.
* [Roadmap](https://github.com/OmniVortexStudios/BansheeEngine/blob/master/Source/bsf/Documentation/GitHub/roadmap.md) - A list of features to be implemented in both near and far future. 

# Download
* [Binaries](https://github.com/OmniVortexStudios/BansheeEngine/blob/master/Documentation/GitHub/install.md) - Download pre-built binaries for the most recent version.
* [Compiling](https://github.com/OmniVortexStudios/BansheeEngine/blob/master/Documentation/GitHub/compiling.md) - Learn how to compile the engine yourself.

# Documentation
* [Documentation](http://docs.banshee3d.com/Managed/index.html) - Documentation for the scripting (C#) API.

# About
* [License](https://github.com/OmniVortexStudios/BansheeEngine/blob/master/Documentation/GitHub/license.md) - Information about Banshee's license.
* [Contribute](http://www.banshee3d.com/contribute) - Help out with the development

# Media
**Banshee Editor**
![Banshee Editor](http://bearishsun.thalassa.feralhosting.com/BansheeEditor.png "Banshee Editor")

[**Video overview**](https://youtu.be/WJsYOyCXGEU)
