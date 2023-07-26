//
// Created by Fernando on 24/07/2023.
//

#ifndef JUEGOC___REALGAME_H
#define JUEGOC___REALGAME_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "Personaje.h"
using namespace sf;
enum class EstadoJuego;
class RealGame{
private:
    //EstadoJuego& estadoJuego;
    sf::RenderWindow& ventana;
    //std::unique_ptr<Projectile> projectile;
    std::unique_ptr<sf::Texture> texture1;
    std::unique_ptr<Sprite> sprite1;
    std::unique_ptr<Texture> texture2;
    std::unique_ptr<Sprite> mapa;
    //std::unique_ptr<Cuadrado<float>> cuadrado;
    //std::unique_ptr<Cuadrado<float>> cuadrado2;
    std::unique_ptr<Event> evento;
    sf::Vector2i divisionsprite;
    sf::Vector2f limiteMundo;
    std::unique_ptr<FabricaPersonaje> fabrica;
    //Personaje de juego
    std::unique_ptr<Personaje> personaje1;
    std::unique_ptr<Personaje> prota1;
    //Aceleracion de gravedad
    sf::Vector2f gravity; // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f;
public:
    RealGame(RenderWindow &ventana);
    void Inicializar();
    void crear_jugadores();
    void Evento();
    void MoverCamara();
    void Dibujar();
    void Colisiones();
    void cargarrecursos();

};
#endif //JUEGOC___REALGAME_H
