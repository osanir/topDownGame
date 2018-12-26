#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class GameSound{
    public:
        GameSound();
        void setSoundFile(string  soundFileName);
        void setMusicFile(string musicFileName);
        void playSound();
        void playMusic();
        void pauseMusic();
    private:
        SoundBuffer buffer;
        Sound sound;
        Music music;
};