cmake_minimum_required(VERSION 3.25.1)
project(DAWtest)

add_executable(${PROJECT_NAME} main.cpp
    gui.cpp
    player.cpp
    synth.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/GLFW glfw)
add_subdirectory(dependencies/PortAudio portaudio)

target_include_directories(${PROJECT_NAME} PRIVATE
    dependencies/PortAudio/include

)


target_link_libraries(${PROJECT_NAME} PUBLIC
    portaudio_static
    glfw
)
