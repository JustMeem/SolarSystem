#pragma once
#include "surface.hpp"
#include "sfml/Graphics.hpp"



class planet
{
private:
    planet &parent;
    sf::Color color;
    gmtl::Matrix33f matrix = gmtl::Matrix33f();
    gmtl::Matrix<float, 3, 1> radvec = gmtl::Matrix<float, 3, 1>();
public:
    planet(){
        float temp[9] = {1, 0, 0,
                        0, 1, 0,
                        0, 0, 1};
        matrix.set(temp);
    }

    

    bool operator <(planet &right){
        return this->radvec(3, 1) < right.radvec(3, 1);
    }

    static void draw(surface *s){
        s->window.draw(sf::CircleShape())
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