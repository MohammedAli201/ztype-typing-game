#include "GameManager.h"
#include "Storage.h"
#include "Entity.h"
#include <algorithm>
#include <cmath>

class Bullet;

class EntityProxy;

//todo: upadate after collision, change levels.
GameManager::GameManager() {
    this->initWindow();
    this->levelId = 0;
    this->targetKey = 0;
    this->Game_running = true;

}

void GameManager::initWindow() {
    ///creating texture for Mute button
    if (!background.loadFromFile("source/image/background.png")) {
        cout << " error " << endl;
    }


    backgroundSprite.setTexture(background);
    backgroundSprite.setColor(Color::Blue);
    /// creating window dynamically and must delete it after its closed.
    this->window = new RenderWindow(VideoMode(windowSize.screenWidth, windowSize.screenHeight), "Type Shooting");
    this->window->setVerticalSyncEnabled(true);
    this->window->setFramerateLimit(60);

    if(!mutePic.loadFromFile("source/image/mute.jpg")){
        cout<<"Error"<<endl;
    }
    mutePicSprite.setPosition(0, 0);
    mutePicSprite.setTexture(mutePic);
    mutePicSprite.setScale(0.2, 0.2);
    this->clock.restart();
}

GameManager::~GameManager() {
    delete this->window;
    delete this->storage;
    for (auto n:*active) {
        delete n;
    }
    this->active->clear();
    delete this->trig;
}

void GameManager::updateEvents() {
    /// handles the events that can happen
    while (this->window->pollEvent(this->event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->window->close();
                this->Game_running = false;
            case sf::Event::KeyPressed:
                noTyping = false;
                status = true;
                listener.typeEvent(event);
                std::cout << "ASCII character typed: " << listener.asci << std::endl;

                if (targetKey == 0) {
                    /// The target is zero choose from the active keys.
                    bullet.push_back(trig);
                    targetKey = min_num(listener.asci);

                    for (auto &i : *active) {
                        std::cout << "key" << i->getId() << std::endl;
                        if (targetKey == i->getId()) {
                            text = i->getWord();
                            i->erase_killedChar(listener.asci, *trig);
                            trig->UnitVector(i->getWord());
                        }
                    }
                } else {
                    /// the target is not zero. There is a target to shoot at.
                    for (auto &i : *active) {
                        std::cout << "key" << i->getId() << std::endl;
                        if (targetKey == i->getId()) {
                            i->erase_killedChar(listener.asci, *trig);
                            text = i->getWord();
                            trig->UnitVector(i->getWord());

                            if (!i->getStatus()) {
                                /// if the word is erased completely, reset the target key to zero
                                /// and choose other target .
                                targetKey = 0;
                                destroyed--;
                                if (destroyed == 0) {
                                    /// all the words are completely destroyed. Get the next level.
                                    int nextlevel = levelId +1;
                                    this->score = new scoreboard(Entity::get_killed(), nextlevel+1);
                                    std::cout<<"Level" << levelId << "finished";
                                    levelId++;
                                    this->update();
                                }
                            }
                        }
                    }

                    break;
                    default:
                        break;
                }
        }

    }
}

void GameManager::update() {
    /// this update the state variables
    /// and active vector before proceeding to the next level.
    this->active->clear();
    this->nwords = 0;
    this->changeLevel();
    this->destroyed = lev->size();
    wordClock.restart();

}

void GameManager::runGame() {
    ///adds background Music
    if(!music.openFromFile("Resource/intromusic.wav")){
        cout<<"Error"<<endl;
    }
    music.play();
    music.setLoop(true);


    this->LoadWords();  /// load words
    this->load(); /// load word to levels and get more words if nedded.
    while (Game_running) {
        elapsed = clock.restart().asSeconds() / 60;
        while (this->window->isOpen()) {
            clock.restart();
            this->updateEvents();
            this->window->clear();
            this->render();
            this->window->display();

            ///applying the mouse for the mute button
            if (event.type == Event::MouseButtonPressed) {
                if (mutePicSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)))) {

                    if (mute ) {
                        music.pause();
                        mute = false;

                    } else {
                        mute = true;
                        music.play();
                    }

                }
            }

        }
        std::cout << "killed: " << EntityProxy::get_killed();
        std::cout << "\nmissed: " << EntityProxy::get_count();
    }
    std::cout << "\n returnig to menus";

}

int GameManager::random_pos() {
    srand(time(nullptr));
    return (int) (rand() % (lev->size() + 1));
}

