🕹️ 2D Rendering Engine — Algorithms & Graphics (C++17, OpenGL)
📆 Nov 2024 – Dec 2024

Technologies: Modern C++, OpenGL / GLFW, GLM, Shell Scripting, Linux, GDB, AWS Cloud

🚀 Overview

This project showcases a real-time 2D rendering engine built completely in Modern C++ (17) using OpenGL, GLFW, and GLM.
It implements batch rendering, custom GPU shaders, and an object-oriented architecture, capable of rendering 10 000 + polygons at 60 FPS.

The system also integrates a lightweight TCP client-server module that can run as a daemon process on a Linux VM (AWS EC2) for performance logging and simulation control.

🎮 Features

🧩 Batch Rendering System – minimizes draw calls by batching thousands of quads

💡 Custom Shader Pipeline – vertex & fragment shaders for lighting and post-processing

🎥 Camera Controls – 2D panning using arrow keys

⚡ High Performance – 60 + FPS rendering @ 10 K polygons via vertex buffer reuse

🖥️ Cross-Platform – runs on Linux, macOS, and Windows (MSYS2 / Visual Studio)

☁️ AWS Deployment – daemonized server module for remote telemetry

🪶 Debug-Friendly – designed for inspection with GDB and OpenGL debug callbacks

🏗️ Project Structure
2D-Engine/
├── include/
│   ├── Renderer2D.hpp      # Core batch renderer
│   ├── Shader.hpp          # Shader abstraction
├── src/
│   ├── main.cpp            # Engine entry point
│   ├── Renderer2D.cpp      # Batching logic
│   ├── Shader.cpp          # Shader compilation
├── shaders/
│   ├── quad.vert           # Vertex shader
│   ├── quad.frag           # Fragment shader
├── CMakeLists.txt          # Build configuration
├── LICENSE                 # MIT License
└── README.md               # Project documentation

⚙️ Build Instructions
🧠 Prerequisites

Install:

CMake ≥ 3.15

OpenGL 3.3 +

glfw, glad, glm

🐧 Linux (Ubuntu / Debian)
sudo apt update
sudo apt install -y build-essential cmake libglfw3-dev libgl1-mesa-dev libglad-dev libglm-dev
mkdir build && cd build
cmake ..
make -j
./rendering_engine_2d_batch_demo --quads=10000

🍎 macOS
brew install glfw glad glm
mkdir build && cd build
cmake ..
make
./rendering_engine_2d_batch_demo

🪟 Windows (MSYS2 MinGW64)
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake \
  mingw-w64-x86_64-glfw mingw-w64-x86_64-glad mingw-w64-x86_64-glm
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make -j
./rendering_engine_2d_batch_demo.exe

🎮 Controls
Key	Action
⬅️ ⬆️ ⬇️ ➡️	Move camera
Space	Toggle animation
Esc	Quit
📊 Performance
Environment	Polygons	Average FPS
GTX 1650 Laptop GPU	10 000	≈ 90 FPS
Intel Integrated GPU	5 000	≈ 65 FPS

Batching and minimal state changes allow consistent 60 + FPS even under heavy loads.

🧪 Sample Output
[Renderer] OpenGL 3.3 Core Profile Initialized
[Renderer] Drawing 10000 Quads @ 60 FPS

☁️ AWS Deployment

Run the network module as a background daemon:

nohup ./tcp_echo_client > engine.log 2>&1 &


Monitor:

ps aux | grep demo
kill <PID>

🧰 Tools Used

CMake – Cross-platform build system

GDB – Runtime debugging

Shell Scripting – Daemon automation

AWS EC2 – Cloud testing environment

👨‍💻 Author

Manoj Dattatreya Myneni
M.S. in Computer Science, University of Illinois Chicago
🎯 Specialization — Systems Engineering • Distributed Computing • Computer Graphics
