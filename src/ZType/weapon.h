#ifndef _ZTYPE_WEAPON_H
#define _ZTYPE_WEAPON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "WindowSize.h"
#include "object.h"

using namespace sf;
class Weapon : public Object {
    friend class Bullet;
public:
    Weapon();
    ~Weapon();
    double  angel;
    int W_rotation(sf::Vector2f position );
    void draw(WindowSize &windowSize, sf::RenderWindow &window) override;
    sf::FloatRect getBounds();
    sf::Vector2f getPositon();
};


#endif //_ZTYPE_WEAPON_H
