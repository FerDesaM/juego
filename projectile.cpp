#include "projectile.h"

Projectile::Projectile(float radius, float speed, float gravity){
    pro.setRadius(radius);
    pro.setFillColor(sf::Color::Red);
    this->gravity=gravity;
}
void Projectile::setPosition(sf::Vector2f position) {
    this->position = position;
    pro.setPosition(position);
}

void Projectile::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
}

void Projectile::setWindowBounds(sf::Vector2f windowSize) {
    windowBounds = windowSize;
}

void Projectile::update(float deltaTime) {
    // Aplica la gravedad a la velocidad del proyectil
    velocity.y += gravity * deltaTime;

    // Actualiza la posición del proyectil según la velocidad
    position += velocity * deltaTime;

    // Comprueba si el proyectil ha llegado al suelo o colisionado con los límites de la ventana
    if (position.y + pro.getRadius() >= windowBounds.y) {
        // Reinicia la posición y la velocidad del proyectil
        position.y = windowBounds.y - pro.getRadius();
        velocity.y = -velocity.y * 0.8f; // Rebote con pérdida de energía
    }

    pro.setPosition(position);
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(pro);
}

bool Projectile::checkCollision(sf::FloatRect bounds) {
    return pro.getGlobalBounds().intersects(bounds);
}


//
// Created by Fernando on 26/06/2023.
//
