//
// Created by EQUIPO on 17/07/2023.
//

#ifndef JUEGOC___PROYECTIL_H
#define JUEGOC___PROYECTIL_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Plataforma.h"
#include <cmath>

class Proyectil {
private:
    float diametro; //Diametro del proyectil
    sf::Vector2f posicion; //Posicion actual del proyectil
    sf::Vector2f velocidad; //Velocidad actual del proyectil
    sf::Texture *textura1; //Textur para sprite del proyectil
    sf::Sprite *sprite1; //Sprite del proyectil
    bool estaExplotado; //

public:
    Proyectil(sf::Vector2f posicionIncial, sf::Vector2f velocidadInicial); //Constructor a partir de posicion y velocidad inicial
    void AplicarAceleracion(float deltaTime, sf::Vector2f aceleracion, std::vector<Plataforma> plataformas); //Aplicar aceleracion en un deltaTime
    void Draw(sf::RenderWindow& window);//Dibujar en ventana
};


#endif //JUEGOC___PROYECTIL_H
