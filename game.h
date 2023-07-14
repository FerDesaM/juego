//
// Created by Fernando on 23/06/2023.
//

#ifndef JUEGOC___GAME_H
#define JUEGOC___GAME_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include<memory>
#include "projectile.h"
#include "cuadrado.h"
using namespace std;
using namespace sf;

class Juego {
private:
    //Se hace uso del puntero unico para la liberacion de memoria
    sf::RenderWindow* ventana;
    std::unique_ptr<Projectile> projectile;
    std::unique_ptr<sf::Texture> texture1;
    std::unique_ptr<Sprite> sprite1;
    std::unique_ptr<Texture> texture2;
    std::unique_ptr<Sprite> mapa;
    std::unique_ptr<Cuadrado<float>> cuadrado;
    std::unique_ptr<Cuadrado<float>> cuadrado2;
    std::unique_ptr<Event> evento;
    sf::Vector2i divisionsprite;

public:
    Juego(int ancho, int largo, const std::string& titulo);
    void Dibujar();
    void GameLoop();
    void Evento();
    void Colisiones();
    void Cargar_recursos();
    void actualizar_animacion(Sprite&);
};


#endif //JUEGOC___GAME_H
