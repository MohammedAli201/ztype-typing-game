#ifndef ZTYPE_BULLET_H
#define ZTYPE_BULLET_H

#include <list>
#include "object.h"
#include "WindowSize.h"
#include "weapon.h"


class GameManager;
class Bullet: public Object{

public:
    ~Bullet();
    //Particle system
    //ParticleSystem* m_particle= nullptr;

    //Bullet();
    void moveBullet(float dt);

    Bullet(WindowSize &windowSize, sf::RenderWindow *window);

    void draw(WindowSize &windowSize, sf::RenderWindow &window) override;

    //Finder will turn true only if there is a collision
    bool finder_Collision = false;

    void update();

    //Normal vector
    sf::Vector2f mainDirection;

    // It will check if target is true if so then the shooting will occurs
    bool isTargetShooting() const;

    void setTarget_Shooting(bool &target_Shooting);

    sf::Vector2<float> UnitVector(sf::Text *text);

    sf::Text *text1 = nullptr;
    sf::Vector2f direction;

private:
    // float bulletPx;
    // float  bulletPy;
    WindowSize windowSize;
    //Dependencies
    // sf::Texture texture;
    sf::RenderWindow *window;
    //Friksjon
    const float num = 0.02f;
    const int speed = 2000;
    //Substracting from the hight of screen;
    int const size = 100;
    // To find unit vector we used this vectors
    sf::Sprite sprite;
    //uses where the collision happens
    sf::Vector2f b_position;
    sf::Vector2f ordPos;
    sf::Vector2f d_ordBullet;
    int bulletSize = 0;
public:
    int getBulletSize() const;

protected:
    void detection(sf::Text &collision, sf::Vector2f& m_postion);
    bool status = true;
    bool shootingTarget = false;
    sf::Text *text;
    sf::RenderTarget *target = nullptr;
    sf::RenderStates states;

    sf::Vector2f m_vector;
    std::list<sf::Sprite *> objects;

};

#endif //ZTYPE_BULLET_H
