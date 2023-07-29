//
// Created by EQUIPO on 25/07/2023.
//

#ifndef JUEGOC___PLATAFORMA_H
#define JUEGOC___PLATAFORMA_H
#include <SFML/Graphics.hpp>

class Plataforma {
private:
    sf::Vector2f position; //Posicion de la plataforma
    float width; //Ancho de la plataforma
    float height; //Alto de la plataforma
    sf::Texture *textura; //Textura para la plataforma
    sf::Sprite *sprite; //Sprite de la plataforma
public:
    sf::Vector2f getPosition() const {
        return position;
    }
    Plataforma(sf::Vector2f position, float width, float height); //Constructor de plataforma
    void Draw(sf::RenderWindow& window);
    sf::FloatRect obtenerBound();
};



#endif //JUEGOC___PLATAFORMA_H
