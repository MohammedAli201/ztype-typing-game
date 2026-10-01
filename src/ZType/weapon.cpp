using namespace std;
#include "weapon.h"


Weapon::Weapon() {
    size = 100;
}

Weapon::~Weapon() {
}

void Weapon::draw(WindowSize&windowSize, sf::RenderWindow &window) {
    if (!texture.loadFromFile("source/image/last.png")) {
        std::cout << "Error occured \n";
    }
    pX = (float) windowSize.screenWidth / 2;
    pY = (float) windowSize.screenHeight - size;

    sprite.setTexture(texture);
    sprite.setPosition(pX, pY);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));

    window.draw(sprite);

}

int Weapon::W_rotation(sf::Vector2f position) {
    return angel;
}

sf::Vector2f Weapon::getPositon() {
    return this->sprite.getPosition();
}
sf::FloatRect Weapon::getBounds(){
    return this->sprite.getGlobalBounds();
}










