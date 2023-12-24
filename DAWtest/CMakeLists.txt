cmake_minimum_required(VERSION 3.25.1)
project(PortAudioTest)

add_executable(${PROJECT_NAME} main.cpp

)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/GLFW glfw)
add_subdirectory(libs/PortAudio portaudio)

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/PortAudio/include
    libs/PortAudio/src/hostapi/dsound
   
)


target_link_libraries(${PROJECT_NAME} PUBLIC
    portaudio_static
)
