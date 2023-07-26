//
// Created by EQUIPO on 25/07/2023.
//

#include "Plataforma.h"
//Implementacion de Constructor
Plataforma::Plataforma(sf::Vector2f position, float width, float height)
        : position(position), width(width), height(height){
    //Establecer texturas y sprites de la plataforma
    textura = new sf::Texture;
    textura->loadFromFile("../images/plataformaPrueba.png");
    sprite = new sf::Sprite;
    sprite->setTexture(*textura);

    //Calcular ancho y alto de la imagen
    float anchoFrame = textura->getSize().x;
    float altoFrame = textura->getSize().y;

    //Redefinir centro de coordenads del personaje
    sprite->setOrigin(anchoFrame/2,altoFrame/2);
    //Scalar plataforma para ajustar al ancho y alto establecidos
    sprite->scale(width/anchoFrame,height/altoFrame);

    //Colocar sprite en posicion inicial
    sprite->setPosition(position);
}

void Plataforma::Draw(sf::RenderWindow& window) {
    //Dibujo del Sprite de la plataforma
    window.draw(*sprite);
}

sf::FloatRect Plataforma::obtenerBound(){
    return sprite->getGlobalBounds();
}