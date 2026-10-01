#ifndef ZTYPE_STORAGE_H
#define ZTYPE_STORAGE_H
#include <vector>
#include <map>
#include <atomic>
#include "EntityProxy.h"
#define INITIAL_SIZE 6
#define MULTIPLIER 3

class EntityProxy;
class Storage {
public:
    Storage();
    ~Storage();
    void loadFile(const std::string &string);
    std::vector<EntityProxy *>* getWordList();
    std::map<int, std::vector<EntityProxy *> *> * getWaves();
    std::vector<EntityProxy*> *createLevel();

    void dynamicLevels(); // creates and populate a level.
    int get_n();
private:
    static int getLevelId();
    static std::atomic<int> levelId;
    int counter;
protected:
    int n; // number of levels
    sf::Font font;
    std::vector<EntityProxy*> *level= nullptr;
    std::vector<EntityProxy*> *wordList = nullptr;
    std::map<int,std::vector<EntityProxy*>*> *waves = nullptr;
};


#endif //ZTYPE_STORAGE_H
