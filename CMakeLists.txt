cmake_minimum_required(VERSION 3.18)

project(game VERSION 0.4)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(app_v01)

set_property(TARGET app_v01 PROPERTY CXX_STANDARD 17)

add_subdirectory(packages/assimp)
# add_subdirectory(packages/glew/build/cmake)

add_subdirectory(external/stb_image)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/glew/build/cmake)

add_subdirectory(packages/lua)
add_subdirectory(packages/freetype)
add_subdirectory(packages/spdlog)