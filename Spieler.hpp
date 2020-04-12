//
// Created by aless on 12.03.2020.
//

#ifndef BATTLESHIPS_SPIELER_HPP
#define BATTLESHIPS_SPIELER_HPP

#include <string>
#include "Spielfeld.hpp"
using namespace std;

class Spieler {
    string _Name;
public:
    Spielfeld Playfield;

    const string &getName() const;

    void setName(const string &name);
};


#endif //BATTLESHIPS_SPIELER_HPP
