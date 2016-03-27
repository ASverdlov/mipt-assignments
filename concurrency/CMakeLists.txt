cmake_minimum_required(VERSION 2.8)
project(futex)

## Include Boost.Tests
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS REQUIRED unit_test_framework)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Man, I've found no boost.test for you...")
    return()
else()
    include_directories(${Boost_INCLUDE_DIRS})
endif()

## Compile sources
include_directories(include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
set(SOURCE "test/test.cpp")
add_executable(${PROJECT_NAME} ${SOURCE})

## Link all together
target_link_libraries(${PROJECT_NAME}
                      ${Boost_UNIT_TEST_FRAMEWORK})
