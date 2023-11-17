cmake_minimum_required(VERSION 3.13)

file(GLOB PROJECT_SOURCES # Code/Test/Graphik/help.cpp
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
                          # Code/Src/grapik.cpp
                          # Code/Src/node.cpp
                          # Code/Src/merged.cpp
                          Code/Test/Audio_test/main.cpp
                          Code/Include/*.cpp )
include( "cmake-modules/executable.cmake" )
