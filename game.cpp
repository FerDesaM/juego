#include "game.h"
#include "cuadrado.h"
#include <type_traits>
#include<memory>
Juego::Juego(int ancho, int largo, const std::string& titulo) {
    int fps = 60;
    gravity = sf::Vector2f(0.f, 9.8f); // Gravedad (puedes ajustarla según tus necesidades)
    ventana = new sf::RenderWindow(sf::VideoMode(ancho, largo), titulo);
    ventana->setFramerateLimit(fps);
    //projectile=new Projectile(10.f,50.f,9.8f);
    //projectile->setPosition(sf::Vector2f(100.f, 100.f)); // Posición inicial
    // projectile->setWindowBounds(sf::Vector2f(ancho, largo));
    divisionsprite.x=5;
    divisionsprite.y=4;
    Cargar_recursos();
    evento= make_unique<Event>();
    GameLoop();
}

void Juego::GameLoop() {
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    bool isProjectileMoving = false;

    while (ventana->isOpen())
    {
        Evento();
        Dibujar();
        Colisiones();
    }
}

void Juego::Dibujar() {
    ventana->clear(sf::Color::Blue);
    // projectile->draw(*ventana);
    ventana->draw(*mapa);
    ventana->draw(*sprite1);
    ventana->draw(cuadrado->getShape());
    ventana->draw(cuadrado2->getShape());

    //Dibujar Personaje
    personaje1->Draw(*ventana,deltaTime,gravity);

    ventana->display();
}
void Juego::Evento()
{
    while(ventana->pollEvent(*evento))
    {
        switch (evento->type)
        {
            case Event::Closed:
                ventana->close();
                exit(1);
                break;
            case Event::KeyPressed:
                personaje1->ResponderEvento(*evento); //Responder evento de Personaje1
                break;
        }

    }
}
void Juego::Colisiones()
{



}
void Juego::actualizar_animacion(sf::Sprite& sprite)
{

    IntRect ubicacion(0, 0, sprite.getTexture()->getSize().x / divisionsprite.x, sprite.getTexture()->getSize().y / divisionsprite.y);
    sprite.setTextureRect(ubicacion);
}
void Juego::Cargar_recursos()
{
    cuadrado = std::make_unique<Cuadrado<float>>(sf::Vector2f(200.f, 200.f), sf::Vector2f(50.f, 50.f),Color::Blue);
    cuadrado2 = std::make_unique<Cuadrado<float>>(sf::Vector2f(0.f, 735.f), sf::Vector2f(1000.f, 50.f),Color::Red);
    texture1= std::make_unique<sf::Texture>();
    texture2= std::make_unique<sf::Texture>();
    sprite1=std::make_unique<sf::Sprite>();
    mapa=std::make_unique<sf::Sprite>();
    texture1->loadFromFile("../images/mariobros.png");
    texture2->loadFromFile("../images/mapa.jpg");
    sprite1->setTexture(*texture1);
    sprite1->setPosition(300,220);
    sprite1->setScale(450.f/sprite1->getTexture()->getSize().x,450.f/sprite1->getTexture()->getSize().y);

    //Crear personaje 1
    personaje1 = std::make_unique<Personaje>(sf::Vector2f(100.f, 200.f), 50.f, 50.f, sf::Color::Red);
    personaje1->RefreshAnimacion();


    actualizar_animacion(*sprite1);
    mapa->setTexture(*texture2);
    mapa->setScale(1000.f/mapa->getTexture()->getSize().x,800.f/mapa->getTexture()->getSize().y);
}

// Created by Fernando on 23/06/2023.
//
