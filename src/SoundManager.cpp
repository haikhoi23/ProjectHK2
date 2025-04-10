#include "Header/SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager(){
    chargeSound = nullptr;
    collisionSound = nullptr;
    holeSound = nullptr;
}

SoundManager::~SoundManager(){
    cleanup();
}

bool SoundManager::loadSounds(){
    chargeSound = Mix_LoadMUS("sfx/res_sfx_charge.mp3");
    collisionSound = Mix_LoadMUS("sfx/res_sfx_swing.mp3");
    holeSound = Mix_LoadMUS("sfx/res_sfx_hole.mp3");
    if (!chargeSound || !collisionSound || !holeSound) {
        std::cerr << "Failed to load sound files!" << std::endl;
        return false;
    }
    return true;
}

void SoundManager::playChargeSound(){
    if (chargeSound){
        Mix_PlayMusic(chargeSound, 0);
    } else {
        std::cerr << "Charge sound is null!" << std::endl;
    }
}
void SoundManager::playCollisionSound(){
    if (collisionSound){
        Mix_PlayMusic(collisionSound, 0);
    } else {
        std::cerr << "Collision sound is null!" << std::endl;
    }
}
void SoundManager::playHoleSound(){
    if (holeSound){
        Mix_PlayMusic(holeSound, 0);
    } else {
        std::cerr << "Hole sound is null!" << std::endl;
    }
}
void SoundManager::cleanup(){
    if (chargeSound) {
        Mix_FreeMusic(chargeSound);
        chargeSound = nullptr;
    }
    if (collisionSound) {
        Mix_FreeMusic(collisionSound);
        collisionSound = nullptr;
    }
    if (holeSound) {
        Mix_FreeMusic(holeSound);
        holeSound = nullptr;
    }
}