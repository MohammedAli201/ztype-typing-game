
#include "EntityProxy.h"
#include "Entity.h"
#include "bullet.h"

EntityProxy::EntityProxy(const sf::Font &font, const std::string &string){
    this->EntityPtr = new Entity(font,string);}
EntityProxy::~EntityProxy() {
    delete EntityPtr;
    EntityPtr = nullptr;}
void EntityProxy::setString(const std::string &string) {this->EntityPtr->setString(string);}
sf::Text *EntityProxy::getWord() const {return this->EntityPtr->getWord();}
void EntityProxy::erase_killedChar(char t, Bullet &bullet) {return this->EntityPtr->erase_killedChar(t,bullet);}
int EntityProxy::get_killed() {return Entity::get_killed();}
int EntityProxy::get_count() {return Entity::get_count();}
bool EntityProxy::getStatus() {return this->EntityPtr->isStatus();}
void EntityProxy::draw(WindowSize &windowSize, sf::RenderWindow &window) {return this->EntityPtr->draw(windowSize, window);}
void EntityProxy::move(float dt, sf::Vector2f dir ) {return this->EntityPtr->move(dt,dir);}
size_t EntityProxy::getsize() {return this->EntityPtr->getsize();}
bool EntityProxy::isActive() {return this->EntityPtr->isActive();}

bool EntityProxy::isFlag() {
    return Entity::isFlag();
}
int EntityProxy::getId() {
    return this->EntityPtr->getId();
}
int EntityProxy::setId(int id) {
    this->EntityPtr->setId(id);
}

