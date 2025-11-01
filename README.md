# 2D Rendering Engine — Algorithms and Graphics 
Technologies: Modern C++, OpenGL, GLFW, GLM, Linux, GDB, AWS Cloud, Shell Scripting
------------------------------------------------------------------------------------
# Overview
This project implements a lightweight 2D rendering engine in Modern C++ (C++17) using OpenGL and GLFW.
The engine demonstrates real-time rendering performance through batch rendering, custom GPU shader programs, and an object-oriented architecture.
It achieves over 60 frames per second while rendering 10,000+ polygons efficiently.

An optional TCP client–server module enables remote telemetry and process communication, deployable as a Linux daemon on AWS EC2.
The codebase is designed to be modular, cross-platform, and easily debuggable for academic or professional graphics research.
------------------------------------------------------------------------------------------------------------------------------------
# Key Features
Batch Rendering System: Minimizes draw calls for improved frame rates.

Custom Shader Pipeline: Implements vertex and fragment shaders for lighting and post-processing.

2D Camera System: Provides smooth translation and viewport control using arrow keys.

Performance Optimization: Maintains 60+ FPS rendering with vertex buffer reuse and reduced state changes.

Cross-Platform Compatibility: Runs on Linux, macOS, and Windows (MSYS2 or Visual Studio).

Optional Network Module: Provides a TCP client–server layer for remote logging or simulation control.

Daemonized Deployment: Supports background execution on AWS EC2 using shell automation.

Debugging Support: Compatible with GDB and OpenGL debug callbacks.

----------------------------------------------------------------------------------------------------------------------------
# Project Structure

```
2D-Engine/
├── include/
│   ├── Renderer2D.hpp
│   ├── Shader.hpp
├── src/
│   ├── main.cpp
│   ├── Renderer2D.cpp
│   ├── Shader.cpp
├── shaders/
│   ├── quad.vert
│   ├── quad.frag
├── CMakeLists.txt
├── LICENSE
└── README.md
```
-----------------------------------------------------------------------------------------------------------------------
# Build Instructions

Prerequisites

Install the following dependencies before building:

CMake ≥ 3.15

OpenGL ≥ 3.3

GLFW

GLAD

GLM

-----------------------------------------------------------------------------------------------------------------------
Linux (Ubuntu / Debian)
```
sudo apt update
sudo apt install -y build-essential cmake libglfw3-dev libgl1-mesa-dev libglad-dev libglm-dev
mkdir build && cd build
cmake ..
make -j
./rendering_engine_2d_batch_demo --quads=10000
```
----------------------------------------------------------------------------------------------------------------------
# macOS
```
brew install glfw glad glm
mkdir build && cd build
cmake ..
make
./rendering_engine_2d_batch_demo
```
--------------------------------------------------------------------------------------------------------------------
# Windows (MSYS2 MinGW64)
```
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake \
  mingw-w64-x86_64-glfw mingw-w64-x86_64-glad mingw-w64-x86_64-glm
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make -j
./rendering_engine_2d_batch_demo.exe
```
--------------------------------------------------------------------------------------------------------------------
# Controls
Key	Action
Arrow Keys	Move camera
Space	Toggle animation
Esc	Quit application
-----------------------------------------------------------------------------------------------------------------
# Performance
Configuration	Polygon Count	Average FPS
GTX 1650 Laptop GPU	10,000	~90 FPS
Intel Integrated GPU	5,000	~65 FPS

Efficient batching and state-change reduction ensure stable 60+ FPS performance even under heavy rendering loads.
------------------------------------------------------------------------------------------------------------------
# AWS Deployment
To run the TCP module as a background daemon:
```
nohup ./tcp_echo_client > engine.log 2>&1 &
```
To verify or stop the process:
```
ps aux | grep demo
kill <PID>
```
------------------------------------------------------------------------------------------------------------
# Author

Manoj Dattatreya Myneni
Master of Science in Computer Science, University of Illinois Chicago
Specialization in Systems Engineering, Distributed Computing, and Computer Graphics
