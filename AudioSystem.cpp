//
// Created by aless on 10.06.2020.
//


#define nameLength 260

#include <vector>
#include <array>
#include "AudioSystem.hpp"

void AudioSystem::playSound() {
    int SongCounter = 0;

    vector<array<char, nameLength>> MusicVec;
    char MusicArr[10][nameLength];
    array<char, 260> temp{};
    char audiofile_char[nameLength] = {'.', '/', 'A','u','d', 'i', 'o','/'};
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (".\\Audio")) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != nullptr) {
            if (ent->d_namlen > 2) {
                for (int i = 0; i < ent->d_namlen; i++) {
                    temp[i] = ent->d_name[i];
                }
                //MusicArr[SongCounter][ent->d_namlen] = '\0';
                temp[ent->d_namlen] = '\0';
                MusicVec.push_back(temp);
                SongCounter++;
            }
        }
        closedir (dir);
    }


    

    
    string audiofile_str;
    fstream fs;


    for (int i = 0; i < SongCounter; i++) {
        for (int j = 8; j < nameLength; j++) {
            audiofile_char[j] = MusicVec[i][j - 8];
        }
        audiofile_str = audiofile_char;
        fs.open(audiofile_str, ios::in);
        if (!PlaySound(audiofile_str.c_str(), nullptr, SND_SYNC)) {
            Sleep(10000);
        }
        if (i == SongCounter-1) {
            SongCounter = 0;
        }
        fs.close();

    }
}
