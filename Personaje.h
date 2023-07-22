//
// Created by EQUIPO on 17/07/2023.
//

#ifndef JUEGOC___PERSONAJE_H
#define JUEGOC___PERSONAJE_H

#include "Proyectil.h"
#include <vector>
//Utilizar el abstract factory para crear distintos tipos de personajes
class Personaje {
private:
    sf::Vector2f position; //Posicion del sprite
    float width; //Ancho del personaje
    float height; //Alto del personaje
    float movementSpeed; //Velocidad de movimiento del personaje
    sf::Texture *textura1; //Textura para sprite del personaje
    sf::Sprite *sprite1; //Sprite del personaje
    sf::Vector2i divisionsprite; //Division de texturas para sprite
    sf::RectangleShape rectangle;
    std::vector<Proyectil> proyectiles2;
    sf::Vector2i frame_actual;
    float deltaTime;
    float tiempoAcumulado;
    sf::Clock frameClock;
public:
    Personaje(sf::Vector2f position, float width, float height, sf::Color color); //Constructor
    void Disparar(std::vector<Proyectil>& projectiles, sf::Vector2f direction, sf::Vector2f velocidadInicial);
    void RefreshAnimacion();
    //void moverCamara(sf::RenderWindow & window,sf::Vector2f limiteMundo);
    void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f aceleracion);
    void setTexture(sf::Texture * texture);
    sf::Vector2f getPosition() const;
    //Movimiento Personaje
    void ResponderEvento(sf::Event event,float deltaTime);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};
class FabricaPersonaje{
public:
    virtual Personaje* crearPersonaje(sf::Vector2f position, const sf::Color& color)=0;
};
class Prota:public FabricaPersonaje{
private:
    sf::Texture* Text{};
    sf::Sprite *personaje{};

public:

    Personaje* crearPersonaje(sf::Vector2f position, const sf::Color& color) override;
};
#endif //JUEGOC___PERSONAJE_H
