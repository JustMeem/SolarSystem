#pragma once
#include "surface.hpp"
#include <cmath>
#include "sfml/Graphics.hpp"
#define M_PI 3.14159265358979323846



class planet
{
private:
    planet &parent;
    sf::CircleShape image;
    gmtl::Matrix33f matrix = gmtl::Matrix33f();
    gmtl::Matrix<float, 3, 1> radvec = gmtl::Matrix<float, 3, 1>();
    float angle, avelocity, radius;
    const float e, a, s;
    bool calculated{false};
public:
    planet(){
        float temp[9] = {1, 0, 0,
                        0, 1, 0,
                        0, 0, 1};
        matrix.set(temp);
    }

    bool isCalculated(){
        return calculated;
    }

    void step(){
        calculated = false;
        avelocity = s / radius;
        angle += avelocity;
        radius = (a * (1 - e * e))/(1 + e * std::cos(angle));
    }
    

    bool operator <(planet &right){
        return this->radvec(3, 1) < right.radvec(3, 1);
    }

    void recalc(){
        radvec(1, 1) = radius * std::cos(angle);
        radvec(2, 1) = radius * std::sin(angle);
        radvec(3, 1) = 0;
        radvec = matrix * radvec;
        radvec(1, 1) += parent.radvec(1, 1);
        radvec(2, 1) += parent.radvec(2, 1);
        radvec(3, 1) += parent.radvec(3, 1);
        calculated = true;
    }

    void draw(surface &s){
        image.setRadius(image.getRadius * s.scale);
        image.setPosition(sf::Vector2f((radvec(1, 1) + s.x) * s.scale, (radvec(2, 1)+ s.y) * s.scale));
        s.window.draw(image);
    }

    void rotateX(float a){
        float m[9] = {1, 0, 0,
                      0, std::cos(a), std::sin(a),
                      0, -std::sin(a), std::cos(a)};
        gmtl::Matrix33f temp = gmtl::Matrix33f();
        temp.set(m);
        matrix = matrix * temp;
    }
    void rotateY(float a){
        float m[9] = {std::cos(a), 0, -std::sin(a),
                      0, 1, 0,
                      std::sin(a), 0, std::cos(a)};
        gmtl::Matrix33f temp = gmtl::Matrix33f();
        temp.set(m);
        matrix = matrix * temp;
    }
    void rotateZ(float a){
        float m[9] = {std::cos(a), std::sin(a), 0,
                      -std::sin(a), std::cos(a), 0,
                      0, 0, 1};
        gmtl::Matrix33f temp = gmtl::Matrix33f();
        temp.set(m);
        matrix = matrix * temp;
    }
    ~planet();
};