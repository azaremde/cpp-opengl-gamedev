set(project_name "app_v01")

project(${project_name})

file(
    GLOB
    src
    src/*.cpp
    src/**/*.cpp
    src/**/**/*.cpp
    src/**/**/**/*.cpp
    src/*.h
    src/**/*.h
    src/**/**/*.h
    src/**/**/**/*.h
)

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_executable(${project_name} ${src})

target_include_directories(${project_name} PUBLIC src)

target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/stb_image/include)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/glew/include)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/glfw/include)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/assimp/include)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/lua)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/glm)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/freetype/include)
target_include_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/packages/spdlog/include)

target_link_libraries(${project_name} stb_image)
target_link_libraries(${project_name} glew_s)
target_link_libraries(${project_name} glfw)
target_link_libraries(${project_name} lualib)
target_link_libraries(${project_name} assimp)
target_link_libraries(${project_name} freetype)
target_link_libraries(${project_name} spdlog)