cmake_minimum_required(VERSION 3.23)
project(JuegoFinal)

set(CMAKE_CXX_STANDARD 17)
add_executable(JuegoFinal main.cpp game.h game.cpp projectile.cpp projectile.h cuadrado.h
        Personaje.h
        Personaje.cpp
        Proyectil.h Proyectil.cpp VectorUtil.cpp VectorUtil.h)
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics audio window network system)

add_definitions(-DSDL_MAIN_HANDLED)

target_link_libraries(JuegoFinal
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
        )