
#include "Entity.h"
#include "bullet.h"
#include "WindowSize.h"
int Entity::killed = 0;
int Entity::count = 0;
bool Entity::flag = false;
char Entity::deltT[5];
std::atomic<int> Entity::s_id;
Entity::Entity(const sf::Font &font, const std::string &string) {
    text = new Text();
    text->setFont(font);
    text->setString(string);
    text->setCharacterSize(26);
    text->setFillColor(Color::Red);
    size = text->getString().getSize();
    text->setPosition(rand()% 800 + 1, 0);
    this->status = false;
    this->active = false;
    id = ++s_id;
}


Text *Entity::getWord() const {return this->text;}

Entity::~Entity() {
    delete this->text;
    this->text = nullptr;
}

void Entity::setString(const std::string &string) {
    this->text->setString(string);
}
void Entity::erase_killedChar(char t, Bullet &bullet) {
    /// erases the first alphabet of a string.
    size_t found = this->getWord()->getString().find(t);
    std::cout << "Position of found: " << found << std::endl;
    try {
        if (found == 0) {

            flag  = true;
            std::string str2 = this->getWord()->getString();
            status = true;
            this->text->setFillColor(Color::Green);
            bullet.setTarget_Shooting(status);
            std::cout << " ID Status  " << str2 << ": " << id << status << std::endl;
            str2.erase(0, 1);

            if (str2.empty()) {
                status = false;
                active = false;
                flag = !flag;
                std::cout << "Status " << str2 << ": " << status << std::endl;
            }
            this->getWord()->setString(str2);
            killed++;
            deltT[found]=t;
        } else {
            count++;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
int Entity::get_killed() {return Entity::killed;}
int Entity::get_count() {return Entity::count;}

bool Entity::isStatus() const {return this->status;}

void Entity::draw(WindowSize &windowSize, sf::RenderWindow &window) {
    auto pos = text->getPosition();
    this->active = true; /// this string is now being drawn on the window.
    window.draw(*text);}

void Entity::move(float delta, sf::Vector2f dir) {this->text->move(
        speed * delta * dir );}
size_t Entity::getsize() {return size;}
bool Entity::isActive() {return this->active;}

void Entity::stop() {
this->text->move(0.f,0.f);
}
void Entity::setId(int id) {
    this->id = id;
}
int Entity::getId() {
    return id;
}
bool Entity::isFlag() {
    return true;
}
void Entity::setStatus(bool status) {
    Entity::status = status;
}




