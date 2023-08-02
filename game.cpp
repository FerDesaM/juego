#include "game.h"
#include "cuadrado.h"
#include <type_traits>
#include "Menu.h"
#include<memory>

Juego::Juego(int ancho, int largo, const std::string& titulo) {
    int fps = 60;
    gravity = sf::Vector2f(0.f, 9.8f); // Gravedad (puedes ajustarla según tus necesidades)
    ventana= make_unique<sf::RenderWindow>(sf::VideoMode(ancho,largo),titulo);
    ventana->setFramerateLimit(fps);

    limiteMundo=sf::Vector2f(ancho*4,largo*2);
    divisionsprite.x=5;
    divisionsprite.y=4;
    Cargar_recursos();
    evento= make_unique<Event>();
    GameLoop();
}

void Juego::GameLoop() {

    juegoRealInicializado = false;
    menu= make_unique<Menu>(*ventana);
    game= make_unique<RealGame>(*ventana);
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    bool isProjectileMoving = false;
    sf::View camaraView;
    //camaraView.setSize(sf::Vector2f(ventana->getSize().x, ventana->getSize().y));
    ventana->setView(camaraView);
    sonido->play();
    while (ventana->isOpen())
    {
        if(estadoJuego==EstadoJuego::Menu){
        menu->Cargar_recursos();
        menu->ProcesarEventos();
        menu->DibujarMenu();
    if (menu->seleccionaropcion()){
            estadoJuego=EstadoJuego::RealGame;

        if(!juegoRealInicializado) {
            game->Inicializar();
            juegoRealInicializado = true;
        } }}
        else if(estadoJuego==EstadoJuego::RealGame){

                prota2->AplicarGravedad(deltaTime, gravity, plataformas);
                prota1->AplicarGravedad(deltaTime, gravity, plataformas);
            Evento();
            moverCamara();
            Dibujar();
            //Colisiones();
        }
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

    //plataforma001->Draw(*ventana);
    //Dibujar Plataformas
    for (auto& plataforma : plataformas) {
        plataforma.Draw(*ventana);
    }
    //plataforma001.Draw(*ventana);
    barraPoder->Draw(*ventana);

    //Dibujar Personaje
    prota2->Draw(*ventana,deltaTime,gravity,plataformas);
    prota1->Draw(*ventana, deltaTime, gravity,plataformas);

    ventana->draw(cuadrado->getShape());
    ventana->draw(cuadrado2->getShape());
    //proy.Draw(window);

    ventana->display();
}
void Juego::Evento()
{
    while(ventana->pollEvent(*evento))
    {
        if (evento->type==sf::Event::Closed){
            ventana->close();
            exit(1);
            break;
        }
        else{
            prota2->ResponderEvento(*evento,* barraPoder);
            prota1->ResponderEvento2(*evento,*barraPoder);//Responder evento de Personaje1
            barraPoder->ResponderEvento(*evento);//Responder evento de Barra de poder de disparo
        }
    }
}
void Juego::Colisiones()
{



}
void Juego::crear_jugadores()
{
    fabrica = std::make_unique<Prota>();
    sf::Vector2f posicion(400.f,200.f);
    sf::Color color=sf::Color::Blue;
    prota1.reset(fabrica->crearPersonaje(posicion,color));
    prota1->RefreshAnimacion();
    fabrica2 = std::make_unique<Prota2>();
    sf::Vector2f posicion2(400.f,200.f);
    sf::Color color2=sf::Color::Blue;
    prota2.reset(fabrica2->crearPersonaje(posicion2,color2));
    prota2->RefreshAnimacion();
}

void Juego::Cargar_recursos()
{
    cuadrado = std::make_unique<Cuadrado<float>>(sf::Vector2f(200.f, 200.f), sf::Vector2f(50.f, 50.f),Color::Blue);
    cuadrado2 = std::make_unique<Cuadrado<float>>(sf::Vector2f(0.f, 735.f), sf::Vector2f(1000.f, 50.f),Color::Red);
    texture1= std::make_unique<sf::Texture>();
    texture2= std::make_unique<sf::Texture>();
    sprite1=std::make_unique<sf::Sprite>();
    mapa=std::make_unique<sf::Sprite>();

    texture2->loadFromFile("../images/mapa.jpg");
    sprite1->setTexture(*texture1);
    sprite1->setPosition(300,220);
    //sprite1->setScale(450.f/sprite1->getTexture()->getSize().x,450.f/sprite1->getTexture()->getSize().y);

    plataforma001= new CompPlataforma(sf::Vector2f(0.f, 0.f),200.f,50.f,"../images/Plt1.png",1,1);

    //Cargar Plataformas
    Plataforma plata(sf::Vector2f(500.f, 500.f), 900.f, 200.f);
    plataformas.push_back(plata);
    //Crear personaje 1//////////////////////////////
    personaje1 = std::make_unique<Personaje>(sf::Vector2f(0.f, 300.f), 300.f, 300.f, sf::Color::Red);
    personaje1->AplicarGravedad(deltaTime,gravity,plataformas);
    personaje1->RefreshAnimacion();
    //Crear Barra de lanzamiento
    barraPoder = std::make_unique<CompBarraPoder>(sf::Vector2f(50, 800), sf::Vector2f(800, 40), sf::Color::Green, sf::Color::Black);
    crear_jugadores();
    buffer = std::make_unique<sf::SoundBuffer>();
    buffer->loadFromFile("../images/big+space.ogg");
    sonido = std::make_unique<sf::Sound>();
    sonido->setBuffer(*buffer);
    sonido->setVolume(80.f);
    mapa->setTexture(*texture2);
    mapa->setScale(1000.f/mapa->getTexture()->getSize().x,800.f/mapa->getTexture()->getSize().y);
}

// Created by Fernando on 23/06/2023.
//
