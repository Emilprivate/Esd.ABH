cmake_minimum_required(VERSION 3.0)
project(Automatic-Bargain-Hunting)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

file(COPY Ressources/Fonts/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Linux -pthread shenanigans
if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif ()

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
if (CMAKE_SYSTEM_NAME STREQUAL Darwin)
    add_library(sokol STATIC Libraries/sokol/sokol.c ${SOKOL_HEADERS})
    target_compile_options(sokol PRIVATE -x objective-c)
    target_link_libraries(sokol PUBLIC
            "-framework QuartzCore"
            "-framework Cocoa"
            "-framework MetalKit"
            "-framework Metal")
else ()
    add_library(sokol STATIC Libraries/sokol/sokol.c ${SOKOL_HEADERS})
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        target_link_libraries(sokol INTERFACE X11 Xi Xcursor GL dl m)
        target_link_libraries(sokol PUBLIC Threads::Threads)
    endif ()
endif ()
target_link_libraries(sokol PUBLIC cimgui)
target_include_directories(sokol INTERFACE sokol)

#=== EXECUTABLE:
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_executable(Automatic-Bargain-Hunting WIN32 "src/main.c" "Debug/terminal_debug_menu.c" "Debug/terminal_debug_menu.h"
            "src/Source/profile_management.c" "src/Header/profile_management.h"
            "src/Source/utilities.c" "src/Header/utilities.h"
            "src/UI/Source/user_interface.c" "src/UI/Header/user_interface.h"
            "src/UI/Source/window_navigation_control.c" "src/UI/Header/window_navigation_control.h"
            "src/Source/user_operations.c" "src/Header/user_operations.h" src/Definitions/struct_definitions.h src/Definitions/enum_definitions.h src/UI/Source/ui_window_settings.c src/UI/Header/ui_window_settings.h)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Automatic-Bargain-Hunting)
else ()
    add_executable(Automatic-Bargain-Hunting "src/main.c" "Debug/terminal_debug_menu.c" "Debug/terminal_debug_menu.h"
            "src/Source/profile_management.c" "src/Header/profile_management.h"
            "src/Source/utilities.c" "src/Header/utilities.h"
            "src/UI/Source/user_interface.c" "src/UI/Header/user_interface.h"
            "src/UI/Source/window_navigation_control.c" "src/UI/Header/window_navigation_control.h"
            "src/Source/user_operations.c" "src/Header/user_operations.h" src/Definitions/struct_definitions.h src/Definitions/enum_definitions.h src/UI/Source/ui_window_settings.c src/UI/Header/ui_window_settings.h)
endif ()
target_link_libraries(Automatic-Bargain-Hunting sokol)

# Emscripten-specific linker options
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # use our own minimal shell.html
    target_link_options(Automatic-Bargain-Hunting PRIVATE --shell-file ../sokol/shell.html)
    # WASM+JS size optimizations
    target_link_options(Automatic-Bargain-Hunting PRIVATE -sNO_FILESYSTEM=1 -sASSERTIONS=0 -sMALLOC=emmalloc --closure=1)
endif ()

# explicitly strip dead code
if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    target_link_options(Automatic-Bargain-Hunting PRIVATE LINKER:-dead_strip)
endif ()

# this hack removes the xxx-CMakeForceLinker.cxx dummy file
set_target_properties(Automatic-Bargain-Hunting PROPERTIES LINKER_LANGUAGE CXX)
