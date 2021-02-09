cmake_minimum_required(VERSION 3.18)

project(game VERSION 0.4)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(app_v01)

set_property(TARGET app_v01 PROPERTY CXX_STANDARD 17)

set(GLFW_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/glfw/include)
set(GLEW_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/glew/include)

add_subdirectory(external/imgui)
add_subdirectory(external/assimp)
add_subdirectory(external/stb_image)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/glew/build/cmake)
add_subdirectory(external/lua)
add_subdirectory(external/freetype)
add_subdirectory(external/spdlog)
