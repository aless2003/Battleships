//
// Created by aless on 12.03.2020.
//


#include "Game.hpp"
void Game::run() {
    initialize();
    play();
}

void Game::initialize() {
    bool fast = false;

    fast = setFastMode();

    string tempName;
    cout << "Player 1 can place his Ships" << endl << "Type in your Name and Press Enter to show your field - make sure your opponent isn't looking on the Screen!" << endl;
    cin >> tempName;
    Player1->setName(tempName);
    Player1->Playfield.printOwnField();
    if (!fast) {
        intPlayer(Player1);
    } else {
        intPlayerFast(Player1);
    }
    system("cls");
    cout << "Player 2 can place his Ships" << endl << "Type in your Name and Press Enter to show your field - make sure your opponent isn't looking on the Screen!" << endl;
    cin >> tempName;
    Player2->setName(tempName);
    Player2->Playfield.printOwnField();
    if (!fast) {
        intPlayer(Player2);
    } else {
        intPlayerFast(Player2);
    }
}

void Game::intPlayer(Spieler* Player) {
    char tempChar;
    int tempNum = 0 , size = 0;
    string currentShip;
    Schiffe tempShip;
    Schiffe* tempShipAdress = nullptr;
    int lastY = 0, lastX = 0;
    char direction = 'N';

    Game::coos temp;
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            currentShip = "Carrier";
            tempShipAdress = tempShip.createCarrier();
            size = 5;
        } else if (i > 0 && i < 3) {
            currentShip = "Battleship";
            tempShipAdress = tempShip.createBattelship();
            size = 4;
        } else if (i > 2 && i < 6) {
            currentShip = "Destroyer";
            tempShipAdress = tempShip.createDestroyer();
            size = 3;
        } else {
            currentShip = "Submarine";
            tempShipAdress = tempShip.createSubmarine();
            size = 2;
        }

        do {
            UserInput(currentShip, tempChar, tempNum, false);
        } while (!isPlacementPossible(Player, size, tempNum - 1, tempChar - 65));
        int x = tempNum - 1;
        int  y = tempChar - 65;
        placeShip(tempShipAdress, x, y, Player);
        cout << "Its Working!";
        temp.y.push_back(y);
        temp.x.push_back(x);
        //Restliche Teile
        for (int j = 0; j < size - 1; j++) {
            do{
                UserInput(currentShip, tempChar, tempNum, true);
            } while (!placeNextRight(temp, tempNum - 1, tempChar - 65, Player, direction));
            x = tempNum - 1;
            y = tempChar - 65;
            if (j == 0) {
                direction = saveDirection(temp,x,y);
            }
            placeShip(tempShipAdress, x, y, Player);
            Player->shipAdressVector.push_back(tempShipAdress);
            temp.x.push_back(x);
            temp.y.push_back(y);
        }
        temp.y.clear();
        temp.x.clear();
        direction = 'N';
        tempShipAdress->intHitsTaken();
    }
}

void Game::UserInput(const string &currentShip, char &tempChar, int &tempNum, bool isPart) {
    tempChar = InputChar(currentShip, isPart);
    tempNum = InputInt(currentShip, isPart);
}

int Game::InputInt(const string &currentShip, bool isPart) {
    int tempNum = 0;
    do {
        if(isPart) {
            cout << "Type the Vertical Coordinate of the next Part of you Ship (" << currentShip << ") [1-10]";
        }else{
            cout << "Type the Vertical Coordinate of the Ship (" << currentShip << ") [1-10]";
        }

        cin >> tempNum;
        try {
            if(cin.fail()){
                throw ("Error. Invalid Input. You can only enter Numbers");
            }
        } catch(const char* error){
            cout << error << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            tempNum = 11;
        }

        /*
         * Old.Version
        cin >> tempNum;
        while (cin.fail())
        {
            cin.clear(); // clears input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "You can only enter numbers.\n";
            tempNum = 11;
        }
         */
    } while ((tempNum < 1 || tempNum > 10) );
    return tempNum;
}

char Game::InputChar(const string &currentShip, bool isPart) {
    char tempChar;
    do {
        if(isPart) {
            cout << "Type the Horizontal Coordinate of the next Part of you Ship (" << currentShip << ") [A-J]";
        }else{
            cout << "Type the Horizontal Coordinate of the Ship (" << currentShip << ") [A-J]";
        }
        cin >> tempChar;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

    } while (tempChar < 'A' || tempChar > 'J');
    return tempChar;
}

