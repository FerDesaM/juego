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
#include "ExplosionProyectil.h"
class Personaje;
class Proyectil {
private:
    float diametro; //Diametro del proyectil
    sf::Vector2f posicion; //Posicion actual del proyectil
    sf::Vector2f velocidad; //Velocidad actual del proyectil
    sf::Texture *textura1; //Textur para sprite del proyectil
    sf::Sprite *sprite1; //Sprite del proyectil
    bool estaExplotado; //
    ExplosionProyectil explosion;
    float tiempoExplosion;
    bool eliminar;
public:
    Proyectil(sf::Vector2f posicionIncial, sf::Vector2f velocidadInicial); //Constructor a partir de posicion y velocidad inicial
    void AplicarAceleracion(float deltaTime, sf::Vector2f aceleracion, std::vector<Plataforma> plataformas); //Aplicar aceleracion en un deltaTime
    void Draw(sf::RenderWindow& window);//Dibujar en ventana
    sf::Vector2f getPosition() const;
    bool colisionaConPersonaje(Personaje& personaje);
    bool estaExplotado2() const {
        return estaExplotado;
    }
    bool isEliminar() const {
        return eliminar;
    }

    void setEliminar(bool value) {
        eliminar = value;
    }
};


#endif //JUEGOC___PROYECTIL_H
