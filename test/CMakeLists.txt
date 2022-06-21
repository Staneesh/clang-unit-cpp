cmake_minimum_required(VERSION 3.14)


# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_executable
  #cunit_test.cpp
  #cunit_demo1_filled.cpp
  #cunit_demo2_filled.cpp
  #cunit_demo4.cpp
  cunit_demo5_filled.cpp
)
target_link_libraries(
  test_executable
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_executable)
