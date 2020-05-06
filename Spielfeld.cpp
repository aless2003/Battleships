//
// Created by aless on 12.03.2020.
//


#include "Spielfeld.hpp"
//row - from left to right
//cols - from top to bottom
// row = [1] column = [2]
void Spielfeld::printOwnField() {
    int x = 'A';
    int rows =  sizeof Playground / sizeof Playground[0];
    int cols = sizeof Playground[0] / sizeof(Feld);
    for (int k = 0; k < rows; k++) {
        cout << "  " <<k + 1;
    }
    cout << endl;
    for (int i = 0; i < cols; i++) {
        cout << (char)x;
        x++;

        for (int j = 0; j < rows; j++) {
            if (Playground[j][i].isHitten() && Playground[j][i].isShipHere()){
                cout << "[x]";
            } else if (Playground[j][i].isHitten() && !Playground[j][i].isShipHere()) {
                cout << "[~]";
            } else if (Playground[j][i].isShipHere()){
                cout << "[S]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
}

void Spielfeld::printField(){
    int x = 'A';
    int rows =  sizeof Playground / sizeof Playground[0];
    int cols = sizeof Playground[0] / sizeof(Feld);
    for (int k = 0; k < rows; k++) {
        cout << "  " <<k + 1;
    }
    cout << endl;
    for (int i = 0; i < cols; i++) {
        cout << (char)x;
        x++;
        for (int j = 0; j < rows; j++) {
            if (Playground[j][i].isHitten() && Playground[j][i].isShipHere()){
                cout << "[x]";
            } else if (Playground[j][i].isHitten() && !Playground[j][i].isShipHere()) {
                cout << "[~]";
            } else {
                cout << "[ ]";
            }
        }
        cout << endl;
    }
}
