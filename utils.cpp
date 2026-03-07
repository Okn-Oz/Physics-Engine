#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include <cmath>
#include <iostream>

GameManager::GameManager(sf::RenderWindow& window, float gravity) : gameWindow(window), gravity(gravity){
}

PhysicsObject& GameManager::CreatePhysicsObject(sf::Shape* allocatedShape, bool isDynamic, int layer, ColliderType colliderType) {
    PhysicsObject obj;
    obj.shape = allocatedShape;
    obj.velocity = {0.f, 0.f}; 
    obj.isDynamic = isDynamic;
    obj.layer = layer;
    obj.colliderType = colliderType;

    PhysicsObjects.push_back(obj);
    
    return PhysicsObjects.back();
}

PhysicsObject& GameManager::CreatePhysicsCircle(float radius, sf::Color color, sf::Vector2f position, bool isDynamic, int layer) {
    sf::CircleShape* circle = new sf::CircleShape(radius);
    circle->setFillColor(color);
    circle->setPosition(position);
    
    return CreatePhysicsObject(circle, isDynamic, layer, ColliderType::Circle); 
}

PhysicsObject& GameManager::CreatePhysicsRectangle(float width, float height, sf::Color color, sf::Vector2f position, bool isDynamic, int layer) {

    sf::RectangleShape* rectangle = new sf::RectangleShape({width, height});
    rectangle->setFillColor(color);
    rectangle->setPosition(position);

    return CreatePhysicsObject(rectangle, isDynamic, layer, ColliderType::Rectangle);
}

void GameManager::UpdatePhysics() {
    for (int i = 0; i < PhysicsObjects.size(); i++) {
        if(PhysicsObjects[i].isDynamic){
            PhysicsObjects[i].velocity.y += gravity;
            PhysicsObjects[i].shape->move({PhysicsObjects[i].velocity.x, PhysicsObjects[i].velocity.y});
        }
    }
}

void GameManager::DrawObjects(){
    for (const auto& obj : PhysicsObjects) {
        gameWindow.draw(*obj.shape);
    }
}

void GameManager::ReorganizeLayers() {
    std::sort(PhysicsObjects.begin(), PhysicsObjects.end(), [](const PhysicsObject& a, const PhysicsObject& b) {
        return a.layer < b.layer;
    });
}

void GameManager::CheckCollisions() {
    CheckCircleCollisions();
    CheckRectangleCollisions();
}

void GameManager::CheckCircleCollisions() {
    for(int i = 0; i < PhysicsObjects.size(); i++){

        if(PhysicsObjects[i].colliderType != ColliderType::Circle) continue;

        sf::CircleShape* circle1 = dynamic_cast<sf::CircleShape*>(PhysicsObjects[i].shape);
        
        float r1 = circle1->getRadius();
        sf::Vector2f center1 = circle1->getPosition() + sf::Vector2f(r1, r1);

        for(int j = i + 1; j < PhysicsObjects.size(); j++){

            if(PhysicsObjects[j].colliderType != ColliderType::Circle) continue;

            sf::CircleShape* circle2 = dynamic_cast<sf::CircleShape*>(PhysicsObjects[j].shape);
            
            float r2 = circle2->getRadius();
            sf::Vector2f center2 = circle2->getPosition() + sf::Vector2f(r2, r2);
            
            float dx = center2.x - center1.x;
            float dy = center2.y - center1.y;
            
            float distanceSquared = (dx * dx) + (dy * dy);
            float radSum = r1 + r2;

            if(distanceSquared <= (radSum * radSum)){
                float distance = std::sqrt(distanceSquared);

                float nx = dx / distance;
                float ny = dy / distance;

                float overlap = radSum - distance;
                
                float invMass1 = PhysicsObjects[i].isDynamic ? 1.f : 0.f;
                float invMass2 = PhysicsObjects[j].isDynamic ? 1.f : 0.f;
                float totalMass = invMass1 + invMass2;

                if (totalMass > 0.f) {
                    float push1 = (invMass1 / totalMass) * overlap;
                    float push2 = (invMass2 / totalMass) * overlap;

                    circle1->move({-nx * push1, -ny * push1});
                    circle2->move({nx * push2, ny * push2});
                }
                float dvx = PhysicsObjects[j].velocity.x - PhysicsObjects[i].velocity.x;
                float dvy = PhysicsObjects[j].velocity.y - PhysicsObjects[i].velocity.y;

                float velAlongNormal = (dvx * nx) + (dvy * ny);

                if(velAlongNormal < 0){
                    float e = 0.1f;

                    float invMass1 = PhysicsObjects[i].isDynamic ? 1.f : 0.f;
                    float invMass2 = PhysicsObjects[j].isDynamic ? 1.f : 0.f;

                    float j_impulse = -(1.f + e) * velAlongNormal / (invMass1 + invMass2);

                    PhysicsObjects[i].velocity.x -= j_impulse * invMass1 * nx;
                    PhysicsObjects[i].velocity.y -= j_impulse * invMass1 * ny;
                    PhysicsObjects[j].velocity.x += j_impulse * invMass2 * nx;
                    PhysicsObjects[j].velocity.y += j_impulse * invMass2 * ny;
                }
            }
        }        
    }
}

void GameManager::CheckRectangleCollisions(){

}