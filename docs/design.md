# Nicandra Design

This is a work in progress.

## Language 

I chose C++. I compared 4 different languages, and here's what I think.

### Zig

Pros: 

- Everything.

Cons:

- Language may still change with updates. 

### C

For context, I did a proof of concept in C. Really liked it.

Pros:

- Language is simple. Forces this simplicity.
- Code is very readable (without macros)
- Could support other languages VERY easily later.
- Massive ecosystem of libraries.

Cons:

- Some libraries are C++, making integration more awkward in some cases.
- Just want some modern tooling out of the box with the standard library.

### Rust

Pros:

- Cargo is amazing.
- Really like the modern features, such as how Rust does enums or error handling.
- Also large ecosystem of libraries (wgpu was tempting)

Cons:

- Borrow checker might be more of a hassle than useful. 
    - Just use valgrind/leaks/dr memory, and smart pointers in C++. Or handle lifetimes well for raw pointers.
    - Forces thread safe concepts everywhere, even on code you don't intend to multithread

### C++

Pros:

- Nice standard library
- All of C's libraries and all of C++'s libraries
- Very large flexibility, you can use OOP... or not.

Cons:

- Sometimes more verbose
- We may not be able to use std::expected as not all major compilers support.

## Modules

### Level 1 - Core

This consists of the lowest level of Nicandra. Primarily concerned with
hardware, assets, and common utilities.

- Nicandra-App (lib) - Engine, runtime, windowing, brings everything together
- Nicandra-Assets (lib) - Asset management, loading and saving.
- Nicandra-Math (lib) - Linear algebra, coordinates, stats, random, etc.
- Nicandra-Visual (lib) - Rendering
- Nicandra-Audio (lib) - Sound and music
- Nicandra-Input (lib) - Keyboard, mouse, etc.
- Nicandra-Networking (lib) - Networking, servers, clients, etc.
- Nicandra-Platform (lib) - Access to OS capabilities (notifications, etc.)
- Nicandra-Profile (lib) - Low level profiling and logging
- Nicandra-GPU-Compute (lib) - Low level parallel compute

### Level 2 - Business Logic

This consists of the foundation to game and app logic. You could make entire
games or apps at this layer, though without much built in.

- Nicandra-World (lib) - Entity and verb system, open world handling (entity level)
- Nicandra-Physics (lib) - Physics engine

### Level 3 - Common

This layer has common things you'd find in games, like terrains, procedural
generation, etc. Sits on top of business layer.

- Nicandra-3D (lib) - Terrain, buildings, water, etc.
- Nicandra-2D (lib) - Sprites, Tilemap, Non-Realtime Vector, etc.
- Nicandra-Gameplay (lib) - Inventory and NPCs (might not do)
- Nicandra-UI (lib) - User interface
- Nicandra-Doc (lib) - Document model, undo & redo, etc.
- Nicandra-Creation (lib) - Procedural generation

### Level 4 - Developer

This layer has developer tools which sit on top of everything.

- Nicandra-SDK (lib) - Developer bindings.
- Nicandra-Shell (lib) - CLI inside Nicandra for commands and scripting.
- Nicandra-Lua (lib) - Lua bindings (separate from SDK) for Nicandra
- Nicandra-Scripts (scripts) - Various scripts, (possibly not needed)

### Level 5 - Tooling

This layer consists of tooling. It's possible after almost every video that 
examples gets added to.

- Nicandra-Editor (bin) - An editor program for beforediting Nicandra worlds and UI.
- Nicandra-Workflow-Tests (bin) - While unit tests are throughout, these would run full workflow tests
- Nicandra-Examples (bins) - Many different examples of how Nicandra works, demos go here.
- Nicandra-Template (repo) - Possibly not needed.

## 