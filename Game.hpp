//
// Created by aless on 12.03.2020.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

#include "Spieler.hpp"
#include "Schiffe.hpp"
#include "Design.hpp"

class Game {
private:
    struct coos{
        vector <int> x, y;
    };
    Spieler* Player1 = new Spieler();
    Spieler* Player2 = new Spieler();
    bool isPlacementPossible(Spieler*, int, int, int);
    bool placeNextRight(coos,int,int,Spieler *, char);
    char saveDirection(coos,int, int);
    void placeShip(const Schiffe *, int, int, Spieler*);
    void intPlayer(Spieler*);
    char InputChar(const string &currentShip, bool) const;
public:
    void initialize();
    void play();
    bool findWinner(Spieler*);
    void printPlayerData();
    void shoot(int, int, Spieler*);
    void run();

    virtual ~Game();


    int InputInt(const string &currentShip, bool) const;

    void UserInput(const string &currentShip, char &tempChar, int &tempNum, bool) const;
};


#endif //BATTLESHIPS_GAME_HPP
