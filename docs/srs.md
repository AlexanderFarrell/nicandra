# Software Requirement Specification

## Executive Summary

Nicandra Engine lets you build native apps and games, with tons of helpful building blocks built in. It unifies 
application and game development to provide the benefits of both: graphics, simulation, and user interface
power.

Nicandra Engine is named after a mysterious plant with nice purple flowers and lantern like structures 
protecting their berries (don't eat them). [It's sometimes a weed](https://en.wikipedia.org/wiki/Nicandra_physalodes#/media/File:Nicandra_physalodes_plant.jpg), able to grow in a wide variety of conditions,
and yet still produce beautiful flowers. I'd like this engine to similarly run on various platforms, be resilient,
be efficient, and allow apps and games to bloom.

## Purpose

When you think of building apps and games... it can get
complicated. There's tons and tons of different tools, 
frameworks, many requiring large amounts of scaffolding.

I just want a nice tool to make fun games, or nice
desktop applications quickly and simply. 

## General Feature Inventory

This is an outline of features needed by the engine, followed by a priority:

- P1 - Necessary
- P2 - Should do
- P3 - Could do
- P4 - Least important

- 1. Games 
    - 1.1 Rendering
        - 1.1.1 Particles - P2
        - 1.1.2 Textures - P1
        - 1.1.3 Meshes - P1
        - 1.1.4 Materials and Shaders - P1
        - 1.1.5 Drawables - P1
        - 1.1.6 Post-processing - P2
        - 1.1.7 Terrain - P1
        - 1.1.8 Shadows - P2
        - 1.1.9 Forward Lighting - P1
        - 1.1.10 Skybox - P1
        - 1.1.11 Hardware Instancing - P2
        - 1.1.12 Cameras - P1
        - 1.1.13 LOD - P2
    - 1.2 3D
        - 1.2.1 Terrain
            - 1.2.1.1 Heightmap Terrain - P1
            - 1.2.1.1 Voxel Terrain - P3
        - 1.2.2 Buildings (maybe move to procedural, but also has rendering & physics component) - P1
            - 1.2.2.1 Walls, Floors, Ceilings and Roofs - P1
            - 1.2.2.2 Roads and Paths - P1
        - 1.2.4 Skybox - P1
        - 1.2.5 Water - P1
        - 1.2.6 Rain, Snow, Sun, etc. - P2
        - 1.2.7 Characters
            - 1.2.7.1 6DOF Character - P2
            - 1.2.7.2 First Person & Third Person Walk - P1
            - 1.2.7.3 Orbit View - P1
            - 1.2.7.4 Vehicle Movement - P3
        - 1.2.8 Open World Engine - P1
    - 1.3 2D
        - 1.3.1 Sprites - P1
        - 1.3.2 Tilemap - P1
        - 1.3.3 Backgrounds (with parallax) - P2
        - 1.3.4 Non-Realtime Vector
    - 1.4 Physics
        - 1.4.1 3D Physics
        - 1.4.2 2D Physics
        - 1.4.3 Ensure frustum, ray and sphere sampling
        - 1.4.4 Ensure pathfinding
    - 1.5 Audio
        - 1.5.1 Sound effects - P1
        - 1.5.2 Music - P1
        - 1.5.3 3D Sounds - P2
        - 1.5.4 Filters like Reverb - P3
        - 1.5.5 MIDI - P2
    - 1.6 World
        - 1.6.1 Entity System - P1
        - 1.6.2 Verb System - P1
            - 1.6.2.1 Verb Runners - P1
            - 1.6.2.2 Events - P1
        - 1.6.3 Multiplayer sync - P3
        - 1.6.4 Serialization and Deserializaton - P1
    - 1.7 Gameplay
        - 1.7.1 Inventory - P2
        - 1.7.2 NPC Dialog or Shared Scripting System - P3
    - 1.8 Procedural
        - 1.8.1 Image & Array2D Filters - P1
            - 1.8.1.1 Blur
            - 1.8.1.2 Voronoi
            - 1.8.1.3 Colors
        - 1.8.2 Plants
        - 1.8.3 Creatures
        - 1.8.4 Interiors
        - 1.8.5 Video effects
    - 1.9 Networking
        - 1.9.1 Multiplayer Support
    - 1.10 Multi-window
    - 1.11 Input and Output
        - 1.11.1 Keyboard and Mouse
        - 1.11.2 Joystick
        - 1.11.3 Controller
        - 1.11.4 Haptics
        - 1.11.5 Touch
        - 1.11.6 Accessibility Devices
        - 1.11.7 Pen
        - 1.11.8 Microphone
        - 1.11.9 Camera
        - 1.11.10 Screenshots and Recording
    - 1.12 Assets
        - 1.12.1 File support (import and export)
            - 1.12.1.1 Image formats
            - 1.12.1.2 Audio formats
            - 1.12.1.3 Asset manager
                - 1.12.3.1 Virtual Filesystem (Local, SFTP, Cloud)
            - 1.12.1.4 Data formats (YAML, JSON, CSV, TOML, XML)
        - 1.12.2 Types: Texture, Material, World, Sound, Data
        - 1.12.3 Asset Hashing and Access
    - 1.13 Math
        - 1.13.1 Linear Algebra (use a library)
        - 1.13.2 Coordinates
        - 1.13.3 Statistics
        - 1.13.4 Random
- 2. Applications
    - 2.1. User Interface
        - 2.1.1 Retained UI 
        - 2.1.2 Common Views
            - 2.1.2.1 Buttons
            - 2.1.2.2 Labels
            - 2.1.2.3 Scroll View
            - 2.1.2.4 Input
                - 2.1.2.4.1 Text Input Basic
                - 2.1.2.4.2 Number Input 
                - 2.1.2.4.3 Checkbox Input 
                - 2.1.2.4.4 Toggle Input 
                - 2.1.2.4.5 Radio Input 
                - 2.1.2.4.6 Dropdown Input 
                - 2.1.2.4.7 Color Input 
                - 2.1.2.4.8 Date Input 
                - 2.1.2.4.9 Time Input 
                - 2.1.2.4.10 File Input 
                - 2.1.2.4.11 Password Input 
                - 2.1.2.4.12 Range Input 
                - 2.1.2.4.13 Week Input 
            - 2.1.2.5 Rich Text Editor
            - 2.1.2.6 Code Editor
            - 2.1.2.6 Layout Views
                - 2.1.2.6.1 Margin
                - 2.1.2.6.1 Table Layout (rows and columns)
            - 2.1.2.7 Native Web Browser Embedding
                - 2.1.2.7.1 WITH SECURITY
        - 2.1.3 Text
            - 2.1.3.1 Basic Styling
                - 2.1.3.1.1 Font
                - 2.1.3.1.1 Font Weight
                - 2.1.3.1.1 Italic 
                - 2.1.3.1.1 Underline 
                - 2.1.3.1.1 Font Size 
                - 2.1.3.1.1 Line Height
                - 2.1.3.1.1 Paragraph Indent
        - 2.1.4 Virtualization (handling tons of elements)
        - 2.1.5 Docking, Tabs, Multi-Pane
        - 2.1.6 Theming & Styling
        - 2.1.7 Drag & Drop
        - 2.1.8 Keyboard Shortcuts and Commands
    - 2.2 Tools
        - 2.2.1 GPU Compute
        - 2.2.2 Document Model
            - 2.2.2.1 Undo and Redo Command System
            - 2.2.2.2 
        - 2.2.3 Lua Embedding
        - 2.2.5 Video playback
            - 2.2.5.1 Video encoders
        - 2.2.6 Developer
            - 2.2.6.1 SDKs
                - 2.2.6.1.1 C++, C, Python, Node.js
            - 2.2.6.2 Console for Commands
            - 2.2.6.3 Templates
            - 2.2.6.4 Asset Manager
            - 2.2.6.5 Hot Reload

- 3. Fitness (how we measure quality)
    - 3.1 Modularity
        - 3.1.1 Nicandra must be broken up into multiple libraries
        - 3.1.2 Nicandra must layer its libraries from low level to high level.
        - 3.1.3 Nicandra must use interfaces for various capabilities, some of which may not be available on some platforms.
    - 3.2 Performance
        - 3.2.1 Nicandra must promote good performance (30 to 60 FPS) on moderate hardware
        - 3.2.2 Nicandra must be very CPU efficient for desktop apps
    - 3.3 Integrity
        - 3.3.1 Nicandra must save documents atomicly, not corrupting existing saves.
        - 3.3.2 Nicandra must support auto-save.
        - 3.3.3 Nicandra must version file documents.
        - 3.3.4 Nicandra must handle dependencies which may not exist.
    - 3.4 Security 
        - 3.4.1 Nicandra must label assets as trusted or not trusted (documents, fonts, shaders, email HTML, etc.)
        - 3.4.2 Nicandra must store secrets in platform credential stores.
    - 3.5 Accessibility - P2 (TODO)
    - 3.6 Testing
        - 3.6.1 Nicandra must support headless testing, rendering images as output if needed.
        - 3.6.2 Nicandra must provide quality logs, traces, crash information, and be easy for users to investigate.
        - 3.6.3 Nicandra must allow CPU, GPU, memory, asset, FPS, audio, and simulation profiling.
        - 3.6.4 Nicandra must expose a command line runner, allowing "cheats", debug commands, etc.
    - 3.7 Distribution
        - 3.7.1 Nicandra products must be installable, updatable, rollback-able and uninstallable.
        - 3.7.2 Nicandra products must support a config, cache, and user-data.
        - 3.7.3 Nicandra must help with platform signing, notarization (like on MacOS) and packaging.
        - 3.7.4 Nicandra must track licenses of third party assets, and package them.
- 4. Platform
    - 4.1 Desktop
        - 4.1.1 Windows 11 (arm, x86) - P1
        - 4.1.2 MacOS (arm) - P1 
        - 4.1.3 MacOS (x86) - P3
        - 4.1.4 Linux (arm, x86) - P1
        - 4.1.5 FreeBSD (arm, x86) - P1
    - 4.2 Web (WebGL and WASM) - P2
    - 4.3 Mobile
        - 4.3.1 Android - P2
        - 4.3.2 iOS/iPadOS - P3
    - 4.4 Headless Server - P1

# Policies

## Development Flow

- Features to build will be in [Version Plans](./version-plans.md). And completed versions will be in [Release Notes](./release-notes.md).
- For order, each version is to have a video doing:
    1. A demo if applicable (to validate frequently)
    2. Discussion of features added (non-technical)
    3. Technical discussion
- Apps and games will use Nicandra once the engine gains the needed features
- Demos 

## AI Policy

LLMs are the hot topic in 2026. At the present moment, I will favor
not using them except for these instances:

1. Research - To help find websites, resources, information, etc. on topics.
2. Debugging - For very niche issues, as its good at cutting down time here.
3. Adversarial Validation - AI is good at seeing gaps in testing and requirements. Did I properly do accessibility? Are there edge cases I'm not thinking of for a unit test?

Otherwise, AI is **not** to be used for code generation. 
This is because:

1. Conceptual Integrity is important. 
2. I want to write the code.
3. I'm not in a rush.

## Documentation

Also in development. Including this document. All of this
is living documentation and I may move things around as 
needed,

## Technical Discussion

Some of my other projects are tutorials walking through
each thing. Here, I'd rather zoom into specific more
difficult topics, and overall architecture, rather than
walking through every line of code.

I think this will:

1. Be more efficient
2. Be more focused
3. Be more beneficial for anyone following