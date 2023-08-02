//
// Created by EQUIPO on 1/08/2023.
//

#ifndef JUEGOC___COMPPERSONAJE_H
#define JUEGOC___COMPPERSONAJE_H

#include "Componente.h"

class CompPersonaje: public Componente{
private:
    bool estaSobrePlataforma;
    float anguloDisparo;
    sf::Vector2f vectorDireccionDisparo;
public:
    ///Constructor Clase Personaje
    CompPersonaje(sf::Vector2f posInicial, float ancho, float alto,
                   const std::string& rutaTextura, int divX, int divY)
            : Componente(posInicial,ancho,alto,rutaTextura,divX, divY){
        velocidadMovimiento = 5.f;
    }
    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite del personaje
        window.draw(*this->sprite);
    };
};

#endif //JUEGOC___COMPPERSONAJE_H
