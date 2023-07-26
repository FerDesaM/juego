//
// Created by Fernando on 24/07/2023.
//

#ifndef JUEGOC___MENU_H
#define JUEGOC___MENU_H
#include <SFML/Graphics.hpp>
enum class EstadoJuego {
    Menu,
    RealGame
};
class Menu{
private:
    EstadoJuego estadoJuego;
    sf::RenderWindow& ventana;
    std::vector<std::string> opciones;
    int opcionSeleccionada;
    sf::Font fuente;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
public:
    Menu(sf::RenderWindow& window);
    void DibujarMenu();
    void ProcesarEventos();
    void Cargar_recursos();
    bool seleccionaropcion();

};
#endif //JUEGOC___MENU_H
