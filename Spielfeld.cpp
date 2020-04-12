//
// Created by aless on 12.03.2020.
//


#include "Spielfeld.hpp"
//row - from left to right
//cols - from top to bottom
// row = [1] column = [2]
void Spielfeld::printOwnField() {
    int rows =  sizeof Playground / sizeof Playground[0];
    int cols = sizeof Playground[0] / sizeof(Feld);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (Playground[i][j].isHitten() && Playground[i][j].isShipHere()){
                cout << "[x]";
            } else if (Playground[i][j].isHitten() && !Playground[i][j].isShipHere()) {
                cout << "[~]";
            } else if (Playground[i][j].isShipHere()){
                cout << "[S]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
}

void Spielfeld::printField(){
    int rows =  sizeof Playground / sizeof Playground[0];
    int cols = sizeof Playground[0] / sizeof(Feld);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (Playground[i][j].isHitten() && Playground[i][j].isShipHere()){
                cout << "[x]";
            } else if (Playground[i][j].isHitten() && !Playground[i][j].isShipHere()) {
                cout << "[~]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
}
