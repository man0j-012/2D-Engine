
cmake_minimum_required(VERSION 3.15)
project(rendering_engine_2d_batch_demo LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_NETWORK "Build optional TCP client demo" OFF)

# Find dependencies: OpenGL, GLFW, and glad (modern OpenGL loader)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
# Try config package first, then fallback to module if available
find_package(glad CONFIG QUIET)
if(NOT glad_FOUND)
  find_package(glad REQUIRED)
endif()

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/Renderer2D.cpp
  src/Shader.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glad)

if(BUILD_NETWORK)
  add_executable(tcp_echo_client src/tcp_echo_client.cpp)
  target_include_directories(tcp_echo_client PRIVATE include)
endif()

# Copy shaders to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/shaders
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)
