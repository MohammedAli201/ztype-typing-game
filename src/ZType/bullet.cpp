#include <iostream>
#include <math.h>
#include "bullet.h"
#include "weapon.h"


using namespace sf;
using namespace std;
Bullet::Bullet(WindowSize &windwoSize, sf::RenderWindow *window) :
        windowSize(windwoSize), window(window), target(window) {
    pY = (float) windwoSize.screenHeight - (float) size;
    pX = (float) windwoSize.screenWidth / 2;
    text1 = new Text;

   // m_particle= new ParticleSystem();

}

// Move  will take the position of the text and then it will move depend on the direction
void Bullet::moveBullet(float dt) {
    if (isTargetShooting()) {
        m_vector.x = pX -= mainDirection.x * (float) speed * num;
        m_vector.y = pY -= mainDirection.y * (float) speed * num;
        sprite.setPosition(pX, pY);
        detection(*text1, m_vector);
        bulletSize++;

    }
}

void Bullet::draw(WindowSize &windowSize, sf::RenderWindow &window) {
    if (!texture.loadFromFile("source/image/bullet.png")) {
        std::cout << "Error occured \n";
    }
    sprite.setTexture(texture);
    sprite.setPosition(pX, pY);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    objects.push_back(new sf::Sprite);




    window.draw(sprite);
   // window.draw(*m_particle);


}

sf::Vector2<float> Bullet::UnitVector(sf::Text *text2) {
    //We have to update text and that will make us to detect collision
    text1 = text2;
    b_position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
    ordPos = sf::Vector2f(text2->getPosition().x, text2->getPosition().y);
    d_ordBullet = b_position - ordPos;
    double sqrt1 = sqrt(pow(d_ordBullet.x, 2) + pow(d_ordBullet.y, 2));
    mainDirection = sf::Vector2f(d_ordBullet.x / sqrt1, d_ordBullet.y / sqrt1);
    // this temporary variable which hold the direction the of the text;
    return mainDirection;
}

void Bullet::update() {
    // keep the window
    if (pY < 0 || pX < 0 || pX > 800) {
    }
}

//Collision detection
void Bullet::detection(sf::Text &collision, sf::Vector2f &m_postion) {
    int init=1000;
    //if (!m_particle->running()) {
        if (collision.getPosition().y == m_postion.y || collision.getPosition().y - m_postion.y > 0) {
            finder_Collision = status;
         //   m_particle->init(init);
            //Particle System
           // m_particle->emitParticles(m_postion);
        }
    }



//}

void Bullet::setTarget_Shooting(bool &target_Shooting) {
    Bullet::shootingTarget = target_Shooting;
}

bool Bullet::isTargetShooting() const {
    return shootingTarget;
}

Bullet::~Bullet() {

    delete this->window;
    delete this->text1;

   // delete this->m_particle;
}

int Bullet::getBulletSize() const {
    return bulletSize;
}
