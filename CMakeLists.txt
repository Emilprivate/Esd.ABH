cmake_minimum_required(VERSION 3.0)
project(P1-extension)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

file(COPY Ressources/Fonts/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Linux -pthread shenanigans
if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

#=== LIBRARY: cimgui + Dear ImGui
add_library(cimgui STATIC
        Libraries/cimgui/cimgui.cpp
        Libraries/cimgui/cimgui.h
        Libraries/cimgui/imgui/imgui.cpp
        Libraries/cimgui/imgui/imgui.h
        Libraries/cimgui/imgui/imgui_widgets.cpp
        Libraries/cimgui/imgui/imgui_draw.cpp
        Libraries/cimgui/imgui/imgui_tables.cpp
        Libraries/cimgui/imgui/imgui_demo.cpp)
target_include_directories(cimgui INTERFACE Libraries/cimgui)

#=== LIBRARY: sokol
# add headers to the the file list because they are useful to have in IDEs
set(SOKOL_HEADERS
        Libraries/sokol/sokol_gfx.h
        Libraries/sokol/sokol_app.h
        Libraries/sokol/sokol_imgui.h
        Libraries/sokol/sokol_glue.h)
if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    add_library(sokol STATIC Libraries/sokol/sokol.c ${SOKOL_HEADERS})
    target_compile_options(sokol PRIVATE -x objective-c)
    target_link_libraries(sokol PUBLIC
        "-framework QuartzCore"
        "-framework Cocoa"
        "-framework MetalKit"
        "-framework Metal")
else()
    add_library(sokol STATIC Libraries/sokol/sokol.c ${SOKOL_HEADERS})
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        target_link_libraries(sokol INTERFACE X11 Xi Xcursor GL dl m)
        target_link_libraries(sokol PUBLIC Threads::Threads)
    endif()
endif()
target_link_libraries(sokol PUBLIC cimgui)
target_include_directories(sokol INTERFACE sokol)

#=== EXECUTABLE:
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_executable(P1-extension WIN32 "main.c" "Debug/terminal_debug_menu.c" "Debug/terminal_debug_menu.h"
            "profile_management.c" "profile_management.h"
            "utilities.c" "utilities.h"
            "UI/user_interface.c" "UI/user_interface.h"
            "UI/window_navigation_control.c" "UI/window_navigation_control.h"
            "user_operations.c" "user_operations.h")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT P1-extension)
else()
    add_executable(P1-extension "main.c" "Debug/terminal_debug_menu.c" "Debug/terminal_debug_menu.h"
            "profile_management.c" "profile_management.h"
            "utilities.c" "utilities.h"
            "UI/user_interface.c" "UI/user_interface.h"
            "UI/window_navigation_control.c" "UI/window_navigation_control.h"
            "user_operations.c" "user_operations.h")
endif()
target_link_libraries(P1-extension sokol)

# Emscripten-specific linker options
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # use our own minimal shell.html
    target_link_options(P1-extension PRIVATE --shell-file ../sokol/shell.html)
    # WASM+JS size optimizations
    target_link_options(P1-extension PRIVATE -sNO_FILESYSTEM=1 -sASSERTIONS=0 -sMALLOC=emmalloc --closure=1)
endif()

# explicitly strip dead code
if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    target_link_options(P1-extension PRIVATE LINKER:-dead_strip)
endif()

# this hack removes the xxx-CMakeForceLinker.cxx dummy file
set_target_properties(P1-extension PROPERTIES LINKER_LANGUAGE CXX)
