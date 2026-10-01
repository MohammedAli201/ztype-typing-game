
#include <fstream>
#include <iostream>
#include "Storage.h"

std::atomic<int> Storage::levelId;
Storage::Storage() {
    this->n = 0;
    this->counter = 0;
    this->wordList = new std::vector<EntityProxy *>;
    this->waves = new std::map < int, std::vector < EntityProxy * > * >;}

std::vector<EntityProxy *> *Storage::getWordList() {
    return wordList;}

Storage::~Storage() {
    for (auto const &pObj : *wordList) {
        delete pObj;
    }
    this->wordList = nullptr;
    for (auto const &it : *waves) {
        for (auto &vIt : *it.second) {
            delete vIt;
        }
    }
    for (auto const &it: *waves) {
        delete it.second;
    }

    delete this->waves;
    waves->clear();
    this->waves = nullptr;
};

void Storage::loadFile(const std::string &string) {
    std::ifstream words_File;
    std::string str;
    words_File.open(string);
    if (!font.loadFromFile("Resource/arial.TTF")) {
        std::cout << "error loading font file";
    }
    if (words_File.is_open()) {
        while (!words_File.eof()) {
            getline(words_File, str);
            auto *entityP = new EntityProxy(font, str);
            wordList->push_back(entityP);
        }
    }
}

std::map<int, std::vector < EntityProxy * > *> *
Storage::getWaves() {
    int random_num;
    srand(time(nullptr));
    std::vector<EntityProxy *> *lev = createLevel();
    if (waves->empty()) {
        level = lev;
    }
    /*populate level 1
    * */
    int range = INITIAL_SIZE + (MULTIPLIER * 0);
    while (level->size() < range) {
        random_num = rand() % (wordList->size() + 1);
        level->push_back((*wordList)[random_num]);
    }
    waves->insert(std::make_pair(0, level));
    ///* populate level 2*/
    range = (INITIAL_SIZE + (MULTIPLIER * n));
    std::vector<EntityProxy *> *lev1 = createLevel();
    while (lev1->size() < range) {
        random_num = rand() % (wordList->size() + 1);
        lev1->push_back((*wordList)[random_num]);
    }
    waves->insert(std::make_pair(n-1, lev1));

    ///*pupulate level 3

    range = INITIAL_SIZE + (MULTIPLIER * n);
    std::vector<EntityProxy *> *lev2 = createLevel();
    while (lev2->size() < range) {
        random_num = rand() % (wordList->size() + 1);
        lev2->push_back((*wordList)[random_num]);
    }
    waves->insert(std::make_pair(n-1, lev2));
    return this->waves;
}
std::vector<EntityProxy *> *Storage::createLevel() {
    //n = ++levelId;
    counter++;
    n = counter;
    return new std::vector<EntityProxy *>;
}

void Storage::dynamicLevels() {
    int random_num;
    /// first dynamic  level
    int range = INITIAL_SIZE + (MULTIPLIER * n);
    std::vector<EntityProxy *> *lev = createLevel();
    while (lev->size() < range) {
        random_num = rand() % (wordList->size() + 1);
        lev->push_back((*wordList)[random_num]);
    }
    waves->insert(std::make_pair(n-1, lev));
    /// second dynamic level
    range = INITIAL_SIZE + (MULTIPLIER * n);
    std::vector<EntityProxy *> *lev2 = createLevel();
    while (lev2->size() < range) {
        random_num = rand() % (wordList->size() + 1);
        lev2->push_back((*wordList)[random_num]);
    }
    waves->insert(std::make_pair(n-1, lev2));
}

int Storage::getLevelId() {
    return Storage::levelId;
}

int Storage::get_n() {
    return this->n;
}




