//
// Created by Fernando on 23/06/2023.
//

#ifndef JUEGOC___GAME_H
#define JUEGOC___GAME_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>
#include<memory>
#include "projectile.h"
#include "cuadrado.h"
#include "Personaje.h"
#include "Plataforma.h"
#include "Proyectil.h"
#include "ExplosionProyectil.h"
#include "RealGame.h"
#include "Menu.h"
using namespace std;
using namespace sf;

class Juego {
private:
    //Se hace uso del puntero unico para la liberacion de memoria
    sf::RenderWindow* ventana;
    std::unique_ptr<Projectile> projectile;
    std::unique_ptr<sf::Texture> texture1;
    std::unique_ptr<Sprite> sprite1;
    std::unique_ptr<Texture> texture2;
    std::unique_ptr<Sprite> mapa;
    std::unique_ptr<Cuadrado<float>> cuadrado;
    std::unique_ptr<Cuadrado<float>> cuadrado2;
    std::unique_ptr<Event> evento;
    sf::Vector2i divisionsprite;
    sf::Vector2f limiteMundo;
    std::unique_ptr<FabricaPersonaje> fabrica;
    //Personaje de juego
    std::unique_ptr<Personaje> personaje1;
    std::unique_ptr<Personaje> prota1;
    std::unique_ptr<Menu> menu;
    std::unique_ptr<RealGame> game;
    //Plataforma de juego
    std::vector<Plataforma> plataformas;
    bool juegoRealInicializado;
    //Aceleracion de gravedad
    sf::Vector2f gravity; // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f; // Delta de tiempo para cálculos de movimiento (60 FPS)
public:
    Juego(int ancho, int largo, const std::string& titulo);
    void Dibujar();
    void GameLoop();
    void Evento();
    void Colisiones();
    void Cargar_recursos();
    void crear_jugadores();
    void moverCamara();
    enum class EstadoJuego {
        Menu,
        RealGame
    };
    EstadoJuego estadoJuego;
};


#endif //JUEGOC___GAME_H
