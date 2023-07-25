//
// Created by EQUIPO on 25/07/2023.
//

#include "VectorUtil.h"
#include <cmath>

sf::Vector2f VectorUtil::proyectarVectorSobreOtro(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dot = (a.x * b.x) + (a.y * b.y);
    float lengthSquared = (b.x * b.x) + (b.y * b.y);

    return sf::Vector2f((dot / lengthSquared) * b.x, (dot / lengthSquared) * b.y);
}

sf::Vector2f VectorUtil::reflejarVector(const sf::Vector2f& original, const sf::Vector2f& mirror) {
    sf::Vector2f projection = proyectarVectorSobreOtro(original, mirror);
    return sf::Vector2f(2.0f * projection.x - original.x, 2.0f * projection.y - original.y);
}

sf::Vector2f VectorUtil::normalizarVector(const sf::Vector2f& vector){
    float x = vector.x;
    float  y = vector.y;
    float length = std::sqrt(x * x + y * y);
    if (length != 0.0f) {
        x /= length;
        y /= length;
    }
    return sf::Vector2f(x,y);
}

float VectorUtil::getAngleWithXAxis(const sf::Vector2f& vector){
    float x = vector.x;
    float y = vector.y;
    return std::atan2(y, x)* 180.0f / M_PI;
}

void VectorUtil::incrementarAnguloAVector(sf::Vector2f& vector, float incrementoDegrees){
    float x = vector.x;
    float y = vector.y;
    float currentAngleRadians = std::atan2(y, x);
    float incrementRadians = incrementoDegrees * M_PI / 180.0f; // Convertir 1 grado a radianes

    float newAngleRadians = currentAngleRadians + incrementRadians;

    // Calcular las nuevas coordenadas con el ángulo incrementado
    float length = std::sqrt(x * x + y * y);
    x = length * std::cos(newAngleRadians);
    y = length * std::sin(newAngleRadians);

    vector.x = x;
    vector.y = y;
}