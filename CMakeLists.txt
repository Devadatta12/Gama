cmake_minimum_required(VERSION 3.10)
project(Gama VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/Engine)
set(INC_DIR ${PROJECT_SOURCE_DIR}/Include)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/Tests)

include_directories(${INC_DIR})
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp)

add_executable(Gama ${SRC_FILES})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Gama sfml-graphics sfml-window sfml-system)

find_package(cppzmq REQUIRED)
target_link_libraries(Gama cppzmq)
#target_include_directories(Gama ${ZeroMQ_INCLUDE_DIRS})
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(runTests ${TEST_FILES} ${SRC_FILES})
#target_link_libraries(runTests GTest::GTest GTest::Main sfml-graphics sfml-window sfml-system ${PC_ZMQ_LIBRARIES})
#
#add_test