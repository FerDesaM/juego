//
// Created by EQUIPO on 26/07/2023.
//

#include "ExplosionProyectil.h"

ExplosionProyectil::ExplosionProyectil(sf::Vector2f position, float tamanio):position(position),tamanio(tamanio) {
    //Establecer texturas y sprites de la plataforma
    textura = new sf::Texture;
    textura->loadFromFile("../images/Explosion.png");
    //Division de la imagen
    divisionsprite.x=4;
    divisionsprite.y=2;
    frame_actual.x=0;
    frame_actual.y=0;


    sprite = new sf::Sprite;
    sprite->setTexture(*textura);

    //Calcular ancho y alto de la imagen
    float anchoFrame = textura->getSize().x/ divisionsprite.x;
    float altoFrame = textura->getSize().y/ divisionsprite.y;

    //Redefinir centro de coordenads del personaje
    sprite->setOrigin(anchoFrame/2,altoFrame/2);
    //Scalar plataforma para ajustar al ancho y alto establecidos
    sprite->scale(tamanio/anchoFrame,tamanio/altoFrame);

    //Colocar sprite en posicion inicial
    sprite->setPosition(position);
}

void ExplosionProyectil::Draw(sf::RenderWindow& window){
    clock.restart();
    if (clock.getElapsedTime().asSeconds() >= frameTime) {
        //Actualizar frame
        sf::IntRect rectangulo(frame_actual.x * (sprite->getTexture()->getSize().x / divisionsprite.x),
                               frame_actual.y * (sprite->getTexture()->getSize().y / divisionsprite.y),
                               sprite->getTexture()->getSize().x / divisionsprite.x,
                               sprite->getTexture()->getSize().y / divisionsprite.y);
        sprite->setTextureRect(rectangulo);
        clock.restart();
    }
    window.draw(*sprite);
}