bool Game::isPlacementPossible(Spieler* Player, int size, int row, int column) {
    bool x = false;
    bool y = false;
    bool temp = true;

    if (Player->Playfield.Playground[row][column].isShipHere()) {
        // Ist der Ort überhaupt Frei?
        return false;
    } else {
        for (int i = 0; i < 2 && !(x && y); i++) {
            if (i == 0 && !x) {
                for (int j = 1; j <= size && temp; j++) {
                    if (row + j == 10) {
                        temp = false;
                    } else {
                        temp = !Player->Playfield.Playground[row + j][column].isShipHere();
                    }
                }
                x = temp;
            } else if (i == 1 && !x) {
                temp = true;
                for (int j = 1; j <= size && temp; j++) {
                    if (row - j < 0){
                        temp = false;
                    } else{
                        temp = !Player->Playfield.Playground[row - j][column].isShipHere();
                    }
                }
                x = temp;
            }

            if (i == 0 && !y) {
                temp = true;
                for (int j = 1; j <= size && temp; j++) {
                    if (column + j == 10) {
                        temp = false;
                    } else {
                        temp = !Player->Playfield.Playground[row][column + j].isShipHere();
                    }
                }
                y = temp;
            } else if (i == 1 && !y) {
                temp = true;
                for (int j = 1; j <= size && temp; j++) {
                    if (column - j < 0){
                        temp = false;
                    } else {
                        temp = !Player->Playfield.Playground[row][column - j].isShipHere();
                    }
                }
                y = temp;
            }
        }
    }
    return x || y;
}

bool Game::placeNextRight(coos temp, int row, int column, Spieler * Player, char direction) {
    bool isValidX = false;
    bool isValidY = false;
    bool secondOnSameSpace = false;
    if (!Player->Playfield.Playground[row][column].isShipHere()) {
        for (int i = 0; i < temp.y.size() && !isValidY; i++) {
            if (direction == 'x') {
                isValidY = temp.y[i] + 1 == column || temp.y[i] - 1 == column;
            } else if(direction == 'y'){
                isValidY = temp.y[i] == column;
            } else if (temp.y[i] == column) {
                isValidY = true;
                secondOnSameSpace = true;
            }   else {
                isValidY = temp.y[i] + 1 == column || temp.y[i] - 1 == column;
            }
        }
        for (int i = 0; i < temp.x.size() && !isValidX; i++) {
            if (direction == 'y') {
                isValidX = temp.x[i] + 1 == row || temp.x[i] - 1 == row;
            } else if (direction == 'x'){
                isValidX = temp.x[i] == row;
            } else if(!secondOnSameSpace) {
                isValidX = temp.x[i] == row;
            } else{
                isValidX = temp.x[i] + 1 == row || temp.x[i] - 1 == row;
            }
        }
    } else {
        return false;
    }
    return isValidX && isValidY;
}

void Game::placeShip(const Schiffe * tempShipAdress, int x, int y, Spieler *Player) {
    Player->Playfield.Playground[x][y].setShipHere();
    Player->Playfield.Playground[x][y].setShipAdress(const_cast<Schiffe *>(tempShipAdress));
    Player->Playfield.printOwnField();
}

