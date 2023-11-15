cmake_minimum_required(VERSION 3.0)
include (GenerateExportHeader)

project(ReKat)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Code/Libs/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Code/Libs/assimp)

add_subdirectory(Code/Libs/freetype)

if(NOT MSVC)
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    else()
        set(WINSOCK_LIBRARIES Ws2_32.lib Mswsock.lib AdvApi32.lib)
    endif()
endif()

include_directories(Code/Include/
                    Code/Libs/assimp/include/
                    Code/Libs/glad/include/
                    Code/Libs/freetype/include/
                    Code/Libs/glfw/include/
                    Code/Libs/glm/
                    Code/Libs/stb/)

file(GLOB LIBS_SOURCES Code/Libs/glad/src/glad.c)
source_group("Libs" FILES ${LIBS_SOURCES})

add_library ( ${PROJECT_NAME} SHARED ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} ${WINSOCK_LIBRARIES} ${LIBS_SOURCES})

GENERATE_EXPORT_HEADER ( ${PROJECT_NAME}
             BASE_NAME ${PROJECT_NAME}
             EXPORT_MACRO_NAME ${PROJECT_NAME}_EXPORT
             EXPORT_FILE_NAME ${PROJECT_NAME}_Export.h
             STATIC_DEFINE ${PROJECT_NAME}_BUILT_AS_STATIC
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})