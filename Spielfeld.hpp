//
// Created by aless on 12.03.2020.
//

#ifndef BATTLESHIPS_SPIELFELD_HPP
#define BATTLESHIPS_SPIELFELD_HPP


#include "Feld.hpp"
#include <iostream>

using namespace std;
class Spielfeld {

public:
    void printOwnField();
    Feld Playground[10][10];
    void printField();
};


#endif //BATTLESHIPS_SPIELFELD_HPP
