
include(FetchContent)

# GoogleTest configuration
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googletest)


# Test executable
add_executable(movie_booking_tests
    main_tests.cpp
)

target_link_libraries(movie_booking_tests
    PRIVATE
        movie_booking_core
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(movie_booking_tests)