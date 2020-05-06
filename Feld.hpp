//
// Created by aless on 13.03.2020.
//

#ifndef BATTLESHIPS_FELD_HPP
#define BATTLESHIPS_FELD_HPP


#include "Schiffe.hpp"

class Feld {
    bool hasShip;
    bool Hitten;
    Schiffe* Ship = NULL;
public:
    bool isShipHere();
    void setShipHere();
    void setHit();
    bool isHitten();
    void setShipAdress(Schiffe*);

    Schiffe *getShip() const;
};


#endif //BATTLESHIPS_FELD_HPP
