//
// Created by Fernando on 23/06/2023.
//

#ifndef JUEGOC___GAME_H
#define JUEGOC___GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "components/CompPlataforma.h"
#include "components/CompBarraPoder.h"
#include "Menu.h"

using namespace std;
using namespace sf;

class Juego {
private:
    static Juego* instance;
    Juego(int ancho, int largo, const std::string& titulo);
    Juego();
    //Se hace uso del puntero unico para la liberacion de memoria
    std::unique_ptr<sf::RenderWindow> ventana;
    std::unique_ptr<Projectile> projectile;
    std::unique_ptr<sf::Texture> texture1;
    std::unique_ptr<Sprite> sprite1;
    std::unique_ptr<Texture> texture2;
    std::unique_ptr<Sprite> mapa;
    std::unique_ptr<Event> evento;
    sf::Vector2i divisionsprite;
    sf::Vector2f limiteMundo;
    std::unique_ptr<FabricaPersonaje> fabrica;
    std::unique_ptr<FabricaPersonaje> fabrica2;
    //Personaje de juego
    std::unique_ptr<Personaje> personaje1;
    std::unique_ptr<Personaje> prota1;
    std::unique_ptr<Personaje> prota2;
    std::unique_ptr<Menu> menu;
    std::unique_ptr<RealGame> game;
    //Plataforma de juego
    std::vector<Plataforma> plataformas;
    CompPlataforma *plataforma001;
    //Barra de poder para el disparo
    std::unique_ptr<CompBarraPoder> barraPoder;
    bool juegoRealInicializado;
    std::vector<std::unique_ptr<Personaje>> personajes;
    std::unique_ptr<sf::Sound> sonido;
    std::unique_ptr<sf::SoundBuffer> buffer;
    std::vector<Proyectil> proyectiles;
    //Aceleracion de gravedad
    sf::Vector2f gravity; // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f; // Delta de tiempo para cálculos de movimiento (60 FPS)
public:
    static Juego* getInstance(int ancho, int largo, const std::string& titulo);
    void Dibujar();
    void GameLoop();
    void Evento();
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
