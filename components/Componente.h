//
// Created by EQUIPO on 1/08/2023.
//

#ifndef JUEGOC___COMPONENTE_H
#define JUEGOC___COMPONENTE_H
#include <SFML/Graphics.hpp>
#include "../VectorUtil.h"
#include <cmath>
#include <iostream>

class Componente {
protected:
    sf::Vector2f posicion; //Posicion del sprite
    float anchoMostrado; //Ancho del componente
    float altoMostrado; //Alto del componente
    float anchoFrame;
    float altoFrame;
    float velocidadMovimiento; //Velocidad de movimiento del componente
    sf::Texture *textura; //Textura para el componente
    sf::Sprite *sprite; //Sprite del personaje
    sf::Vector2i divisionsprite; //Division de texturas para sprite
    sf::Vector2i frame_actual;
public:
    ///Constructor Clase Abstracta Componente
    Componente(sf::Vector2f posInicial, float ancho, float alto,
               const std::string& rutaTextura, int divX, int divY)
               : posicion(posInicial), anchoMostrado(ancho), altoMostrado(alto)
    {
            //Establecer texturas y sprites del Componente
            textura = new sf::Texture;
            textura->loadFromFile(rutaTextura);
            //Division de la imagen
            divisionsprite = sf::Vector2i (4,2);
            frame_actual = sf::Vector2i (0,0);
            //Creacion del sprite
            sprite = new sf::Sprite;
            sprite->setTexture(*textura);
            //Calcular ancho y alto de un frame
            anchoFrame = textura->getSize().x / divisionsprite.x;
            altoFrame = textura->getSize().y / divisionsprite.y;

            //Redefinir centro de coordenads del componente (al centro)
            sprite->setOrigin(anchoFrame/2,altoFrame/2);
            //Scalar sprite para ajustar al ancho y alto establecidos
            sprite->scale(ancho/anchoFrame,alto/altoFrame);

            //Colocar sprite en posicion inicial
            sprite->setPosition(posInicial);
    }

    ///Destructor Clase Componente
    virtual ~Componente()=default; //Destructor

    virtual void Draw(sf::RenderWindow& window) = 0; //Funcion virtual pura (sebe ser implementada por clases derivadas)
    ///Funcion virtual (puede ser sobreescrito en clases derivadas)
    virtual void ResponderEvento(sf::Event event){

    }
    ///Funcion No Virtual (no es candidato de sobreescritura en clases derivadas)
    sf::FloatRect ObtenerBound(){
        return sprite->getGlobalBounds();
    }

};

#endif //JUEGOC___COMPONENTE_H
