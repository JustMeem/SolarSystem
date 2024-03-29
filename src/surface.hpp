#pragma once
#include "planet.hpp"
#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include <sfml/Graphics.hpp>

#include <cmath>
#include <vector>

class surface
{
    friend class planet;
private:
    sf::RenderWindow &window;
    std::vector<planet> &planets;
    float x{}, y{};
    float scale{1};
public:
    surface(sf::RenderWindow &w, std::vector<planet> &p):window{w}, planets{p}{}

    float getX(){
        return x;
    }
    float getY(){
        return y;
    }
    float getScale(){
        return scale;
    }
    sf::RenderWindow &getWindow(){
        return window;
    }


    void rotateX(float a){
        for (auto &planet : planets){
            planet.rotateX(a);
        }
    }
    void rotateY(float a){
        for (auto &planet : planets){
            planet.rotateY(a);
        }
    }
    void rotateZ(float a){
        for (auto &planet : planets){
            planet.rotateZ(a);
        }
    }
    void rescale(float mult){
        scale *= mult;
    }
    void move(float dx, float dy){
        x += dx;
        y += dy;
    }
    void draw(){
        std::sort(planets.begin(), planets.end());
        window.clear();
        for(auto &planet : planets){
            planet.draw(*this);
        }
    }
    ~surface(){}
};


