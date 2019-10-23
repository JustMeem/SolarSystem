#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setVisible(true);
    window.draw()
}
