//
// Created by Alex on 12.03.2020.
//

#include <unistd.h>
#include "Design.hpp"

void Design::printRules(){

    cout << "Welcome to the best Battleships Program in the whole universe!" << endl;
    cout << "Zuerst starten wir mit den Regeln." << endl;
    sleep(1);
    cout << "1. Regel: ";
    cout << "Die Schiffe duerfen nicht aneinanderstossen." << endl;
    sleep(1);
    cout << "2. Regel: ";
    cout << "Die Schiffe duerfen nicht über Eck gebaut sein oder Ausbuchtungen besitzen." << endl;
    sleep(1);
    cout << "3. Regel: ";
    cout << "Die Schiffe duerfen auch am Rand liegen." << endl;
    sleep(1);
    cout << "4. Regel: ";
    cout << "Die Schiffe duerfen nicht diagonal aufgestellt werden." << endl;
    sleep(1);
    system("cls");
}
