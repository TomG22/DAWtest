cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER c++)

# add_compile_options(-Wall)

project(DAWtest)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Gui.cpp
    src/KeyboardController.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/GLFW glfw)
add_subdirectory(engines)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
    engines/AudioEngine/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    portaudio_static
    glfw
    AudioEngine
)