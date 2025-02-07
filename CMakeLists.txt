cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(testingcpp C CXX)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory("thirdparty/glad")

add_executable(app main.cpp)
target_link_libraries(app PRIVATE glfw glad OpenGL::GL dl)
