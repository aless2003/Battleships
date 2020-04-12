//
// Created by Alex on 12.03.2020.
//

#include "Design.hpp"

void Design::printRules(){

    cout << "Welcome to the best Battleships Program in the whole universe!" << endl;
    _sleep(5000);
    cout << "Zuerst starten wir mit den Regeln." << endl;
    _sleep(7000);
    system("cls");
    cout << "Nachdem die Regeln geprintet wurden, wird ein kleiner Test durchgefuehrt um sicherzustellen das Sie die Regeln verstanden haben." << endl;
    _sleep(500);
    system("cls");
    cout << "1. Regel: ";
    cout << "Die Schiffe duerfen nicht aneinanderstossen." << endl;
    _sleep(7000);
    system("cls");
    cout << "2. Regel: ";
    cout << "Die Schiffe duerfen nicht über Eck gebaut sein oder Ausbuchtungen besitzen." << endl;
    _sleep(7000);
    system("cls");
    cout << "3. Regel: ";
    cout << "Die Schiffe duerfen auch am Rand liegen." << endl;
    _sleep(7000);
    system("cls");
    cout << "4. Regel: ";
    cout << "Die Schiffe duerfen nicht diagonal aufgestellt werden." << endl;
    _sleep(7000);
    system("cls");

}
