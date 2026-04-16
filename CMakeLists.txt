cmake_minimum_required(VERSION 3.20)
project(obcx-plugin-example LANGUAGES CXX)

# When built standalone (outside OBCX tree), find the installed SDK
# When built via FetchContent from OBCX, obcx_core is already available
if(NOT TARGET obcx_core)
    find_package(obcx-sdk REQUIRED)
endif()

# Include the plugin helper (provides obcx_add_plugin function)
include(OBCXPlugin)

# Define the plugin
obcx_add_plugin(example
    SOURCES
        src/example_plugin.cpp
    DEPS
        # Add extra dependencies here, e.g.:
        # nlohmann_json::nlohmann_json
        # unofficial::sqlite3::sqlite3
)
