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
    textura1->loadFromFile("../images/megaman.png");
    //Division de la imagen
    divisionsprite.x=5;
    divisionsprite.y=2;
    frame_actual.x=0;
    frame_actual.y=0;
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
    sf::IntRect rectangulo(frame_actual.x * (sprite1->getTexture()->getSize().x / divisionsprite.x),
                           frame_actual.y * (sprite1->getTexture()->getSize().y / divisionsprite.y),
                           sprite1->getTexture()->getSize().x / divisionsprite.x,
                           sprite1->getTexture()->getSize().y / divisionsprite.y);
    sprite1->setTextureRect(rectangulo);
}
void Personaje::setTexture(sf::Texture *texture) {
    sprite1->setTexture(*texture);

}
void Personaje::Disparar(std::vector<Proyectil> &projectiles, sf::Vector2f direction, sf::Vector2f velocidadInicial) {
    //Posicion de lazamiento de la bala
    sf::Vector2f r0(position.x + width, position.y + height / 2.f);
    //Geometria del proyectil
    Proyectil bala(r0,velocidadInicial);
    projectiles.push_back(bala);
}/*
void Personaje::moverCamara(sf::RenderWindow &window,sf::Vector2f limiteMundo) {
    sf::Vector2f camaraPosition = position - sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

    // Asegurarse de que la cámara no salga de los límites del mundo
    if (camaraPosition.x < 0) {
        camaraPosition.x = 0;
    }
    if (camaraPosition.y < 0) {
        camaraPosition.y = 0;
    }
    if (camaraPosition.x > limiteMundo.x - window.getSize().x) {
        camaraPosition.x = limiteMundo.x - window.getSize().x;
    }
    if (camaraPosition.y > limiteMundo.y - window.getSize().y) {
        camaraPosition.y = limiteMundo.y - window.getSize().y;
    }

    // Establecer la vista de la cámara en la ventana
    sf::View camaraView(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
    camaraView.setCenter(camaraPosition);
    window.setView(camaraView);
}*/
sf::Vector2f Personaje::getPosition() const {
    return position;
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

void Personaje::ResponderEvento(sf::Event event,float deltaTime){
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
    frame_actual.x++;

    // Set the frame row for the "up" animation (adjust this if needed)

}

void Personaje::moveDown() {
    position.y += movementSpeed;
    sprite1->setPosition(position);
    frame_actual.y++;

}

void Personaje::moveLeft() {
    position.x -= movementSpeed;
    sprite1->setPosition(position);

}

void Personaje::moveRight() {
    if (frame_actual.x < divisionsprite.x - 1) {
        frame_actual.x++;
    } else {
        // Si se alcanzó la última columna de la primera fila, avanzar a la primera columna de la segunda fila
        frame_actual.x = 0;
        frame_actual.y = (frame_actual.y == 0) ? 1 : 0; // Cambiar entre las dos filas
    }

    // Mover el personaje con cada incremento en el índice de la columna actual
    position.x += movementSpeed * (frame_actual.x + 1);
    sprite1->setPosition(position);
    RefreshAnimacion();
}
Personaje *Prota::crearPersonaje(sf::Vector2f position, const sf::Color &color) {
    Text=new sf::Texture;
    Text->loadFromFile("../images/mariobros.png");
    Personaje* personaje1=new Personaje(position,100.f,100.f,color);
    personaje1->setTexture(Text);
    return personaje1;
}