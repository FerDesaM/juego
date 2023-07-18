//
// Created by EQUIPO on 17/07/2023.
//

#include <SFML/Graphics.hpp>
#include "Personaje.h"

//Implementacion de Constructor
Personaje::Personaje(sf::Vector2f position, float width, float height, sf::Color color)
        : position(position), width(width), height(height), movementSpeed(5.f) {
    //Establecer textura y sprite
    textura1 = new sf::Texture;
    textura1->loadFromFile("../images/mariobros.png");
    //Division de la imagen
    divisionsprite.x=5;
    divisionsprite.y=4;
    //Creacion del sprite
    sprite1 = new sf::Sprite;
    sprite1->setTexture(*textura1);
    //Scalar sprite para ajustar al ancho y alto establecidos
    //sprite1->scale(width/sprite1->getTexture()->getSize().x,height/sprite1->getTexture()->getSize().y);
    //Colocar sprite en posicion inicial
    sprite1->setPosition(position);

    /*
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(position);
    rectangle.setFillColor(color);*/
}

void Personaje::RefreshAnimacion()
{
    sf::IntRect rectangulo(0, 0,
                           sprite1->getTexture()->getSize().x / divisionsprite.x,
                           sprite1->getTexture()->getSize().y / divisionsprite.y);
    sprite1->setTextureRect(rectangulo);
}

void Personaje::Disparar(std::vector<Proyectil> &projectiles, sf::Vector2f direction, sf::Vector2f velocidadInicial) {
    //Posicion de lazamiento de la bala
    sf::Vector2f r0(position.x + width, position.y + height / 2.f);
    //Geometria del proyectil
    Proyectil bala(r0,velocidadInicial);
    projectiles.push_back(bala);
}

void Personaje::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f aceleracion) {
    window.draw(*sprite1);
    //window.draw(rectangle);

    //
    for (auto& bala : proyectiles2) {
        bala.AplicarAceleracion(deltaTime,aceleracion);
        bala.Draw(window);

    }
}

void Personaje::ResponderEvento(sf::Event event){
    if (event.key.code == sf::Keyboard::Up)
        this->moveUp();
    else if (event.key.code == sf::Keyboard::Down)
        this->moveDown();
    else if (event.key.code == sf::Keyboard::Left)
        this->moveLeft();
    else if (event.key.code == sf::Keyboard::Right)
        this->moveRight();
    else if (event.key.code == sf::Keyboard::Space){
        sf::Vector2f direction(1.f, 1.f); // Dirección del proyectil (puedes ajustarla)
        sf::Vector2f v0(50.f, -50.f); // Velocidad inicial del proyectil
        this->Disparar(proyectiles2, direction, v0);
    }
}

void Personaje::moveUp() {
    position.y -= movementSpeed;
    sprite1->setPosition(position);
}

void Personaje::moveDown() {
    position.y += movementSpeed;
    sprite1->setPosition(position);
}

void Personaje::moveLeft() {
    position.x -= movementSpeed;
    sprite1->setPosition(position);
}

void Personaje::moveRight() {
    position.x += movementSpeed;
    sprite1->setPosition(position);
}


