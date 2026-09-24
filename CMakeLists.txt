cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE Debug)

project(IAMGANGOD VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(IAMGANGOD src/main.cpp src/WindowManager.cpp src/Modeling.cpp src/Shaders.cpp)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_compile_definitions(SOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_directories(IAMGANGOD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_link_libraries(IAMGANGOD PRIVATE OpenGL::GL GLEW::GLEW glfw)
