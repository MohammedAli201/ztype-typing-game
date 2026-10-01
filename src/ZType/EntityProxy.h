
#ifndef ZTYPE_ENTITYPROXY_H
#define ZTYPE_ENTITYPROXY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"

class Entity;
class EntityProxy : public Object{
public:
    EntityProxy(const sf::Font &font, const std::string &string);
    void draw(WindowSize &windowSize, sf::RenderWindow &window) override;
    ~EntityProxy();
    void setString(const std:: string &string);
    sf::Text *getWord() const;
    void erase_killedChar(char t, Bullet &bullet);
    static int get_count();
    static int get_killed();
    void move(float dt, sf::Vector2f dir); ///
    size_t getsize();
    bool getStatus(); /// true if the current word being shot at
    bool isActive(); /// true if drawn on window
    static bool isFlag();
    int getId();
    int setId(int id);
private:
    Entity *EntityPtr= nullptr;
};


#endif //ZTYPE_ENTITYPROXY_H
