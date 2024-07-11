cmake_minimum_required(VERSION 3.0)

project(tetris)

set(SDL_HEADER_LOCATION "/usr/include/SDL2")

set(SDL_HEADERS "${SDL_HEADER_LOCATION}/SDL.h" "${SDL_HEADER_LOCATION}/SDL_ttf.h")

add_library(SDL2_LIB STATIC IMPORTED GLOBAL "/usr/lib/x86_64-linux-gnu/libSDL2.a")
add_library(SDL2_TTF_LIB STATIC IMPORTED GLOBAL "/usr/lib/x86_64-linux-gnu/libSDL2_ttf.a")

add_executable(tetris main.cpp gameRenderer.cpp gameRenderer.h playfield.cpp playfield.h activeBlock.cpp activeBlock.h blockDefs.h utils.h ${SDL_HEADERS})

target_include_directories(tetris PRIVATE ${SDL_HEADER_LOCATION})

#target_compile_options(tetris PRIVATE -lSDL2_ttf)

target_link_libraries(tetris PRIVATE ${SDL2_LIB} ${SDL2_TTF_LIB} SDL2_ttf)

install(TARGETS tetris RUNTIME DESTINATION bin)
