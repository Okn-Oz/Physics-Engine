#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class ColliderType {
    Circle,
    Rectangle
};

struct PhysicsObject {
    sf::Shape* shape;     
    sf::Vector2f velocity;    
    bool isDynamic;
    int layer;
    ColliderType colliderType;
};

class GameManager {
public:
    sf::RenderWindow& gameWindow;
    std::vector<PhysicsObject> PhysicsObjects;
    float gravity;

    GameManager(sf::RenderWindow& window, float gravity);

    PhysicsObject& CreatePhysicsObject(sf::Shape* allocatedShape, bool isDynamic = true, int layer = 0, ColliderType colliderType = ColliderType::Circle);
    PhysicsObject& CreatePhysicsCircle(float radius = 50.f, sf::Color color = sf::Color::White, sf::Vector2f position = {0.f, 0.f}, bool isDynamic = true, int layer = 0);
    PhysicsObject& CreatePhysicsRectangle(float heigth = 20.f, float width = 20.f, sf::Color color = sf::Color::White, sf::Vector2f position = {0, 0}, bool isDynamic = true, int layer = 0);
    void UpdatePhysics();
    void CheckCollisions();
    void CheckCircleCollisions();
    void CheckRectangleCollisions();
    void DrawObjects();
    void ReorganizeLayers();
};