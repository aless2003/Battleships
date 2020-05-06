//
// Created by aless on 12.03.2020.
//

#include "Schiffe.hpp"

Schiffe* Schiffe::createDestroyer() {
    auto* Destroyer = new Schiffe(3);
    return Destroyer;
}

Schiffe::Schiffe(int size) : _size(size) {
    _size = size;
}

Schiffe* Schiffe::createSubmarine() {
    auto* Submarine = new Schiffe(2);
    return Submarine;
}

Schiffe* Schiffe::createCarrier() {
    auto* Carrier = new Schiffe(5);
    return Carrier;
}

Schiffe* Schiffe::createBattelship() {
    auto* Battleship = new Schiffe(4);
    return Battleship;
}

Schiffe::Schiffe() {

}

int Schiffe::getSize() const {
    return _size;
}

int Schiffe::getHitsTaken() const {
    return _hitsTaken;
}

void Schiffe::intHitsTaken() {
    _hitsTaken = 0;
}

void Schiffe::increaseHit() {
    _hitsTaken++;
}


