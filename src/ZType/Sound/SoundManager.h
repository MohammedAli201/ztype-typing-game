#ifndef ZTYPE_SOUNDMANAGER_H
#define ZTYPE_SOUNDMANAGER_H

#include <SFML/Audio.hpp>
using namespace sf;

    class SoundManager {
    public:
        // The Sounds
        Sound m_Fire1Sound;
        // The buffers
        SoundBuffer m_FireBuffer;
        // Sound m_Fire2Sound;
        Sound m_ReachGoalSound;
    private:
        SoundBuffer m_ReachGoalBuffer;


    public:

        SoundManager();

        void playFire();
        void playReachGoal();

};


#endif //ZTYPE_SOUNDMANAGER_H
