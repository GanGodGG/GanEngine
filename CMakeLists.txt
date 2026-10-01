cmake_minimum_required(VERSION 3.16)

project(gEngine VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENGINE_SOURCES src/WindowManager.cpp src/Modeling.cpp src/Shaders.cpp src/Time.cpp)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_library(gEngine STATIC ${ENGINE_SOURCES})
add_compile_definitions(SOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(gEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(gEngine PUBLIC OpenGL::GL GLEW::GLEW glfw)
target_compile_definitions(gEngine PRIVATE VERSION_INFO="${PROJECT_VERSION}")



