//
// Created by aless on 12.03.2020.
//

#ifndef BATTLESHIPS_SCHIFFE_HPP
#define BATTLESHIPS_SCHIFFE_HPP

using namespace std;

#include <vector>

class Schiffe {
    int _size;
    int _hitsTaken;
public:
    void intHitsTaken();
    void increaseHit();
    Schiffe(int size);
    Schiffe();
    Schiffe * createSubmarine();
    Schiffe* createDestroyer();
    Schiffe * createCarrier();
    Schiffe * createBattelship();

    int getHitsTaken() const;

    int getSize() const;
};


#endif //BATTLESHIPS_SCHIFFE_HPP
