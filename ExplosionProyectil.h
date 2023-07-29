//
// Created by EQUIPO on 26/07/2023.
//

#ifndef JUEGOC___EXPLOSIONPROYECTIL_H
#define JUEGOC___EXPLOSIONPROYECTIL_H
#include <SFML/Graphics.hpp>

class ExplosionProyectil {
private:
    sf::Vector2f position; //Posicion de la explosion
    float tamanio; //Tmanio explosion cuadrada
    sf::Texture *textura; //Textura para la plataforma
    sf::Sprite *sprite; //Sprite de la plataforma
    sf::Vector2i divisionsprite; //Division de texturas para sprite
    sf::Vector2i frame_actual;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame de la animación (ajústalo según tu necesidad)
    bool realcontacto;
public:
    ExplosionProyectil() = default;
    ExplosionProyectil(sf::Vector2f position, float tamanio); //Constructor de plataforma
    void Draw(sf::RenderWindow& window);
    void setContact(bool contacto);
    void updatePosition(const sf::Vector2f& newPosition);
};


#endif //JUEGOC___EXPLOSIONPROYECTIL_H
