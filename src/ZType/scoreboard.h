#ifndef ZTYPE_SCOREBOARD_H
#define ZTYPE_SCOREBOARD_H
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "Machine.h"

class scoreboard: public State {
public:
    void NextState(Machine &context) override ;

    scoreboard(size_t const &score);

    scoreboard(size_t const &score, int const &level);

    ~scoreboard() override;

    Machine *machine;

private:
    bool true_newgame= false;
    bool restart = false;

    sf::Clock clock;
    sf::Texture texture;
    sf::Sprite background;
    sf::Font font;
    sf::Text txt1;
    sf::Text txt2;
    sf::Text txt3;

};


#endif //ZTYPE_SCOREBOARD_H
