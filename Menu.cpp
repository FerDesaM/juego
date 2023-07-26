//
// Created by Fernando on 24/07/2023.
//

#include "Menu.h"
Menu::Menu(sf::RenderWindow& window) : ventana(window), opcionSeleccionada(0) {
    // Carga una fuente para el texto del menú
    if (!fuente.loadFromFile("../images/04B_31__.ttf")) {
        // Manejo de error si la fuente no se pudo cargar
    }

    // Define las opciones del menú
    opciones.push_back("Jugar");
    opciones.push_back("Configuracion");
    opciones.push_back("Salir");
}

void Menu::DibujarMenu() {
    ventana.clear(sf::Color::Black);
    ventana.draw(spriteFondo);
    spriteFondo.setScale(1000.f/spriteFondo.getTexture()->getSize().x,800.f/spriteFondo.getTexture()->getSize().y);
    // Configura el tamaño y color del texto
    int tamTexto = 30;
    sf::Color colorTextoNormal = sf::Color::White;
    sf::Color colorTextoSeleccionado = sf::Color::Red;

    for (size_t i = 0; i < opciones.size(); i++) {
        sf::Text texto(opciones[i], fuente, tamTexto);
        texto.setPosition(ventana.getSize().x / 2 - texto.getGlobalBounds().width / 2, 500.f + i * 200.f);

        // Cambia el color del texto si está seleccionado
        if (i == opcionSeleccionada) {
            texto.setFillColor(colorTextoSeleccionado);
        } else {
            texto.setFillColor(colorTextoNormal);
        }

        ventana.draw(texto);
    }

    ventana.display();
}

void Menu::ProcesarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
        } else if (evento.type == sf::Event::KeyPressed) {
            if (evento.key.code == sf::Keyboard::Up) {
                opcionSeleccionada = (opcionSeleccionada + opciones.size() - 1) % opciones.size();
            } else if (evento.key.code == sf::Keyboard::Down) {
                opcionSeleccionada = (opcionSeleccionada + 1) % opciones.size();
            } else if (evento.key.code == sf::Keyboard::Enter) {
                // Procesar selección de opción
                if (opcionSeleccionada == 0) {
                    //estadoJuego=EstadoJuego::RealGame;
                    //estadoJuego = EstadoJuego::RealGame;
                    // Opción "Jugar"
                    // Aquí puedes iniciar el juego o cambiar el estado del juego
                } else if (opcionSeleccionada == 1) {
                    // Opción "Configuración"
                    // Implementa la configuración del juego si lo deseas
                } else if (opcionSeleccionada == 2) {
                    // Opción "Salir"
                    ventana.close();
                }
            }
        }
    }
}
void Menu::Cargar_recursos() {
    // ...

    if (!texturaFondo.loadFromFile("../images/Space bullet.png")) {
        // Manejo de error si la imagen no se pudo cargar
    }

    spriteFondo.setTexture(texturaFondo);
}
bool Menu::seleccionaropcion() {
    // En este ejemplo, consideraremos que el usuario selecciona la opción al presionar Enter.
    // Aquí podrías agregar lógica adicional según tus necesidades.

    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}