//
// Created by EQUIPO on 17/07/2023.
//

#include "Proyectil.h"
#include <cmath>

Proyectil::Proyectil(sf::Vector2f posicionIncial, sf::Vector2f velocidadInicial):posicion(posicionIncial),velocidad(velocidadInicial){
    //Establecer textura y sprite del proyectil
    textura1 = new sf::Texture;
    textura1->loadFromFile("../images/R.png");
    sprite1 = new sf::Sprite;
    sprite1->setTexture(*textura1);
    //Scalar sprite
    diametro = 50.f;
    sprite1->scale(diametro/sprite1->getTexture()->getSize().x,diametro/sprite1->getTexture()->getSize().y);
    //Cambiar las coordenadas locales del sprite al centro del sprite
    sprite1->setOrigin(sprite1->getTexture()->getSize().x/2,sprite1->getTexture()->getSize().y/2);

    //Establecer propiedades geometrical del proyectil
    //circulo.setRadius(10.f);
    //circulo.setFillColor(sf::Color::Yellow);
}

void Proyectil::AplicarAceleracion(float deltaTime, sf::Vector2f aceleracion) {
    //Actualizar posiciones de los proyectiles
    velocidad += aceleracion * deltaTime;
    posicion += velocidad * deltaTime; // Actualiza la posición del proyectil según la velocidad
    //circulo.setPosition(posicion);
    sprite1->setPosition(posicion); // Aplica la posición al sprite
    // Calcula el ángulo de la velocidad
    float angle = std::atan2(velocidad.y, velocidad.x);
    // Convierte el ángulo de radianes a grados
    angle = angle * 180.f / static_cast<float>(M_PI);
    sprite1->setRotation(angle);
}

void Proyectil::Draw(sf::RenderWindow& window) {
    //window.draw(circulo);
    window.draw(*sprite1);
}