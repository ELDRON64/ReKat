project(ReKat)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
endif()

file(GLOB LIBS_SOURCES    Code/Libs/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Code/Include/*.hpp
                          Code/Inlcude/*.h)
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
                          Code/Src/merged.cpp
                          Code/Include/*.cpp )
file(GLOB PROJECT_SHADERS Code/Resources/Shaders/*.cs
                          Code/Resources/Shaders/*.fs
                          Code/Resources/Shaders/*.gs
                          Code/Resources/Shaders/*.vs)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Include" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Libs" FILES ${LIBS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${LIBS_SOURCES})

# find_library ( OPENAL_LIBRARY
    # Names same as in CMake's vanilla FindOpenAL
    # # NAMES OpenAL al openal OpenAL32 OpenAL32d
    # For binary OpenAL Soft distribution on Windows
    # # PATH_SUFFIXES ${_OPENAL_LIBRARY_PATH_SUFFIX}
    # The other PATHS from CMake's vanilla FindOpenAL seem to be a legacy
    # cruft, skipping those. The Windows registry used by the vanilla
    # FindOpenAL doesn't seem to be set anymore either.
    # # REQUIRED HINTS "c:/Users/cicciogamer/Documents/ReKat/openAl" )

add_library(ReKatd ReKat.dll)

target_link_libraries(${PROJECT_NAME} assimp glfw freetype 
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} ${WINSOCK_LIBRARIES} ${OPENAL_LIBRARY} )

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Code/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
