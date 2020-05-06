//
// Created by aless on 13.03.2020.
//

#include "Feld.hpp"

void Feld::setHit() {
    Hitten = true;
}

void Feld::setShipHere() {
    hasShip = true;
}

bool Feld::isShipHere(){
    return hasShip;
}

bool Feld::isHitten() {
    return Hitten;
}

void Feld::setShipAdress(Schiffe* x) {
    Ship = x;
}

Schiffe *Feld::getShip() const {
    return Ship;
}