void GameManager::render() {
    ///drawing Words , bullets, and weapon.
    window->draw(backgroundSprite);
    window->draw(mutePicSprite);

    for (auto &i : *active) {
        /// move the enemies toward the weapon.
        direction = (weapon.getPositon() - i->getWord()->getPosition());
        normalize(direction);
        i->move(elapsed, direction);
        (*i).draw(windowSize, *window);

        if (i->getWord()->getGlobalBounds().intersects(weapon.getBounds())) {
            ///restarting the game after collision with the shooter.
            this->score = new scoreboard(Entity::get_killed());
            Game_running = false;
            music.pause();
            mute= false;

            window->close();
            reset_game();
            return;
        }
    }
    if (wordClock.getElapsedTime().asSeconds() > 7) {
        /// get waves after a the condition above is met.
        this->load();

        for (int i = nwords - 3; i < active->size(); i++) {
            ///move the enemies toward the weapon.
            direction = (weapon.getPositon() - (*active)[i]->getWord()->getPosition());
            normalize(direction);
            (*active)[i]->move(elapsed, direction);
            (*active)[i]->draw(windowSize, *window);

            if ((*active)[i]->getWord()->getGlobalBounds().intersects(weapon.getBounds())) {
                ///restarting the game after collision with the shooter.
                this->score = new scoreboard(Entity::get_killed());
                Game_running = false;

                window->close();
                reset_game();
                return;
            }
        }
        clock.restart();
    }

    weapon.draw(windowSize, *window);
    trig = new Bullet(windowSize, window);
    manager = new SoundManager();
    s.push_back(manager);
    if (((status && targetKey != 0) && (Entity::deltT[0] == listener.asci))) {
        for (auto &i : s) {
            i->playFire();
        }

        if (bullet.empty()) {
            bullet.push_back(trig);
        }
        for (auto &k : bullet) {
            k->draw(windowSize, *window);
            k->UnitVector(text);
            k->moveBullet(elapsed);
            k->setTarget_Shooting(shooting);
        }
    }
    ///Erase after bullet is collided the word on the screen
    auto it = bullet.begin();
    for (int k = 0; k < bullet.size(); ++k) {
        if (bullet[k]->finder_Collision) {
            it = bullet.erase(it);
            noTyping = true;
        }
    }
    if (noTyping) {
        status = false;
    }
}

void GameManager::LoadWords() {
    ///the first time words are loaded from the file, get a font and then
    /// divided in to levels as necessary.
    storage = new Storage();
    active = new std::vector<EntityProxy *>;
    storage->loadFile("Resource/Dictionary.txt");
    waves = storage->getWaves();
    lev = (*waves)[levelId];
    destroyed = lev->size(); // the number of destroyed words.

}

void GameManager::changeLevel() {
    /// change of levels is performed here.
    lev = (*waves)[levelId];
    int waveSize = waves->size() - 2;
    for (int i = 0; i < 3; i++) {
        activkeys[i] = (*(*lev)[i]).getId();
        active->push_back((*lev)[i]);
        nwords++;
    }
    ///dynamically generating levels.
    if (levelId == waveSize) {
        storage->dynamicLevels();
    }

}

Vector2<float> GameManager::normalize(Vector2<float> dir) {
    /// normalise the direction by calculating distance between to entities.
    float hyp = sqrt(direction.x * direction.x + direction.y * direction.y);
    dir.x /= hyp;
    dir.y /= hyp;
    return dir;
}

bool GameManager::keyFound(int key) {
    for (int activkey : activkeys) {
        if (activkey == key)
            return true;
    }
}

bool GameManager::target(int key) {
    return targetKey = key;
}

void GameManager::setTarget(int key) {
    this->targetKey = key;
}

bool GameManager::compare(int i, int j) {
    return i < j;
}

int GameManager::getTargetKey() {
    return this->targetKey;
}

int GameManager::min_num(char t) {
    ///*This block  sets a single target, by choosing a key if
    /// *multiple entities start by the same alphabet.*/

    /// array that holds texts that start with the same alphabet.
    int priority[4] = {};

    for (int i = 0; i < active->size(); i++) {
        size_t found = (*active)[i]->getWord()->getString().find(t);
        if (found == 0) {
            priority[i] = (*active)[i]->getId();
            targetKey = (*active)[i]->getId();
        }
    }


    for (int i = -1; i < sizeof(priority) / sizeof(int); i++) {
        /// if this array holds elements setup one to be the target key.
        if (priority[i] <= targetKey) {
            targetKey = priority[i];
        }
    }
    return targetKey;
}

void GameManager::load() {
    /// this code is a loader. that loads words to be drawn on the window.
    wordClock.restart();
    int temp = nwords;
    for (int i = temp; i < temp + 3; i++) {
        if (i < lev->size()) {
            active->push_back((*lev)[i]);
            nwords++;
        } else {
            break;
        }
    }
}

///resett state variables to initialization state
void GameManager::reset_game() {
    this->active->clear();
    this->nwords = 0;
    levelId = 0;
    targetKey = 0;
    destroyed = 0;
    shooting = true;
    noTyping = false;
    waves->clear();
    waves = storage->getWaves();
    lev = (*waves)[levelId];
    destroyed = lev->size();
}