void Game::play() {
    bool won = false;
    char tempChar = ' ';
    bool hitValid = false;
    int x = 0, y = 0;
    Spieler* Enemy = nullptr;
    Spieler* Player = nullptr;
    string name;
    int tempNum = 0;
    int currentPlayer = 0;
    //erstellt die erste Value von currentPlayer für die Auswahl des Spielers.
    currentPlayer = rand() % 2 + 1;

    do{
        //Basierend auf der gerade gegebenen CurrentPlayer Value wird der derzeitige Spieler bestimmt
        if (currentPlayer == 1){
            Enemy = Player2;
            Player = Player1;
            //Current Player wird auf 0 gesetzt, damit im nächsten durchlauf der andere Spieler dran ist.
            currentPlayer = 0;
        } else {
            Player = Player2;
            Enemy = Player1;
            currentPlayer = 1;
        }
        //name des Spieler wird abgespeichert für text
        name = Player->getName();
        cout << endl << name <<" it's your Turn!" << endl;
        //Spielfeld des Gegners wird OHNE Schiffe ausgegeben um dem derzeitigen Spieler einen Überblick über die bisherigen Schüsse zu geben.
        Enemy->Playfield.printField();
        //Eingabe der Coos für den Schuss
        do {
            UserInput(tempChar, tempNum);
            x = tempNum - 1;
            y = tempChar - 65;
            //Ist an der Stelle schonmal geschossen worden?
            hitValid = Enemy->Playfield.Playground[x][y].isHitten();
            if (hitValid){
                cout << "No valid Coos, you shot there already >:(" << endl;
            }
            //wenn ja, dann wird der benutzer nochmal aufgefordert Coos einzugeben
        } while (hitValid);
        //Schuss wird ausgeführt
        shoot(x, y, Enemy);
        //Spieler tauschen Feld
        won = findWinner(Enemy);
        if (!won) {
            //Enter von Eingabe ignorieren
            cin.ignore();
            system("cls");
            Enemy->Playfield.printField();
            cout << "Press Enter to switch Boards" << endl;
            //Bestätigungsenter
            cin.ignore();
            system("cls");
        }
    } while (!won);
    winningMessage(Player, Enemy);
}

void Game::shoot(int x, int y, Spieler* Player) {
    Player->Playfield.Playground[x][y].setHit();
    Player->Playfield.Playground[x][y].getShip()->increaseHit();
}

bool Game::findWinner(Spieler *x) {
    bool noShipLeft = false;

        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                for(int i = 0; i < x->shipAdressVector.size(); i++){
                    if(x->Playfield.Playground[j][k].isShipHere()) {
                        if(x->Playfield.Playground[j][k].isHitten()) {
                            if (x->Playfield.Playground[j][k].getShip() == x->shipAdressVector[i]) {
                                if (x->shipAdressVector[i]->getHitsTaken() == x->shipAdressVector[i]->getSize()) {
                                    x->sunkenShips.push_back(x->shipAdressVector[i]);
                                    x->shipAdressVector.erase(x->shipAdressVector.begin() + i);
                                }
                            }
                        }
                    }
            }
        }
    }
    if (x->shipAdressVector.empty()) {
        noShipLeft = true;
    }
    return noShipLeft;
}

char Game::saveDirection(Game::coos First, int x, int y) {
    //directon -> in which direction you can set you ship parts
    char direction = 'N';
    if (First.x[0] == x ) {
        direction = 'x';
    } else if (First.y[0] == y) {
        direction = 'y';
    }
    return direction;
}

Game::~Game() = default;

void Game::UserInput(char &tempChar, int &tempNum) {
    string msg1 = "Type the Horizontal Coordinate of your shooting guess [1-10]:";
    string msg2 = "Type the Vertical Coordinate of your shooting guess [A-J]:";
    tempChar = InputChar(msg2);
    tempNum = InputInt(msg1);
}

int Game::InputInt(const string& message){
    int tempNum = 0;
    do {
        cout << message;
        cin >> tempNum;
        try{
            if (cin.fail()){
                throw ("Error. Invalid Input. You can only Enter Numbers.");
            }
        } catch (const char* error) {
            cout << error << endl;
            cin.clear();
            cin.ignore();
            tempNum = 11;
        }
        /*
         * Old.Version
        while (cin.fail())
        {
            cin.clear(); // clears input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "You can only enter numbers.\n";
            tempNum = 11;
        }
         */
    } while ((tempNum < 1 || tempNum > 10));
    return tempNum;
}

char Game::InputChar(const string& message) {
    char tempChar;
    do {

        cout << message;
        cin >> tempChar;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

    } while (tempChar < 'A' || tempChar > 'J');
    return tempChar;
}

void Game::winningMessage(Spieler *Player, Spieler *Enemy) {
    const string& name = Player->getName();
    const string& enemyName = Enemy->getName();
    cout << "Congratulations " << name << ", you have beaten " << enemyName << "!" << endl;
    sleep(1000);
    cin.ignore();
    cin.ignore();
}

