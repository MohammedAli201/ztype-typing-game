#ifndef ZTYPE_ACTIONLISTENER_H
#define ZTYPE_ACTIONLISTENER_H
#include <conio.h>
#include <cstdio>
#include <SFML/Graphics.hpp>

class ActionListener {
public:
    char asci;

    void typeEvent(sf::Event &event) {
        if (!kbhit()) {

            int key_press = event.key.code;

            int asciiVal = (key_press % 26) + 97;
            asci = asciiVal;
        }
    }

};
#endif //ZTYPE_ACTIONLISTENER_H
