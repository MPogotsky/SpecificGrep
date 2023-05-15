cmake_minimum_required( VERSION 3.22.1 )
project( specific_grep )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

option( UNIT_TESTS "Enable tests" OFF )

add_subdirectory( src )

if( UNIT_TESTS )
  add_subdirectory( test )
endif()
