#pragma once
#include "planet.hpp"

class sun: public planet
{
private:

public:
    sun(float radius, sf::Color color, float x, float y, float z):planet(*(planet*)(nullptr), radius, color, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f){
        this->radvec(1, 1) = x;
        this->radvec(2, 1) = y;
        this->radvec(3, 1) = z;
    }
    virtual void recalc(){}
    virtual void step(){}
    ~sun(){}
};


