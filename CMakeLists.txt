cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(testingcpp C CXX)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("thirdparty/")
add_subdirectory("thirdparty/glad")

# add imgui to project
file(
  GLOB
  IMGUI_SRC
  thirdparty/imgui/imgui.cpp
  thirdparty/imgui/imgui_draw.cpp
  thirdparty/imgui/imgui_demo.cpp
  thirdparty/imgui/imgui_widgets.cpp
  thirdparty/imgui/imgui_tables.cpp
  thirdparty/imgui/backends/imgui_impl_glfw.cpp
  thirdparty/imgui/backends/imgui_impl_opengl3.cpp)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC thirdparty/imgui)

set(sources src/main.cpp src/circle.cpp src/rectangle.cpp)

add_executable(app ${sources})
target_link_libraries(app PRIVATE glfw glad imgui glm OpenGL::GL dl)

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/resources/shaders")
add_compile_definitions(SHADER_DIR="${SHADER_DIR}")
