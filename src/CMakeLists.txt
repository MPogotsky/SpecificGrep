# Set target name
set( TARGET specific_grep )

# Find boost lib dependency
find_package( Boost REQUIRED COMPONENTS
              program_options
              thread
              filesystem
)

include_directories( ${Boost_INCLUDE_DIRS} )

# Find sources
file( GLOB SOURCE_FILES
      *.cpp
)

add_executable( ${TARGET} ${SOURCE_FILES} )

set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )
set_target_properties( ${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                       ${CMAKE_BINARY_DIR}
)

target_link_libraries( ${TARGET} ${Boost_LIBRARIES} )
