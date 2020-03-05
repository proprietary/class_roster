cmake_minimum_required(VERSION 3.13)

project(class_roster VERSION 1.0.0 LANGUAGES CXX)

include(cmake/local.cmake OPTIONAL)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=clang-diagnostic-*,clang-analyzer-*,-clang-analyzer-alpha*,cppcoreguidelines-*,cppcoreguidelines-pro-lifetime-*,performance-*,readability-*")

add_library(students STATIC)
target_sources(
  students
  PUBLIC
  "include/degree.h"
  "include/student.h"
  "include/networkStudent.h"
  "include/securityStudent.h"
  "include/softwareStudent.h"
  "src/student.cpp"
  "src/networkStudent.cpp"
  "src/securityStudent.cpp"
  "src/softwareStudent.cpp"
)
target_include_directories(
  students
  PUBLIC
  "include"
)
target_compile_features(
  students
  PRIVATE
  cxx_std_17
)

add_library(class_roster_lib STATIC)
target_sources(
  class_roster_lib
  PRIVATE
  "include/roster.h"
  "src/roster.cpp"
  )
target_link_libraries(class_roster_lib PRIVATE students)
target_include_directories(class_roster_lib PUBLIC "include")
target_compile_features(
  class_roster_lib
  PRIVATE
  cxx_std_17
)

add_executable(class_roster)
target_sources(
  class_roster
  PRIVATE
  "src/rosterMain.cpp"
)
target_link_libraries(class_roster PRIVATE class_roster_lib)
target_compile_features(
  class_roster
  PRIVATE
  cxx_std_17
)

# The assignment asks for no third-party libraries. The tests are
# commented out because they use gtest.
#add_subdirectory(test)
