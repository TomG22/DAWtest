cmake_minimum_required(VERSION 3.10)

set(OpenGL_GL_PREFERENCE "GLVND")

project(DAWtest)

# Set CMake to use static linking
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/WindowListener.cpp
)

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    GUIEditor
    Synth
)
