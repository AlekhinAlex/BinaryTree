cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "inc/*.hpp")
file(GLOB TYPES "inc/types/*.hpp")
file(GLOB IMPLEMENTATIONS "impl/*.tpp")
file(GLOB TEST_HEADERS "tests/*.hpp")
file(GLOB TEST_SOURCE "tests/test_*.cpp")

list(REMOVE_ITEM TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_performance_big.cpp")


find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(${GTEST_INCLUDE_DIRS} inc impl)

add_executable(tests
    ${TEST_SOURCE}
    ${HEADERS}
    ${IMPLEMENTATIONS}
    ${TYPES}
)

# Замените строку add_executable(test_sorted_performance ...) на следующую
add_executable(test_sorted_performance
    tests/test_sorted_performance.cpp
    ${HEADERS}
    ${IMPLEMENTATIONS}
    ${TYPES}
)

# И убедитесь, что линковка библиотек выполняется правильно
target_link_libraries(test_sorted_performance ${GTEST_LIBRARIES} pthread)


add_executable(test_performance_big
    tests/test_performance_big.cpp
    ${HEADERS}
    ${IMPLEMENTATIONS}
    ${TYPES}
)

target_link_libraries(tests GTest::GTest GTest::Main pthread)
target_link_libraries(test_performance_big pthread)
