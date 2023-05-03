cmake_minimum_required(VERSION 3.22.1)
project(specific_grep)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find boost lib dependency
find_package(Boost REQUIRED COMPONENTS
    program_options
    thread
    filesystem
)

include_directories(${Boost_INCLUDE_DIRS})

# Find sources
file( GLOB SOURCE_FILES
    src/*.cpp
)

add_executable(specific_grep ${SOURCE_FILES})

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(specific_grep PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(specific_grep
    ${Boost_LIBRARIES}
)
