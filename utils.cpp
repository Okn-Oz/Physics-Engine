#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

GameManager::GameManager(sf::RenderWindow& window, float gravity) : gameWindow(window), gravity(gravity){
}

PhysicsObject GameManager::CreatePhysicsObject(sf::Shape* allocatedShape, bool isDynamic, int layer, ColliderType colliderType) {
    PhysicsObject obj;
    obj.shape = allocatedShape;
    obj.velocity = {0.f, 0.f}; 
    obj.isDynamic = isDynamic;
    obj.layer = layer;
    obj.colliderType = colliderType;

    PhysicsObjects.push_back(obj);
    
    return obj;
}

PhysicsObject GameManager::CreatePhysicsCircle(float radius, sf::Color color, sf::Vector2f position, bool isDynamic, int layer) {
    sf::CircleShape* circle = new sf::CircleShape(radius);
    circle->setFillColor(color);
    circle->setPosition(position);
    
    return CreatePhysicsObject(circle, isDynamic, layer, ColliderType::Circle); 
}

PhysicsObject GameManager::CreatePhysicsRectangle(float width, float height, sf::Color color, sf::Vector2f position, bool isDynamic, int layer) {

    sf::RectangleShape* rectangle = new sf::RectangleShape({width, height});
    rectangle->setFillColor(color);
    rectangle->setPosition(position);

    return CreatePhysicsObject(rectangle, isDynamic, layer, ColliderType::Rectangle);
}

void GameManager::ApplyGravity() {
    for (int i = 0; i < PhysicsObjects.size(); i++) {
        if(PhysicsObjects[i].isDynamic){
            PhysicsObjects[i].velocity.y += gravity;
            PhysicsObjects[i].shape->move({0.f, PhysicsObjects[i].velocity.y});
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

void GameManager::CheckCircleCollisions(){
    for(int i = 0; i < PhysicsObjects.size(); i++){

        sf::CircleShape* circle1 = dynamic_cast<sf::CircleShape*>(PhysicsObjects[i].shape);

        if(PhysicsObjects[i].colliderType == ColliderType::Circle){

            for(int j = 0; j < PhysicsObjects.size(); j++){
                if(i == j && !(PhysicsObjects[j].colliderType == ColliderType::Circle)) continue;
                sf::CircleShape* circle2 = dynamic_cast<sf::CircleShape*>(PhysicsObjects[j].shape);

            }        
        }
    }
}

void GameManager::CheckRectangleCollisions(){

}