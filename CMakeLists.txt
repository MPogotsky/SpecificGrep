cmake_minimum_required(VERSION 3.22.1)
project(specific_grep)
set(CMAKE_CXX_STANDARD 17)

# Add source files
file( GLOB SOURCE_FILES
    *.cpp
)

# Find boost lib dependency
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(specific_grep ${SOURCE_FILES})

target_link_libraries(specific_grep ${Boost_LIBRARIES})
