//
// Created by EQUIPO on 17/07/2023.
//

#ifndef JUEGOC___PERSONAJE_H
#define JUEGOC___PERSONAJE_H

#include "Proyectil.h"
#include <vector>
#include "Plataforma.h"
#include "components/CompBarraPoder.h"

//Utilizar el abstract factory para crear distintos tipos de personajes
class Personaje {
private:
    sf::Vector2f position; //Posicion del sprite
    float width; //Ancho del personaje
    float height; //Alto del personaje
    float movementSpeed; //Velocidad de movimiento del personaje
    bool estaSobrePlataforma;

    //Angulo de disparo
    float anguloDisparo;
    sf::Vector2f vectorDireccionDisparo;

    sf::Texture *textura1; //Textura para sprite del personaje
    sf::Texture *texturaFlecha; //Textura para sprite del personaje
    sf::Sprite *sprite1; //Sprite del personaje
    sf::Sprite *spriteFlecha; //Sprite de la flecha apuntadora
    sf::Vector2i divisionsprite; //Division de texturas para sprite
    sf::RectangleShape rectangle;
    std::vector<Proyectil> proyectiles2;
    sf::Vector2i frame_actual;
    float deltaTime;
    float tiempoAcumulado;
    sf::Clock frameClock;

    //Prueba Ciruclo
    sf::CircleShape *circulo;

public:
    Personaje(sf::Vector2f position, float width, float height, sf::Color color); //Constructor
    void Disparar(std::vector<Proyectil>& projectiles, sf::Vector2f velocidadInicial);
    void RefreshAnimacion();
    //void moverCamara(sf::RenderWindow & window,sf::Vector2f limiteMundo);
    void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f aceleracion,std::vector<Plataforma> plataformas);
    void setTexture(sf::Texture * texture);
    sf::Vector2f getPosition() const;
    //Movimiento Personaje
    void ResponderEvento(sf::Event event,CompBarraPoder barra);
    void ResponderEvento2(sf::Event event,float deltaTime);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void ActualizarPosicion();
    void AplicarGravedad(float deltaTime, sf::Vector2f gravedad,std::vector<Plataforma> plataformas);

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
