cmake_minimum_required(VERSION 3.5)
project(text_formatter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure --name")

find_package(Catch2 REQUIRED)

# Add the executable target
add_executable(formatter main.cpp formatter.cpp)
add_executable(test_formatter test_formatter.cpp formatter.cpp)
add_executable(bencmark benchmark.cpp formatter.cpp)

# Add include directories
target_include_directories(formatter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test_formatter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(bencmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(test_formatter Catch2::Catch2WithMain)

include(CTest)
enable_testing()
add_test(NAME FormatterTest COMMAND test_formatter)