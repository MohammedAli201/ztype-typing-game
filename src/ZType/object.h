#include <SFML/Graphics.hpp>
#include "WindowSize.h"
#ifndef _ZTYPE_OBJECT_H
#define _ZTYPE_OBJECT_H


class Object {
public:
    virtual void draw(WindowSize &windowSize, sf::RenderWindow &window) {}
    // Text will make a movement.
 //todo: have a position variable , list som holder all objects,
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float pX;
    float pY;
    int size;




};

#endif //_ZTYPE_OBJECT_H
