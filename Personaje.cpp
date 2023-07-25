//
// Created by EQUIPO on 17/07/2023.
//

#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "VectorUtil.h"
#include <cmath>
#include <iostream>

//Implementacion de Constructor
Personaje::Personaje(sf::Vector2f position, float width, float height, sf::Color color)
        : position(position), width(width), height(height), movementSpeed(5.f) {
    //Establecer angulo Inicial

    vectorDireccionDisparo = sf::Vector2f(1.0,-1.0);
    //vectorDireccionDisparo = VectorUtil::normalizarVector(vectorDireccionDisparo);
    anguloDisparo = VectorUtil::getAngleWithXAxis(vectorDireccionDisparo);
    //std::cout<<anguloDisparo<<std::endl;

    //Establecer texturas y sprites del Personaje
    textura1 = new sf::Texture;
    textura1->loadFromFile("../images/cocodrilo.png");
    //Division de la imagen
    divisionsprite.x=4;
    divisionsprite.y=2;
    frame_actual.x=0;
    frame_actual.y=0;
    //Creacion del sprite
    sprite1 = new sf::Sprite;
    sprite1->setTexture(*textura1);
    //Calcular ancho y alto de un frame
    float anchoFrame = textura1->getSize().x / divisionsprite.x;
    float altoFrame = textura1->getSize().y / divisionsprite.y;
    //Redefinir centro de coordenads del personaje
    sprite1->setOrigin(anchoFrame/2,altoFrame/2);
    //Scalar sprite para ajustar al ancho y alto establecidos
    sprite1->scale(width/anchoFrame,height/altoFrame);

    //Colocar sprite en posicion inicial
    sprite1->setPosition(position);


    //Sprite de flecha apuntadora
    texturaFlecha = new sf::Texture;
    texturaFlecha->loadFromFile("../images/canion.png");
    spriteFlecha = new sf::Sprite;
    spriteFlecha->setTexture(*texturaFlecha);
    //Redefinir centro de coordenads de la flecha
    spriteFlecha->setOrigin(0.0,spriteFlecha->getTexture()->getSize().y/2);
    //Scalar sprite para ajustar al ancho y alto establecidos
    spriteFlecha->scale(100.0/spriteFlecha->getTexture()->getSize().x,100.0/spriteFlecha->getTexture()->getSize().y);
    spriteFlecha->setPosition(position);
    spriteFlecha->setRotation(anguloDisparo);

/*
    //Circulo de Pruebas de ubicacion Personaje
    circulo = new sf::CircleShape(20.0);
    circulo->setOrigin(20.0,20.0);
    circulo->setPosition(position);
    circulo->setFillColor(sf::Color(255,255,0,255));*/

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
void Personaje::Disparar(std::vector<Proyectil> &projectiles, sf::Vector2f velocidadInicial) {
    //Posicion de lazamiento de la bala
    sf::Vector2f r0(position.x, position.y);
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
    //Dibujo de proyectiles lanzados por el personaje
    for (auto& bala : proyectiles2) {
        bala.AplicarAceleracion(deltaTime,aceleracion);
        bala.Draw(window);
    }

    //Dibujo del Sprite del personaje
    window.draw(*sprite1);

    //Dubujo circulo Ubicacion ( borrar)
    //window.draw(*circulo);

    //Dibujo de flecha de angulo
    window.draw(*spriteFlecha);


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
        //Definir Fuerza de lanzamiento
        float fuerzaLanzamiento = 50.f;
        sf::Vector2f v0 = fuerzaLanzamiento*vectorDireccionDisparo; // Velocidad inicial del proyectil ( se supone que el vector direccion debe estar normalizado)
        this->Disparar(proyectiles2, v0);
    }
}

void Personaje::moveUp() {
    float incremento = -1;
    if(frame_actual.y == 1)
        incremento *=-1;
    //Incrementar 1 grado la direccion de disparo
    VectorUtil::incrementarAnguloAVector(vectorDireccionDisparo,incremento);
    //anguloDisparo -= 1.0;
    ActualizarPosicion();
}

void Personaje::moveDown() {
    float incremento = 1;
    if(frame_actual.y == 1)
        incremento *=-1;
    VectorUtil::incrementarAnguloAVector(vectorDireccionDisparo,incremento);
    //anguloDisparo += 1.0;
    ActualizarPosicion();
}

void Personaje::moveLeft() {
    if (frame_actual.y != 1){
        frame_actual.y = 1;
        vectorDireccionDisparo = VectorUtil::reflejarVector(vectorDireccionDisparo,sf::Vector2f(0,1));
    }
    else{
        frame_actual.x++;
        if (frame_actual.x == divisionsprite.x){
            frame_actual.x =0;
        }
        position.x -= movementSpeed;
    }
    ActualizarPosicion();
    RefreshAnimacion();
}

void Personaje::moveRight() {
    if (frame_actual.y != 0){
        frame_actual.y = 0;
        vectorDireccionDisparo = VectorUtil::reflejarVector(vectorDireccionDisparo,sf::Vector2f(0,1));
    }
    else{
        frame_actual.x++;
        if (frame_actual.x == divisionsprite.x){
            frame_actual.x =0;
        }
        position.x += movementSpeed;
    }
    ActualizarPosicion();
    RefreshAnimacion();
}

void Personaje::ActualizarPosicion(){
    sprite1->setPosition(position);
    spriteFlecha->setPosition(position);
    anguloDisparo = VectorUtil::getAngleWithXAxis(vectorDireccionDisparo);
    spriteFlecha->setRotation(anguloDisparo);
}

Personaje *Prota::crearPersonaje(sf::Vector2f position, const sf::Color &color) {
    Text=new sf::Texture;
    Text->loadFromFile("../images/mariobros.png");
    Personaje* personaje1=new Personaje(position,500.f,500.f,color);
    personaje1->setTexture(Text);
    return personaje1;
}