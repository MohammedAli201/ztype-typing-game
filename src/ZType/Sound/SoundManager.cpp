#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager()
{// Load the sound in to the buffers
    m_FireBuffer.loadFromFile( "Resource/fire_bow_sound-mike-koenig.wav");

    m_ReachGoalBuffer.loadFromFile("Resource/fire_bow_sound-mike-koenig.wav");
    // The sound reduces steadily as the player moves further away
    //float minDistance = 10;
    float attenuation = 10;
    m_Fire1Sound.setAttenuation(attenuation);
    //m_Fire1Sound.setMinDistance(minDistance);


    m_Fire1Sound.setBuffer(m_FireBuffer);
    m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

}

void SoundManager::playFire()
{
    m_Fire1Sound.setRelativeToListener(true);
    if (m_Fire1Sound.getStatus() == Sound::Status::Stopped)
    {
        // Play the sound, if its not already
        m_Fire1Sound.play();
    }

}

void SoundManager::playReachGoal()
{
    m_ReachGoalSound.setRelativeToListener(true);
    m_ReachGoalSound.play();
}