//
// Created by EQUIPO on 17/07/2023.
//

#include "Proyectil.h"

Proyectil::Proyectil(sf::Vector2f posicionIncial, sf::Vector2f velocidadInicial):
        posicion(posicionIncial),tiempoExplosion(2.0f),velocidad(velocidadInicial),estaExplotado(false),
        explosion(posicionIncial, 100.f){
    //Establecer textura y sprite del proyectil
    textura1 = new sf::Texture;
    textura1->loadFromFile("../images/R.png");
    sprite1 = new sf::Sprite;
    sprite1->setTexture(*textura1);
    //Scalar sprite
    diametro = 50.f;
    sprite1->scale(diametro/sprite1->getTexture()->getSize().x,diametro/sprite1->getTexture()->getSize().y);
    //Cambiar las coordenadas locales del sprite al centro del sprite
    sprite1->setOrigin(sprite1->getTexture()->getSize().x/2,sprite1->getTexture()->getSize().y/2);

}
sf::Vector2f Proyectil::getPosition() const {
    return posicion;
}void Proyectil::AplicarAceleracion(float deltaTime, sf::Vector2f aceleracion, std::vector<Plataforma> plataformas) {
    // Actualizar posiciones de los proyectiles
    velocidad += aceleracion * deltaTime;
    posicion += velocidad * deltaTime; // Actualiza la posición del proyectil según la velocidad

    // Verificar si el proyectil impacta con plataforma
    bool impactoConPlataforma = false;
    if (!estaExplotado) {
        for (auto& plataforma : plataformas) {
            // Obtener bound de plataforma
            sf::FloatRect contornoPlataforma = plataforma.obtenerBound();
            if (contornoPlataforma.contains(posicion)) {
                impactoConPlataforma = true;
                break;
            }
        }
    }

    // Si el proyectil impacta con la plataforma, explotar
    if (impactoConPlataforma) {
        estaExplotado = true;
        explosion.setContact(true);
        // Actualizar la posición de la explosión al punto de impacto del proyectil
        explosion.updatePosition(posicion);
    }

    // Si tiempoExplosion <= 0, el proyectil debe explotar
    if (tiempoExplosion <= 0.0f) {
        estaExplotado = true;
        explosion.setContact(true);
        // Actualizar la posición de la explosión al final del recorrido del proyectil
        explosion.updatePosition(posicion);
    }

    // Si debe explotar, disminuir el tiempoExplosion
    if (estaExplotado) {
        tiempoExplosion -= deltaTime;
    }

    // Si no ha explotado, actualiza la posición del sprite del proyectil
    if (!estaExplotado) {
        sprite1->setPosition(posicion); // Aplica la posición al sprite
    }

    // Calcula el ángulo de la velocidad
    float angle = std::atan2(velocidad.y, velocidad.x);
    // Convierte el ángulo de radianes a grados
    angle = angle * 180.f / static_cast<float>(M_PI);
    sprite1->setRotation(angle);
}
void Proyectil::Draw(sf::RenderWindow& window) {
    if (!estaExplotado) {
        window.draw(*sprite1);
    }
    else {
        explosion.Draw(window);
    }
}