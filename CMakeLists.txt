cmake_minimum_required(VERSION 3.8)

project("MG3TR")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("inc")
include_directories("src")

find_package(OpenGL REQUIRED)
if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    find_package(assimp REQUIRED)
endif()

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

set(CXX_DIRECTORIES
    "inc/glad"
    "inc/GLFW"
    "inc/glm"
    "inc/KHR"
    "inc/stb"

    "src"
    "src/Components"
    "src/Constants"
    "src/Graphics"
    "src/Graphics/Shaders"
    "src/Math"
    "src/Scene"
    "src/Scripting"
    "src/Utils"
    "src/Window"
)

set(CXX_HEADERS "")
set(CXX_SOURCES "")

foreach(DIR in ${CXX_DIRECTORIES})
    file(GLOB CXX_HEADERS_IN_DIR "${DIR}/*.hpp" "${DIR}/*.hxx")
    file(GLOB CXX_SOURCES_IN_DIR "${DIR}/*.cpp" "${DIR}/*.cxx" "${DIR}/*.c")

    list(APPEND CXX_HEADERS ${CXX_HEADERS_IN_DIR})
    list(APPEND CXX_SOURCES ${CXX_SOURCES_IN_DIR})
endforeach()

add_executable(${PROJECT_NAME} ${CXX_HEADERS} ${CXX_SOURCES})

target_link_libraries(${PROJECT_NAME} OpenGL::GL)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(DLL_SUBDIR "Win32")
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(DLL_SUBDIR "Win64")
    else()
        message(FATAL_ERROR "Project can only be built for 32 bits or 64 bits architectures.")
    endif()

    target_link_libraries(${PROJECT_NAME}
        "${CMAKE_CURRENT_LIST_DIR}/lib/GLFW/${DLL_SUBDIR}/glfw3.lib"
        "${CMAKE_CURRENT_LIST_DIR}/lib/assimp/${DLL_SUBDIR}/assimp-vc142-mt.lib"
    )

    add_library(GLFW "${CMAKE_CURRENT_LIST_DIR}/lib/GLFW/${DLL_SUBDIR}/glfw3.dll")
    set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE C)

    add_library(assimp "${CMAKE_CURRENT_LIST_DIR}/lib/assimp/${DLL_SUBDIR}/assimp-vc142-mt.dll")
    set_target_properties(assimp PROPERTIES LINKER_LANGUAGE CXX)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/lib/GLFW/${DLL_SUBDIR}/glfw3.dll"
            "${CMAKE_CURRENT_LIST_DIR}/lib/assimp/${DLL_SUBDIR}/assimp-vc142-mt.dll"
            
            # Destination directory
            "${CMAKE_BINARY_DIR}"
    )

elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} glfw assimp ${CMAKE_DL_LIBS})
endif()
