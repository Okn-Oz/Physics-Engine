#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "utils.hpp"
#include <iostream>

int main() {
sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3.0 Test");
    window.setFramerateLimit(1);
    

    GameManager manager(window, 0.1f); 

    PhysicsObject& object1 = manager.CreatePhysicsCircle(50.f, sf::Color::Red, {380.f, 400.f}, true);
    object1.velocity = {0, -10};

    manager.CreatePhysicsCircle(50.f, sf::Color::Blue, {350.f, 0.f}, true);

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)){
            window.setFramerateLimit(60);
        }
        manager.UpdatePhysics();
        manager.CheckCollisions();
        manager.DrawObjects();
        window.display();
        std::cout << object1.velocity.y << std::endl;
    }
    
    for(int i = 0; i < manager.PhysicsObjects.size(); i++){
        delete manager.PhysicsObjects[i].shape;
    }
    
    return 0;
}