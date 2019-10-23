#pragma once
#include "surface.hpp"
#include <cmath>
#include "sfml/Graphics.hpp"
#define M_PI 3.14159265358979323846




class planet
{
private:
    planet &parent;
    sf::CircleShape image{};
    gmtl::Matrix33f matrix = gmtl::Matrix33f();
    gmtl::Matrix<float, 3, 1> radvec = gmtl::Matrix<float, 3, 1>();
    float angle, avelocity, radius, s;
    const float e, a;
    bool calculated{false};
public:
    planet(planet &p, float diameter, sf::Color &color, float perhelion, float aphelion, float a, float e, float period,
            float inclination, float asclong, float periapsarg, float angle = 0):parent{p}, e{e}, a{a}, angle{angle}{
        image.setRadius(diameter / 2);
        image.setFillColor(color);
        float temp[9] = {1, 0, 0,
                        0, 1, 0,
                        0, 0, 1};
        matrix.set(temp);
        s = (perhelion + aphelion)/2 * (2 * M_PI / (period * 3650));
        inclination *= M_PI/180;
        asclong *= M_PI/180;
        periapsarg *= M_PI/180;
        rotateX(inclination);
        rotateY(asclong);
        rotateZ(periapsarg);
        radius = (a * (1 - e * e))/(1 + e * std::cos(angle));
        recalc();
    }

    bool isCalculated(){
        return calculated;
    }

    void scaleSpeed(float multiplyer){
        s *= multiplyer;
    }

    void reverse(){
        s = -s;
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
        float scale = s.getScale();
        image.setRadius(image.getRadius * scale);
        image.setPosition(sf::Vector2f((radvec(1, 1) + s.getX()) * scale, (radvec(2, 1)+ s.getY()) * scale));
        s.getWindow().draw(image);
    }

    void rotateX(float a){
        float m[9] = {1, 0, 0,
                      0, std::cos(a), std::sin(a),
                      0, -std::sin(a), std::cos(a)};
        gmtl::Matrix33f temp = gmtl::Matrix33f();
        temp.set(m);
        matrix = temp * matrix;
    }
    void rotateY(float a){
        float m[9] = {std::cos(a), 0, -std::sin(a),
                      0, 1, 0,
                      std::sin(a), 0, std::cos(a)};
        gmtl::Matrix33f temp = gmtl::Matrix33f();
        temp.set(m);
        matrix = temp * matrix;
    }
    void rotateZ(float a){
        float m[9] = {std::cos(a), std::sin(a), 0,
                      -std::sin(a), std::cos(a), 0,
                      0, 0, 1};
        gmtl::Matrix33f temp = gmtl::Matrix33f();
        temp.set(m);
        matrix = temp * matrix;
    }
    ~planet();
};