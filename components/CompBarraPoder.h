//
// Created by EQUIPO on 1/08/2023.
//

#ifndef JUEGOC___COMPBARRAPODER_H
#define JUEGOC___COMPBARRAPODER_H
#include "Componente.h"

class CompBarraPoder{
private:
    sf::RectangleShape rectBarraProgreso;
    sf::RectangleShape rectBorde;
    float progreso; //Va de 0 a 100
    bool seLleno;
public:
    ///Constructor de BarraProgreso
    CompBarraPoder(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color borderColor)
    : progreso(0.0f), seLleno(false)
    {
        rectBarraProgreso.setPosition(position);
        rectBarraProgreso.setSize(size);
        rectBarraProgreso.setFillColor(fillColor);

        rectBorde.setPosition(position);
        rectBorde.setSize(size);
        rectBorde.setFillColor(sf::Color::Transparent);
        rectBorde.setOutlineColor(borderColor);
        rectBorde.setOutlineThickness(2.0f);
    }

    ///Funcion geter para obtener el progreso
    float getProgreso(){
        return this->progreso;
    }
    ///Función para dibujar la barra de progreso
    void Draw(sf::RenderWindow& window){
        if (progreso > 0)
        {
            sf::RectangleShape progressRect(rectBarraProgreso);
            //Obtener relacion
            float relacion = progreso / 100.0f;
            progressRect.setSize(sf::Vector2f(rectBarraProgreso.getSize().x * relacion, rectBarraProgreso.getSize().y));
            window.draw(progressRect);
        }
        window.draw(rectBorde);
    }

    ///Función para responder a eventos
    void ResponderEvento(sf::Event event){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            if (seLleno) //Si detecta que ya se lleno previamente. reinica el progreso
            {
                this->progreso = 0.0f;
            }
            this->progreso+=1.0; //Condifurar incremento, es la Velocidad del progressBar
            if (progreso >= 100.f)
                this->progreso = 100.0f;
            seLleno = false; //Mientras se este apretando la barra espaciadora selleno es falso
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        {
            seLleno = true; //Una vez se suelta la barra espaciadora "selleno" es true
        }
    }
};

#endif //JUEGOC___COMPBARRAPODER_H
