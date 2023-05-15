# Find GTest
find_package( GTest REQUIRED )
include_directories( ${GTEST_INCLUDE_DIRS} )

# Find boost lib dependency
find_package( Boost REQUIRED COMPONENTS
              program_options
              thread
              filesystem
)
include_directories( ${Boost_INCLUDE_DIRS} )

set( TESTS UT_Options.cpp )
set( SOURCES ${CMAKE_SOURCE_DIR}/src/Options.cpp )

add_executable( UT_SpecificGrep ${TESTS} ${SOURCES} )
target_link_libraries( UT_SpecificGrep PRIVATE ${GTEST_LIBRARIES} ${Boost_LIBRARIES} )
