#ifndef ZTYPE_GAMEMANAGER_H
#define ZTYPE_GAMEMANAGER_H
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <iostream>
#include "EntityProxy.h"
#include "weapon.h"
#include "bullet.h"
#include "ActionListener.h"
#include "Sound/SoundManager.h"
#include "scoreboard.h"
#include <list>

using namespace std;
using namespace sf;
class Object;
class Storage;

class GameManager {
    friend class EntityProxy;
protected:
    Weapon weapon;
    scoreboard *score = nullptr;
    Bullet *trig= nullptr;
    std::vector<Bullet*> bullet; /// Vector that will hold bullets.
    Storage *storage; /// container of words and levels.
    std::vector<EntityProxy *> *lev = nullptr; /// level that holds the vectors to be drawn.
    std::vector<EntityProxy *> *active = nullptr; /// active objects.
    std::map<int, std::vector<EntityProxy *> *> *waves = nullptr;
    Text *text;
    Event event;
    ActionListener listener;
    WindowSize windowSize;
    Clock clock;
    Clock wordClock;
    Vector2f direction;
    float elapsed;
    int random_pos();
    int activkeys[4] = {}; /// array that holds active objectsId;
    int targetKey; /// key of isolated target.
    int nwords = 0; /// number of active words
    int levelId; ///level id.
    int destroyed = 0; /// destroyed words.

    Texture mutePic;
    Sprite mutePicSprite;
    Music music;

protected:
    void initWindow();

public:
    RenderWindow *window;

    GameManager();
    ~GameManager();
    void updateEvents();
    void update();
    void runGame();
    void LoadWords();
    int min_num(char t); /// returns a targetKey to shoot if strings start with the same alphabet.
    bool keyFound(int key); /// returns true if the key is found in ActiveKeys[].
    bool compare(int i, int j);
    void render();
    void changeLevel(); /// changes levels.
    void load(); /// release 3 words.
    void reset_game();
    Vector2<float> normalize(Vector2<float> direction);
    bool target(int key);
    void setTarget(int key);
    bool status = false;
    bool Game_running= false;
    bool shooting = true;
    bool noTyping= false;
    int getTargetKey();
    bool mute = true;

    sf::Shader m_background;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    SoundManager *manager = nullptr;
    vector<SoundManager*> s;


};

#endif //ZTYPE_GAMEMANAGER_H
