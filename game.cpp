#include "game.h"
#include "cuadrado.h"
#include <type_traits>
Juego::Juego(int ancho, int largo, const std::string& titulo) {
    int fps = 60;
    ventana = new sf::RenderWindow(sf::VideoMode(ancho, largo), titulo);
    ventana->setFramerateLimit(fps);
    projectile=new Projectile(10.f,50.f,9.8f);
    projectile->setPosition(sf::Vector2f(100.f, 100.f)); // Posición inicial
    projectile->setWindowBounds(sf::Vector2f(ancho, largo));
    float cuadradoX = 200.f;
    float cuadradoY = 200.f;
    float cuadradoWidth = 50.f;
    float cuadradoHeight = 50.f;
    //comprobamos si lo que compone al cuadrado es igual a un tipo flotante
    static_assert(is_same_v<decltype(cuadradoX),float>,"no es igual");
    static_assert(is_same_v<decltype(cuadradoY),float>,"no es igual");
    static_assert(is_same_v<decltype(cuadradoWidth),float>,"no es igual");
    static_assert(is_same_v<decltype(cuadradoHeight),float>,"no es igual");
    cuadrado = new Cuadrado(sf::Vector2f ( cuadradoX,cuadradoY),sf::Vector2f(cuadradoWidth, cuadradoHeight));
}


void Juego::Dibujar() {
    ventana->clear(sf::Color::Blue);
    ventana->draw(projectile->getShape());
    ventana->draw(cuadrado->getShape());
    ventana->display();
}
void Juego::GameLoop() {
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    bool isProjectileMoving = false;

    while (ventana->isOpen()) {
        sf::Time currentTime = clock.getElapsedTime();
        sf::Time deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        sf::Event evento;
        while (ventana->pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana->close();

            if (evento.type == sf::Event::MouseButtonPressed) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f clickPosition = sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y);
                    sf::Vector2f velocity = clickPosition - projectile->getPosition();
                    projectile->fire(projectile->getPosition(), velocity);
                    isProjectileMoving = true;
                }
            }
        }

        if (isProjectileMoving) {
            projectile->update(deltaTime.asSeconds());

            // Verificar colisiones con las paredes de la ventana
            if (projectile->getPosition().x <= 0 || projectile->getPosition().x >= ventana->getSize().x) {
                projectile->setVelocity(sf::Vector2f(-projectile->getVelocity().x, projectile->getVelocity().y));
            }
            if (projectile->getPosition().y <= 0 || projectile->getPosition().y >= ventana->getSize().y) {
                projectile->setVelocity(sf::Vector2f(projectile->getVelocity().x, -projectile->getVelocity().y));
            }

            // Verificar colisión con el cuadrado
            if (cuadrado->checkCollision(projectile->getBounds())) {
                // Invertir la dirección del proyectil
                projectile->setVelocity(-projectile->getVelocity());
            }
        }

        ventana->clear();
        projectile->draw(*ventana);
        ventana->draw(cuadrado->getShape());
        ventana->display();
    }
}






// Created by Fernando on 23/06/2023.
//
