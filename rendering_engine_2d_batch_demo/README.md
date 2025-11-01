
# Rendering and Game Engine — 2D Batch Renderer (C++)

A compact C++ demo of a **2D batch renderer** using **modern OpenGL** with **GLFW + glad**.
It renders thousands of quads with a single draw call per batch, showcasing 60+ FPS potential
on typical hardware. The code is clean and resume-friendly.

> **Features**
> - Modern C++ (C++17), OOP design, single VAO/VBO batch
> - Instanced-like CPU-side batching (position, size, color)
> - Minimal shader pipeline (vertex/fragment)
> - Simple camera transform and time-based animation toggle
> - Cross-platform: Linux, macOS, Windows (via MSYS/MinGW or Visual Studio)

## Build

### macOS (Homebrew)
```bash
brew install glfw glad
mkdir build && cd build
cmake ..
make -j
./rendering_engine_2d_batch_demo
```

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install -y cmake g++ libglfw3-dev libgl1-mesa-dev
# Install glad via package manager if available, otherwise use vcpkg:
#   sudo apt install -y libglad-dev
# or vcpkg:
#   git clone https://github.com/microsoft/vcpkg.git && ./vcpkg/bootstrap-vcpkg.sh
#   ./vcpkg/vcpkg install glad glfw3
#   cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ..
mkdir build && cd build
cmake ..
make -j
./rendering_engine_2d_batch_demo
```

### Windows (MSYS2 MinGW64)
```bash
# In MSYS2 MinGW64 shell
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake \
  mingw-w64-x86_64-glfw mingw-w64-x86_64-glad
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make -j
./rendering_engine_2d_batch_demo.exe
```

> If CMake can't find **glad**, install it via your package manager or vcpkg. This project expects
> `find_package(glad)` to succeed (either CONFIG or MODULE mode).

## Run
```
./rendering_engine_2d_batch_demo
```

- **Arrow keys**: pan camera
- **Space**: toggle animation
- **Esc**: quit

## Performance
Set the number of quads via the `--quads=N` CLI flag. Example:
```
./rendering_engine_2d_batch_demo --quads=10000
```
On a modest GPU, 10,000 quads should easily hit **60+ FPS**.

## License
MIT — free to use in your GitHub.



# Dependency Notes

This project uses:
- GLFW (window/input)
- glad (OpenGL loader)
- OpenGL
- GLM (header-only math library)

Install via package manager (brew/apt/pacman/vcpkg). On Debian/Ubuntu:
```
sudo apt install libglfw3-dev libglad-dev libglm-dev
```
