//
// Created by Fernando on 23/06/2023.
//

#ifndef JUEGOC___GAME_H
#define JUEGOC___GAME_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include "projectile.h"
#include "cuadrado.h"
using namespace std;
using namespace sf;
class Juego {
private:
    sf::RenderWindow* ventana;
    Projectile* projectile;
    Cuadrado* cuadrado;
public:
    Juego(int ancho, int largo, const std::string& titulo);
    void Dibujar();
    void GameLoop();

};


#endif //JUEGOC___GAME_H
