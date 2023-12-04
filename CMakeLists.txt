cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

# Src
file(GLOB PROJECT_SOURCES # Code/Src/grapik.cpp
                          # Code/Src/node.cpp
                          # Code/Src/V1.0/merged.cpp
                          # Code/Src/V1.1/main.cpp
                          # Code/Src/V1.3/main.cpp
                          Code/Src/V2.0/main.cpp
                          Code/Include/*.cpp )

# Test
file(GLOB _PROJECT_SOURCES # Code/Test/Graphik/help.cpp
                          # Code/Test/TestSock_Win/client.cpp
                          # Code/Test/TestSock_Win/server.cpp
                          # Code/Test/node_network/*.cpp
                          # Code/Test/Graphic_test/main.cpp
                          # Code/Test/Graphik/test_lib.cpp
                          # Code/Test/Graphik/test_freetype.cpp
                          # Code/Test/texture.cpp
                          # Code/Test/texture_RK.cpp
                          # Code/Test/tex.cpp
                          # Code/Test/*.cpp
                          # Code/Test/Audio_test/main.cpp
                          # Code/Test/button_test.cpp
                          Code/Test/tile_map.cpp
)

include( "cmake-modules/executable.cmake" )
