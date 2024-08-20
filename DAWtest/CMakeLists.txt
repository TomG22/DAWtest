cmake_minimum_required(VERSION 3.27.8)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER c++)

# add_compile_options(-Wall)

project(DAWtest)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Gui.cpp
    src/KeyboardController.cpp

    src/IndexBuffer.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp

    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/GLFW glfw)
add_subdirectory(engines)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/include/GLFW
    ${CMAKE_CURRENT_SOURCE_DIR}/engines/AudioEngine/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    AudioEngine
)