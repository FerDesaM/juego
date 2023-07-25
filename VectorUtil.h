//
// Created by EQUIPO on 25/07/2023.
//

#ifndef JUEGOC___VECTORUTIL_H
#define JUEGOC___VECTORUTIL_H
#include <SFML/System/Vector2.hpp>

class VectorUtil {
public:
    static sf::Vector2f proyectarVectorSobreOtro(const sf::Vector2f& a, const sf::Vector2f& b);
    static sf::Vector2f reflejarVector(const sf::Vector2f& original, const sf::Vector2f& mirror);
    static sf::Vector2f normalizarVector(const sf::Vector2f& vector);
    static float getAngleWithXAxis(const sf::Vector2f& vector);
    static void incrementarAnguloAVector(sf::Vector2f& vector,float incrementoDegrees);
};


#endif //JUEGOC___VECTORUTIL_H
