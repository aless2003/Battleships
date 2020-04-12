//
// Created by aless on 12.03.2020.
//

#include "Spieler.hpp"

void Spieler::setName(const string &name) {
    _Name = name;
}

const string &Spieler::getName() const {
    return _Name;
}
