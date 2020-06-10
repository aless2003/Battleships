//
// Created by aless on 10.06.2020.
//

#include "AudioSystem.hpp"

void AudioSystem::playSound() {
    char audiofile_char[50] = {'M','u','s','i','c','.','w','a','v'};
    string audiofile_str;
    fstream fs;

    fs.open(audiofile_char, ios::in);
    audiofile_str = audiofile_char;
    PlaySound(audiofile_str.c_str(), NULL, SND_ASYNC);
    fs.close();
}
