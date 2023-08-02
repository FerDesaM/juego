//
// Created by Fernando on 24/07/2023.
//

#include "RealGame.h"
RealGame::RealGame(sf::RenderWindow& window) : ventana(window) {
    cargarrecursos();
    evento= std::make_unique<Event>();

}
void RealGame::Evento()
{
    while(ventana.pollEvent(*evento))
    {
        switch (evento->type)
        {
            case Event::Closed:
                ventana.close();
                exit(1);
                break;
            case Event::KeyPressed:
                //personaje1->ResponderEvento(*evento);
                //prota1->ResponderEvento(*evento);//Responder evento de Personaje1
                break;
        }

    }
}
void RealGame::crear_jugadores()
{
    fabrica = std::make_unique<Prota>();
    sf::Vector2f posicion(500.f,600.f);
    sf::Color color=sf::Color::Blue;
    prota1.reset(fabrica->crearPersonaje(posicion,color));
    prota1->RefreshAnimacion();

}
void RealGame::Dibujar() {
    ventana.clear(sf::Color::Blue);

    // projectile->draw(*ventana);
    ventana.draw(*mapa);
    ventana.draw(*sprite1);
    ///ventana.draw(cuadrado->getShape());
    //ventana.draw(cuadrado2->getShape());
    //Dibujar Personaje
    //personaje1->Draw(ventana,deltaTime,gravity);
    //prota1->Draw(ventana, deltaTime, gravity);
    ventana.display();}
void RealGame:: Inicializar(){

    cargarrecursos();
}
void RealGame::cargarrecursos()
{
    //cuadrado = std::make_unique<Cuadrado<float>>(sf::Vector2f(200.f, 200.f), sf::Vector2f(50.f, 50.f),Color::Blue);
    //cuadrado2 = std::make_unique<Cuadrado<float>>(sf::Vector2f(0.f, 735.f), sf::Vector2f(1000.f, 50.f),Color::Red);
    texture1= std::make_unique<sf::Texture>();
    texture2= std::make_unique<sf::Texture>();
    sprite1=std::make_unique<sf::Sprite>();
    mapa=std::make_unique<sf::Sprite>();
    //Menu menu(*ventana);
    //texture1->loadFromFile("../images/mariobros.png");
    texture2->loadFromFile("../images/mapa.jpg");
    sprite1->setTexture(*texture1);
    sprite1->setPosition(300,220);
    sprite1->setScale(450.f/sprite1->getTexture()->getSize().x,450.f/sprite1->getTexture()->getSize().y);

    //Crear personaje 1
    personaje1 = std::make_unique<Personaje>(sf::Vector2f(100.f, 200.f), 50.f, 50.f, sf::Color::Red);
    personaje1->RefreshAnimacion();
    crear_jugadores();
    mapa->setTexture(*texture2);
    mapa->setScale(1000.f/mapa->getTexture()->getSize().x,800.f/mapa->getTexture()->getSize().y);
}