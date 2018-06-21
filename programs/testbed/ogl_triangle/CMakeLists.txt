cmake_minimum_required(VERSION 3.8)
project(opengl1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)

# include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# include glfw3
find_package(glfw3 REQUIRED)

# include glad
include_directories(${CMAKE_SOURCE_DIR}/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/glad)

# include glad
include_directories(${CMAKE_SOURCE_DIR}/stb_image)
add_subdirectory(${CMAKE_SOURCE_DIR}/stb_image)

set(SOURCE_FILES main.cpp Shader.h Shader.cpp)
add_executable(opengl1 ${SOURCE_FILES})
# target link OpenGL
target_link_libraries(opengl1 ${OPENGL_LIBRARIES})

# target link glad
target_link_libraries(opengl1 glad)

# target link glfw
target_link_libraries(opengl1 glfw)

# target link stb_image
target_link_libraries(opengl1 stb_image)

add_custom_command(
        TARGET opengl1
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
        VERBATIM
)
