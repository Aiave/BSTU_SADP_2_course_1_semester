#setup cmake
cmake_minimum_required(VERSION 3.26)

#setup project
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME} CXX)
set(CMAKE_CXX_STANDARD 23)

# include all source and header files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# add custom rule for copy assets directory
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets/
            ${CMAKE_BINARY_DIR}
)
add_dependencies(${PROJECT_NAME} copy_assets)

# setup root directory like include
target_include_directories(${PROJECT_NAME}
        PRIVATE src
)
