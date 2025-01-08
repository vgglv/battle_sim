cmake_minimum_required(VERSION 3.30)
project(battle-sim)

file(GLOB_RECURSE PLAYER_SOURCES
    "player/*.hpp"
    "player/*.cpp"
)

file(GLOB_RECURSE CLI_SOURCES
    "cli/*.cpp"
    "cli/*.hpp"
)

add_executable(battle-sim-player ${PLAYER_SOURCES})
add_executable(battle-sim-cli ${CLI_SOURCES})

set_target_properties(battle-sim-player PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)
set_target_properties(battle-sim-cli PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST "Automatically run unit-tests as a post build step" OFF)
set(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF)
set(JSONCPP_WITH_CMAKE_PACKAGE OFF)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
set(BUILD_OBJECT_LIBS OFF)

add_subdirectory(libs/raylib)
add_subdirectory(libs/jsoncpp)

target_link_libraries(battle-sim-player PRIVATE raylib)
target_link_libraries(battle-sim-cli PRIVATE jsoncpp_static)

set_target_properties(battle-sim-player PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
)

set_target_properties(battle-sim-cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
)