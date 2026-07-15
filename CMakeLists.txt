cmake_minimum_required(VERSION 3.25)
project(obcx_actor_example VERSION 0.1.0 LANGUAGES CXX)

if(NOT TARGET obcx_core)
  find_package(obcx-sdk CONFIG REQUIRED)
endif()
include(OBCXActor)

obcx_add_actor(example
  SOURCES src/example_actor.cpp
  OUTPUT_NAME example)
target_include_directories(example_actor PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src)
