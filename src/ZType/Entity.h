#ifndef ZTYPE_ENTITY_H
#define ZTYPE_ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <atomic>
#include "bullet.h"

using namespace sf;
class Entity : public  Object{
public:
    Entity(const sf::Font &font, const std::string &string);
    ~Entity();
    Text *getWord() const ; // gets the string in the text
    void draw(WindowSize &windowSize, sf::RenderWindow &window) override ;
    void setString(const std:: string &string);
    void move(float delta, sf::Vector2f dir);
    void erase_killedChar(char t, Bullet &bullet); // deletes killed letters.
    static int get_count(); // the number of letters typed in.
    static int get_killed(); // the number of deleted letters
    bool isStatus() const;
    static bool isFlag();
    bool isActive();
    void stop();
    int getId();
    size_t  getsize();
    void setId(int id);

    static char deltT[];
protected:
    static int killed;
    static int count;
    static bool flag;
    static int krasj;
    uint32_t id;

protected:
    Text *text= nullptr;
    float speed = 5;
    size_t size;
    bool status;

public:
    void setStatus(bool status);

protected:
    // true if the string is being shot at.
    bool active; // true if the string is drawn.
    static std::atomic<int> s_id;
};
#endif //ZTYPE_ENTITY_H
