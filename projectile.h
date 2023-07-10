//
// Created by Fernando on 26/06/2023.
//

#ifndef JUEGOC___PROJECTILE_H
#define JUEGOC___PROJECTILE_H
#include <SFML/Graphics.hpp>
class Projectile{
private:
    sf::CircleShape pro;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f windowBounds;
    float gravity;
public:
    Projectile(float radius,float speed,float gravity);
    void setPosition(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);
    void setWindowBounds(sf::Vector2f windowSize);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool checkCollision(sf::FloatRect bounds);
    //hacemos una comprobacion de que T y float son lo mismo en fire
    template<typename T>
    void fire(const sf::Vector2<T>& startPosition, const sf::Vector2<T>& initialVelocity) {
        static_assert(std::is_same_v<T,float>,"no son del mismo tipo");
        position = startPosition;
        velocity = initialVelocity;
    }
    sf::Vector2f getPosition() const {
        return position;
    }
    sf::Vector2f getVelocity() const {
        return velocity;
    }
    sf::CircleShape getShape() const {
        return pro;
    }
        sf::FloatRect getBounds() const {
            return pro.getGlobalBounds();
        }
};
#endif //JUEGOC___PROJECTILE_H
