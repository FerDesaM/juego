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
        : position(position), width(width), height(height), movementSpeed(5.f),
        estaSobrePlataforma(false) {
    //Establecer direccion disparo inicial
    vectorDireccionDisparo = sf::Vector2f(1.0,-1.0);
    anguloDisparo = VectorUtil::getAngleWithXAxis(vectorDireccionDisparo);

    //Establecer texturas y sprites del Personaje
    textura1 = new sf::Texture;
    textura1->loadFromFile("../images/cocodrilo.png");
    //Division de la imagen
    divisionsprite = sf::Vector2i (4,2);
    frame_actual = sf::Vector2i (0,0);
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
}

sf::Vector2f Personaje::getPosition() const {
    return position;
}

void Personaje::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f aceleracion,std::vector<Plataforma> plataformas) {
    //Dibujo de proyectiles lanzados por el personaje
    for (auto& bala : proyectiles2) {
        bala.AplicarAceleracion(deltaTime,aceleracion,plataformas);
        bala.Draw(window);
    }

    //Dibujo del Sprite del personaje
    window.draw(*sprite1);

    //Dibujo de flecha de angulo
    window.draw(*spriteFlecha);
}

void Personaje::ResponderEvento(sf::Event event,CompBarraPoder barra){

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        this->moveUp();
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        this->moveDown();
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        this->moveLeft();
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        this->moveRight();
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {

    }
    else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
    {

        //Definir Fuerza de lanzamiento
        float fuerzaLanzamiento = barra.getProgreso(); //Esta es la fuerza de disparo, falta definir un valor maximo y una barra
        sf::Vector2f v0 = fuerzaLanzamiento*vectorDireccionDisparo; // Velocidad inicial del proyectil ( se supone que el vector direccion debe estar normalizado)
        this->Disparar(proyectiles2, v0);
    }
    else if (event.key.code == sf::Keyboard::Space){
        //Definir Fuerza de lanzamiento
        float fuerzaLanzamiento = 50.f; //Esta es la fuerza de disparo, falta definir un valor maximo y una barra
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

void Personaje::AplicarGravedad(float deltaTime, sf::Vector2f gravedad,
                                std::vector<Plataforma> plataformas) {
    // Aplicar la gravedad a la velocidad actual del personaje
    sf::Vector2f velocidad = gravedad * deltaTime;
    // Actualizar la posición del personaje con la nueva velocidad
    position += velocidad;

    // Guardar el estado anterior de estar sobre una plataforma
    bool estabaSobrePlataformaPrevio = estaSobrePlataforma;

    // Comprobar si el personaje está sobre una plataforma
    estaSobrePlataforma = false;
    for (auto& plataforma : plataformas) {
        sf::FloatRect contornoPlataforma = plataforma.obtenerBound();
        if (contornoPlataforma.intersects(sprite1->getGlobalBounds())) {
            estaSobrePlataforma = true;
            break;
        }
    }

    // Si el personaje está sobre una plataforma, detener su caída y posicionarlo en la plataforma
    if (estaSobrePlataforma) {
        // Obtener la posición del personaje
        sf::Vector2f personajePosition = plataformas[0].getPosition();

        // Colocar al personaje encima de la plataforma
        position.y = personajePosition.y - height / 2;
    }

    // Actualizar la posición del sprite del personaje
    sprite1->setPosition(position);

    // Si estaba sobre una plataforma y ahora no lo está, actualizar la animación para que mire hacia abajo
    if (estabaSobrePlataformaPrevio && !estaSobrePlataforma) {
        frame_actual.y = 1;
        RefreshAnimacion();
    }
}

Personaje *Prota::crearPersonaje(sf::Vector2f position, const sf::Color &color) {
    Text=new sf::Texture;
    Text->loadFromFile("../images/gatopsicopata.png");
    Personaje* personaje1=new Personaje(position,100.f,200.f,color);
    personaje1->setTexture(Text);
    return personaje1;
}