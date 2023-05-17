# Define executable name
set( EXECUTABLE specific_grep )

# Define core lib with sources and dpendencied
# for test part
set( CORE_LIB specific_grep_lib )

# Find boost lib
find_package( Boost REQUIRED COMPONENTS
              program_options
              thread
              filesystem
)

include_directories( ${Boost_INCLUDE_DIRS} )

set( SPECIFIC_GREP_DEPENDENCY
     ${Boost_LIBRARIES}
)

# Define sources
set( SPECIFIC_GREP_SOURCES
      FileManager.cpp
      Options.cpp
      Scout.cpp
      SpecificGrep.cpp
)

# Define core lib
add_library( ${CORE_LIB}
             ${SPECIFIC_GREP_SOURCES}
)
target_link_libraries( ${CORE_LIB} ${SPECIFIC_GREP_DEPENDENCY} )
target_include_directories( ${CORE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

# Executable part
add_executable( ${EXECUTABLE} main.cpp )
set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set_target_properties( ${EXECUTABLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                       ${CMAKE_BINARY_DIR}
)
target_link_libraries( ${EXECUTABLE} ${CORE_LIB} )
