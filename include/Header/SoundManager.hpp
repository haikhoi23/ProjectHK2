#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP
#include <SDL_mixer.h>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool loadSounds();
    void playChargeSound();
    void playCollisionSound();
    void playHoleSound();
    void cleanup();

private:
    Mix_Music* chargeSound;
    Mix_Music* collisionSound;
    Mix_Music* holeSound;
};

#endif 
