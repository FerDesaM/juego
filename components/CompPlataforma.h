//
// Created by EQUIPO on 1/08/2023.
//

#ifndef JUEGOC___COMPPLATAFORMA_H
#define JUEGOC___COMPPLATAFORMA_H
#include "Componente.h"

class CompPlataforma: public Componente{
public:
    ///Constructor Clase Plataforma
    CompPlataforma(sf::Vector2f posInicial, float ancho, float alto,
                   const std::string& rutaTextura, int divX, int divY)
            : Componente(posInicial,ancho,alto,rutaTextura,divX, divY){
        //Implementar constructor Plataforma
    }
    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite del personaje
        window.draw(*this->sprite);
    };
};
#endif //JUEGOC___COMPPLATAFORMA_H
