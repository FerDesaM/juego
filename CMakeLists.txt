cmake_minimum_required(VERSION 3.23)
project(juegogithub)

set(CMAKE_CXX_STANDARD 17)
add_executable(juegogithub main.cpp game.h game.cpp projectile.cpp projectile.h cuadrado.h )
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics audio window network system)

add_definitions(-DSDL_MAIN_HANDLED)

target_link_libraries(juegogithub
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
        )