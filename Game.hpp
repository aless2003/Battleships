//
// Created by aless on 12.03.2020.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

#include "Spieler.hpp"
#include "Schiffe.hpp"
#include <windows.h>
#include "AudioSystem.hpp"
#include <thread>

class Game {
private:
    struct coos{
        vector <int> x, y;
    };
    Spieler* Player1 = new Spieler();
    Spieler* Player2 = new Spieler();
    static bool isPlacementPossible(Spieler*, int, int, int);
    static bool placeNextRight(coos,int,int,Spieler *, char);
    static char saveDirection(coos,int, int);
    static void placeShip(const Schiffe *, int, int, Spieler*);
    static void intPlayer(Spieler*) ;
    static void intPlayerFast(Spieler*);
    //Overloading for Fast Placement
    static bool isPlacementPossible(Spieler*, int, int, int, char);
    static char InputChar(const string &currentShip, bool) ;
    static int InputInt(const string &currentShip, bool) ;
    //Overloading für shoot Eingabe
    static int InputInt(const string&);
    static char InputChar(const string&);
    static char InputDirection();
    static bool setFastMode();
    static bool findWinner(Spieler*);
    static void shoot(int, int, Spieler*);
    static void winningMessage(Spieler*, Spieler*);
    //Overloading für Shoot Eingabe
    static void UserInput(char &tempChar, int &tempNum);
    static void UserInput(const string &currentShip, char &tempChar, int &tempNum, bool) ;
    //Overloading für Fast User Init
    static void UserInput(const string& Ship,char &tempChar, int &tempNum, char &direction);
    static void printRules();
public:
    void initialize();
    void play();
    void run();
    virtual ~Game();
};


#endif //BATTLESHIPS_GAME_HPP
