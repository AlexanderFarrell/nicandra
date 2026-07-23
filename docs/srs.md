# Software Requirement Specification

## Executive Summary

Spindle is a lightweight, batteries-included game and application engine in Rust. 

## Features

- Build native desktop applications in Rust or Lua.
- Build 2D or 3D games
- Wide library for networking

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
        - 1.3.4 Backgrounds (with parallax) - P2
    - 1.4 Physics
        - 1.4.1 3D Physics
        - 1.4.2 2D Physics
        - 1.4.3 Ensure frustum, ray and sphere sampling
    - 1.5 Audio
        - 1.5.1 Sound effects - P1
        - 1.5.2 Music - P1
        - 1.5.3 3D Sounds - P2
        - 1.5.4 Filters like Reverb - P3
    - 1.6 World
        - 1.6.1 Entity System - P1
        - 1.6.2 Verb System - P1
        - 1.6.3 Multiplayer support - P3
    - 1.7 Gameplay
        - 1.7.1 Inventory - P2
        - 1.7.2 NPC Dialog or Shared Scripting System - P3
    - 1.8 Procedural
        - 1.8.1 Image & Array2D Filters - P1
            - 1.8.1.1 Blur
            - 1.8.1.2 Voronoi
            - 1.8.1.3 
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
        - 2.1.3 Text
            - 2.1.3.1 Basic Styling
                - 2.1.3.1.1 Font
                - 2.1.3.1.1 Font Weight
                - 2.1.3.1.1 Italic 
                - 2.1.3.1.1 Underline 
                - 2.1.3.1.1 Font Size 
                - 2.1.3.1.1 Line Height
                - 2.1.3.1.1 Paragraph Indent
    - 2.2 2D 
