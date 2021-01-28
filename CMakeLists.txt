cmake_minimum_required(VERSION 3.18)

project(game VERSION 0.4)

add_subdirectory(app_v01)

add_subdirectory(packages/stb_image)
add_subdirectory(packages/assimp)
add_subdirectory(packages/glew/build/cmake)
add_subdirectory(packages/glfw)
add_subdirectory(packages/lua)
add_subdirectory(packages/freetype)
add_subdirectory(packages/spdlog)