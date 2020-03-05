#########
# Tests #
#########

include(CTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e588eb1ff9ff6598666279b737b27f983156ad85
)
FetchContent_MakeAvailable(googletest)
if (NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(test_roster)
target_sources(test_roster PRIVATE "test_roster.cpp")
target_link_libraries(test_roster PRIVATE class_roster_lib gtest_main)
