#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "utils.hpp"

int main() {
sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3.0 Test");
    window.setFramerateLimit(60);
    
    GameManager manager(window, 0.1f); 

    manager.CreatePhysicsCircle(50.f, sf::Color::Red, {350.f, 100.f}, true);

    manager.CreatePhysicsRectangle(800.f, 20.f, sf::Color::Blue, {0.f, 580.f}, false);
    manager.CreatePhysicsRectangle(800.f, 20.f, sf::Color::Blue, {0.f, 0.f}, false);
    manager.CreatePhysicsRectangle(20.f, 600.f, sf::Color::Blue, {0.f, 0.f}, false);
    manager.CreatePhysicsRectangle(20.f, 600.f, sf::Color::Blue, {780.f, 0.f}, false);
    
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        window.clear(sf::Color::Black);

        manager.ApplyGravity();
        manager.CheckCollisions();
        manager.DrawObjects();
        window.display();
    }
    
    for(int i = 0; i < manager.PhysicsObjects.size(); i++){
        delete manager.PhysicsObjects[i].shape;
    }
    
    return 0;
}