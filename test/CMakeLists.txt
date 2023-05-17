# Find GTest
find_package( GTest REQUIRED )
include_directories( ${GTEST_INCLUDE_DIRS} )

set( LIBS
    ${GTEST_LIBRARIES}
    specific_grep_lib
)

set( TESTS
     UT_Options.cpp
)

add_executable( UT_SpecificGrep ${TESTS} )
target_link_libraries( UT_SpecificGrep
                       PRIVATE
                           ${LIBS} )
add_test(UT_SpecificGrep UT_SpecificGrep)