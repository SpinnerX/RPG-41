#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class SoundFX {
    
    public:
    SoundFX() {}

        void playSound(int num) {
            switch(num){
                case 1:
                    buffer.loadFromFile("Game/assets/sounds/shootingSound.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                    //std::cout << "case 1 " << std::endl;
                    break;
                case 2:
                    buffer.loadFromFile("Game/assets/sounds/menuTrack.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                    //std::cout << "case 2" << std::endl;
                    break;
                case 3:
                    buffer.loadFromFile("Game/assets/sounds/gametrack.wav");
                    sound.setBuffer(buffer);
                    sound.play();
            }
        }

        void stopSound() {
            sound.stop();
        }

    private:
    sf::Sound sound;
    sf::SoundBuffer buffer;
};