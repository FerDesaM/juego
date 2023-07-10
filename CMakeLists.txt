cmake_minimum_required(VERSION 3.23)
project(juegoc__)

set(CMAKE_CXX_STANDARD 17)
add_executable(juegoc__ main.cpp game.h game.cpp projectile.cpp projectile.h cuadrado.h rectangulo.h "crear juego.cpp" "crear juego.h")
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics audio window network system)

add_definitions(-DSDL_MAIN_HANDLED)

target_link_libraries(juegoc__
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
        )