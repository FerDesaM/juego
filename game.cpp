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
    limiteMundo=sf::Vector2f(ancho*4,largo*2);
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
    sf::View camaraView;
    camaraView.setSize(sf::Vector2f(ventana->getSize().x, ventana->getSize().y));
    ventana->setView(camaraView);
    while (ventana->isOpen())
    {
        Evento();
        moverCamara();
        Dibujar();
        Colisiones();
    }
}
void Juego::moverCamara() {
    sf::Vector2f personajePosition = personaje1->getPosition();

    // Asegurarse de que la cámara no salga de los límites del mundo
    sf::Vector2f camaraPosition = personajePosition;
    if (camaraPosition.x < ventana->getSize().x / 2) {
        camaraPosition.x = ventana->getSize().x / 2;
    }
    if (camaraPosition.y < ventana->getSize().y / 2) {
        camaraPosition.y = ventana->getSize().y / 2;
    }
    if (camaraPosition.x > limiteMundo.x - ventana->getSize().x / 2) {
        camaraPosition.x = limiteMundo.x - ventana->getSize().x / 2;
    }
    if (camaraPosition.y > limiteMundo.y - ventana->getSize().y / 2) {
        camaraPosition.y = limiteMundo.y - ventana->getSize().y / 2;
    }

    // Establecer la posición de la cámara para que el personaje esté en el centro
    sf::View camaraView;
    camaraView.setCenter(camaraPosition);
    ventana->setView(camaraView);

    // Establecer la posición del fondo (mapa) según la posición de la cámara
    mapa->setPosition(camaraPosition - sf::Vector2f(ventana->getSize().x / 2, ventana->getSize().y / 2));
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
    prota1->Draw(*ventana, deltaTime, gravity);
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
                personaje1->ResponderEvento(*evento,deltaTime);
                prota1->ResponderEvento(*evento,deltaTime);//Responder evento de Personaje1
                break;
        }

    }
}
void Juego::Colisiones()
{



}
void Juego::crear_jugadores()
{
    fabrica = std::make_unique<Prota>();
    sf::Vector2f posicion(500.f,600.f);
    sf::Color color=sf::Color::Blue;
    prota1.reset(fabrica->crearPersonaje(posicion,color));
    prota1->RefreshAnimacion();

}

void Juego::Cargar_recursos()
{
    cuadrado = std::make_unique<Cuadrado<float>>(sf::Vector2f(200.f, 200.f), sf::Vector2f(50.f, 50.f),Color::Blue);
    cuadrado2 = std::make_unique<Cuadrado<float>>(sf::Vector2f(0.f, 735.f), sf::Vector2f(1000.f, 50.f),Color::Red);
    texture1= std::make_unique<sf::Texture>();
    texture2= std::make_unique<sf::Texture>();
    sprite1=std::make_unique<sf::Sprite>();
    mapa=std::make_unique<sf::Sprite>();
    //texture1->loadFromFile("../images/mariobros.png");
    texture2->loadFromFile("../images/mapa.jpg");
    sprite1->setTexture(*texture1);
    sprite1->setPosition(300,220);
    //sprite1->setScale(450.f/sprite1->getTexture()->getSize().x,450.f/sprite1->getTexture()->getSize().y);

    //Crear personaje 1//////////////////////////////
    personaje1 = std::make_unique<Personaje>(sf::Vector2f(0.f, 300.f), 300.f, 300.f, sf::Color::Red);
    personaje1->RefreshAnimacion();
    crear_jugadores();
    mapa->setTexture(*texture2);
    mapa->setScale(1000.f/mapa->getTexture()->getSize().x,800.f/mapa->getTexture()->getSize().y);
}

// Created by Fernando on 23/06/2023.
//
