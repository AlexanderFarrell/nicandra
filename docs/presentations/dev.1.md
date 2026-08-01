---
theme: default
title: Nicandra
---

# Nicandra Engine

One tool to build apps, games and simulations.

<img src="./Nicandra002.png" width="200px">

---

# Purpose

Less fragmentation, more synergy.

Make tons of projects **without switching between frameworks, libraries and engines**. For example:

- 📝 My own word processor or writing tool.
- 📊 A spreadsheet program with Lua scripts
- 🏝️ Island survival game
- ⚔️ Role playing game
- ✅ Next version of my planner.
- ⛏️ Creative tools to edit maps, build stories, etc.

---

# Purpose

I want to blur the lines between app, game and simulation. 

- Apps frequently use 3D graphics.
- Games sometimes require rich UI.

---

Go to features

---

# Policies

## Work in Public

- 🍰 I'd like to take you along the journey. 
- 📚 I can learn from you, and maybe you can learn from me. 
- ✅ I can document my process for accountability.
- 🌍 Open source so other people can use it.

---

## Development Flow

- Features to do in Version Plans. Completed features in Release Notes.
- Video for each version:
    1. Demo
    2. Discussion
    3. Technical Dive
- Other projects will use Nicandra.

---

## AI Policy

Will **not use AI**, except for:

1. Research - Finding websites, resources, etc. Learning about topics.
2. Debugging - Useful speed up at times for niche issues.
3. As an adversary - Did I properly do accessibility? What are my unit tests missing.

---

## AI Policy

Why not use AI?

- I'm not in a rush.
- This is a fun project.
- Conceptual integrity is important.

---

# Technical Dives vs Code Explanation

- More beneficial to just focus on difficult concepts or overall architecture.
- Maybe we can do coding/design/specification sessions, let me know!

---

## Language 

I chose C++. I compared 4 different languages, and here's what I think.

---

### Zig

Pros: 

- Everything.

Cons:

- Language may still change with updates. 

---

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

---

### Rust

Pros:

- Cargo is amazing.
- Really like the modern features, such as how Rust does enums or error handling.
- Also large ecosystem of libraries (wgpu was tempting)

Cons:

- Borrow checker might be more of a hassle than useful. 
    - Just use valgrind/leaks/dr memory, and smart pointers in C++. Or handle lifetimes well for raw pointers.
    - Forces thread safe concepts everywhere, even on code you don't intend to multithread

---

### C++

Pros:

- Nice standard library
- All of C's libraries and all of C++'s libraries
- Very large flexibility, you can use OOP... or not.

Cons:

- Sometimes more verbose
- We may not be able to use std::expected as not all major compilers support.