void Game::intPlayerFast(Spieler* Player) {
    char tempChar;
    int tempNum = 0 , size = 0;
    string currentShip;
    Schiffe tempShip;
    char direction;
    Schiffe* tempShipAdress = nullptr;
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            currentShip = "Carrier";
            tempShipAdress = tempShip.createCarrier();
            size = 5;
        } else if (i > 0 && i < 3) {
            currentShip = "Battleship";
            tempShipAdress = tempShip.createBattelship();
            size = 4;
        } else if (i > 2 && i < 6) {
            currentShip = "Destroyer";
            tempShipAdress = tempShip.createDestroyer();
            size = 3;
        } else {
            currentShip = "Submarine";
            tempShipAdress = tempShip.createSubmarine();
            size = 2;
        }

        do {
            UserInput(currentShip, tempChar, tempNum, direction);
        } while (!isPlacementPossible(Player, size, tempNum - 1, tempChar - 65, direction));
        int row = tempNum - 1;
        int column = tempChar - 65;
        for (int j = 0; j < size; j++) {
            if(direction == 'r'){
                Player->Playfield.Playground[row + j][column].setShipAdress(tempShipAdress);
                Player->Playfield.Playground[row + j][column].setShipHere();
            } else if (direction == 'l') {
                Player->Playfield.Playground[row - j]->setShipAdress(tempShipAdress);
                Player->Playfield.Playground[row - j][column].setShipHere();
            } else if (direction == 'u'){
                Player->Playfield.Playground[row][column - j].setShipAdress(tempShipAdress);
                Player->Playfield.Playground[row][column - j].setShipHere();
            } else if(direction == 'd') {
                Player->Playfield.Playground[row][column + j].setShipAdress(tempShipAdress);
                Player->Playfield.Playground[row][column + j].setShipHere();
            }
        }
        Player->Playfield.printOwnField();
        Player->shipAdressVector.push_back(tempShipAdress);
        tempShipAdress->intHitsTaken();
    }
}

bool Game::isPlacementPossible(Spieler* Player, int size, int row, int column, char direction) {
    bool x = false;
    bool y = false;
    bool temp = true;
    if (Player->Playfield.Playground[row][column].isShipHere()) {
        // Ist der Ort überhaupt Frei?
        return false;
    } else {
        if(direction == 'r'){
            for (int i = 0; i < size && temp; i++) {
                if (row + i == 10) {
                    temp = false;
                } else {
                    temp = !Player->Playfield.Playground[row + i][column].isShipHere();
                }
            }
        } else if (direction == 'l') {
            for (int i = 0; i < size && temp; i++) {
                if(row - i < 0){
                    temp = false;
                } else {
                    temp = !Player->Playfield.Playground[row - i][column].isShipHere();
                }
            }
        } else if (direction == 'u') {
            for (int i = 0; i < size && temp; i++) {
                if(column - i < 0){
                    temp = false;
                } else {
                    temp = !Player->Playfield.Playground[row][column - i].isShipHere();
                }
            }
        } else if (direction == 'd'){
            for (int i = 0; i < size && temp; i++) {
                if (column + i == 10){
                    temp = false;
                } else {
                    temp = !Player->Playfield.Playground[row][column + i].isShipHere();
                }
            }
        }
    }
    return temp;
}

void Game::UserInput(const string& Ship,char &tempChar, int &tempNum, char &direction) {
    tempChar = InputChar(Ship, false);
    tempNum = InputInt(Ship, false);
    direction = InputDirection();
}

char Game::InputDirection() {
    char tempDirection = ' ';
    do{
        cout << "What direction? [u = Up, d = Down, r = right, l = left]:";
        cin >> tempDirection;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (tempDirection >= 'A' && tempDirection <= 'Z') {
            tempDirection = (char)(tempDirection - ('a' - 'A'));
        }
    } while (tempDirection != 'u' && tempDirection != 'd' && tempDirection != 'r' && tempDirection != 'l');
    return tempDirection;
}

bool Game::setFastMode() {
    int Awnser;
    cout << endl << "Fast Mode on or off?" << endl;
    do {
        cout<< endl << "1. on" << endl;
        cout<< "2. off" << endl;
        cin >> Awnser;
        while (cin.fail())
        {
            cin.clear(); // clears input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "You can only enter numbers.\n";
            Awnser = 0;
        }
    } while (Awnser != 1 && Awnser != 2);
    return Awnser == 1;
}

