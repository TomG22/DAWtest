cmake_minimum_required(VERSION 3.25.1)
project(OpenALTest)

add_executable(${PROJECT_NAME} main.cpp
    gui.cpp
    player.cpp
    synth.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/GLFW)

target_include_directories(${PROJECT_NAME}
    PUBLIC libs
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(${PROJECT_NAME}
    PRIVATE libs
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
glfw
winMM.Lib
)
