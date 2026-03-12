#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "utils.hpp"
#include <iostream>

int main() {
sf::RenderWindow window(sf::VideoMode({800, 600}), "Physics Engine Demo");
    window.setFramerateLimit(1);
    GameManager manager(window, 0.1f); 

    manager.CreatePhysicsCircle(50.f, sf::Color::Red, {400.f, 50.f}, true);
    manager.CreatePhysicsCircle(50.f, sf::Color::Blue, {450.f, 300.f}, true);
    manager.CreatePhysicsCircle(25.f, sf::Color::Blue, {75.f, 170.f}, true).velocity = {10, 5};


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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)){
            window.setFramerateLimit(60);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)){
            window.setFramerateLimit(1);
        }
        manager.UpdatePhysics();
        manager.CheckCollisions();
        manager.DrawObjects();
        window.display();
    }
    
    for(int i = 0; i < manager.PhysicsObjects.size(); i++){
        delete manager.PhysicsObjects[i].shape;
    }
    
    return 0;
}