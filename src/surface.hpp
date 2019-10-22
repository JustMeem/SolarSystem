#pragma once
#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include <sfml/Graphics.hpp>
#include "planet.hpp"
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
        for(auto &planet : planets){
            planet.draw(*this);
        }
    }
    ~surface(){}
};


