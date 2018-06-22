cmake_minimum_required(VERSION 3.8)
project(ogl_triangle)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/testbed/ogl_triangle/bin)

# include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# include glfw3
find_package(glfw3 REQUIRED)

# include glad
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

# include glad
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stb_image)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stb_image)

set(SOURCE_FILES main.cpp Shader.h Shader.cpp Texture.cpp Texture.h ShaderProgram.cpp ShaderProgram.h PipelineData.cpp PipelineData.h)
add_executable(ogl_triangle ${SOURCE_FILES})

# target link OpenGL
target_link_libraries(ogl_triangle ${OPENGL_LIBRARIES})

# target link glad
target_link_libraries(ogl_triangle glad)

# target link glfw
target_link_libraries(ogl_triangle glfw)

# target link stb_image
target_link_libraries(ogl_triangle stb_image)

add_custom_command(
        TARGET ogl_triangle
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
        VERBATIM
)
