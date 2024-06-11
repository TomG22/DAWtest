cmake_minimum_required(VERSION 3.27.8)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER c++)

project(DAWtest)

add_executable(${PROJECT_NAME} main.cpp
    Gui.cpp
    Player.cpp
    PaStreamHandler.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/GLFW glfw)
add_subdirectory(dependencies/PortAudio portaudio)

# target_include_directories(${PROJECT_NAME} PRIVATE
# 
# )

target_link_libraries(${PROJECT_NAME} PUBLIC
    portaudio_static
    glfw
)
