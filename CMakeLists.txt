cmake_minimum_required(VERSION 2.6)
project(TrackerProxy)

# Setup boost dependency
find_package(Boost 1.54 COMPONENTS system thread REQUIRED)
set(Boost_USE_STATIC_LIBS ON) # link statically to boost

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  message(STATUS "Boost Found")
else()
  message(FATAL_ERROR "Boost lib not found, please install Boost (at least 1.54)")
endif()

# enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TrackerProxy_SOURCES
  src/main.cc
  src/server.cc)

add_executable(TrackerProxy ${TrackerProxy_SOURCES})

target_link_libraries(TrackerProxy ${Boost_LIBRARIES})
