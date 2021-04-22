# cmake version / definitions
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(OpenglProject)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE DEBUG)


FIND_PACKAGE(OpenGL REQUIRED)

add_executable(main
        src/Colour.cpp
        src/Colour.hpp
        src/Application.cpp
        src/Application.hpp
        src/Shader.cpp
        src/Shader.hpp
        src/App.cpp
        src/App.hpp

        lib/glad/src/glad.c src/glError.cpp src/glError.hpp src/main.cpp)



set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

# glad
include_directories(lib/glad/include)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

add_compile_definitions(GLFW_INCLUDE_NONE)
