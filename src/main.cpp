#include <iostream>
#include "surface.hpp"
#include "planet.hpp"
#include "sun.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    window.setVerticalSyncEnabled(true);
    window.setVisible(true);
    std::vector<planet> planets(15);
    sun Sun(50.0f, sf::Color(255, 219, 77), 500.0f, 500.0f, 0.0f);
    planets.push_back(Sun);
    surface solar_system(window, planets);
    solar_system.draw();
    while(window.isOpen()){}
}
