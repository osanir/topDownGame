#include "../include/GameSound.h"

GameSound::GameSound(){

    //pass
}

void GameSound::setSoundFile(string  soundFileName){

    if(!buffer.loadFromFile(soundFileName)){
        cout<<"DOSYA BULUNAMADIyy"<<endl;
    }   
    sound.setBuffer(buffer);
}

void GameSound::setMusicFile(string musicFileName){
    if(!music.openFromFile(musicFileName)){
        cout<<"DOSYA BULUNAMADIxx"<<endl;
    }
}
void GameSound::playSound(){
        sound.play();
}
void GameSound::playMusic(){
        music.play();
}
void GameSound::pauseMusic(){
        music.pause();
}