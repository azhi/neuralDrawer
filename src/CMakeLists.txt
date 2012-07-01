cmake_minimum_required (VERSION 2.6)

set(CMAKE_BUILD_TYPE Debug)

set (PROJECT
    neuralDrawer)

set (SOURCES
    main.cpp

    neuron.cpp
    neuron.h

    neural_network.cpp
    neural_network.h

    field.cpp
    field.h
    
    extended_array.cpp
    extended_array.h

    sdl_controller.cpp
    sdl_controller.h

    main_controller.cpp
    main_controller.h
)

set (EXECUTABLE_OUTPUT_PATH ../bin)

find_package(SDL REQUIRED)

if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-mwindows -static-libgcc -static-libstdc++")
endif (WIN32)

add_executable (${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${SDL_LIBRARY})
