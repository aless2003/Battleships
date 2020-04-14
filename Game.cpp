//
// Created by aless on 12.03.2020.
//

#include "Game.hpp"
void Game::run() {
    initialize();
    play();//TODO play ausprogrammieren
}

void Game::initialize() {
    string tempName;
    cout << "Player 1 can place his Ships" << endl << "Type in your Name and Press Enter to show your field - make sure your opponent isn't looking on the Screen!";
    cin >> tempName;
    Player1->setName(tempName);
    Player1->Playfield.printOwnField();
    intPlayer(Player1);

    cout << "Player 2 can place his Ships" << endl << "Type in your Name and Press Enter to show your field - make sure your opponent isn't looking on the Screen!";
    cin >> tempName;
    Player2->setName(tempName);
    Player2->Playfield.printOwnField();
    intPlayer(Player2);
}

void Game::intPlayer(Spieler* Player) {
    char tempChar;
    int tempNum = 0 , size = 0;
    string currentShip;
    Schiffe tempShip;
    Schiffe* tempShipAdress = NULL;
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
            cout << "Type the Vertical Coordinate of the Ship (" << currentShip << ") [A-J]";
            cin >> tempChar;
            cout << "Type the Horizontal Coordinate of the Ship (" << currentShip <<") [1-10]";
            cin >> tempNum;
        } while (!isPlacementPossible(Player1, size, tempNum, tempChar - 65));
        int x = tempNum - 1;
        int  y = tempChar - 65;
        placeShip(tempShipAdress, x, y, Player);
        cout << "Its Working!";
        temp.y.push_back(y);
        temp.x.push_back(x);
        //Restliche Teile
        for (int j = 0; j < size - 1; j++) {
            do{

                cout << "Type the vertical position of the next part of your Ship [A-J]";
                cin >> tempChar;
                cout << "Type the horizontal position of the next part of your Ship [1-10]";
                cin >> tempNum;
            } while (!placeNextRight(temp, tempChar - 65, tempNum - 1, Player, direction));
            int x = tempNum - 1;
            int  y = tempChar - 65;
            if (j == 0) {
                direction = saveDirection(temp,x,y);
            }
            placeShip(tempShipAdress, x, y, Player);
            temp.x.push_back(x);
            temp.y.push_back(y);
        }
        temp.y.clear();
        temp.x.clear();
        direction = 'N';
    }
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
                    temp = !Player->Playfield.Playground[row + j][column].isShipHere();
                }
                x = temp;
            } else if (i == 1 && !x) {
                for (int j = 1; j <= size && temp; j++) {
                    temp = !Player->Playfield.Playground[row - j][column].isShipHere();
                }
                x = temp;
            }

            if (i == 0 && !y) {
                for (int j = 1; j <= size && temp; j++) {
                    temp = !Player->Playfield.Playground[row][column + j].isShipHere();
                }
                y = temp;
            } else if (i == 1 && !y) {
                for (int j = 1; j <= size && temp; j++) {
                    temp = !Player->Playfield.Playground[row][column - j].isShipHere();
                }
                y = temp;
            }
        }
    }
    return x && y;
}

bool Game::placeNextRight(coos temp, int row, int column, Spieler * Player, char direction) {
    bool isValidX = false;
    bool isValidY = false;
    bool secondOnSameSpace = false;
    if (!Player->Playfield.Playground[row][column].isShipHere()) {
        for (int i = 0; i < temp.x.size() && !isValidX; i++) {
            if (direction == 'y') {
                isValidX = temp.x[i] + 1 == column || temp.x[i] - 1 == column;
            } else if(direction == 'x'){
                isValidX = temp.x[i] == column;
            } else if (temp.x[i] == column) {
                isValidX = true;
                secondOnSameSpace = true;
            }   else {
                isValidX = temp.x[i] + 1 == column || temp.x[i] - 1 == column;
            }
        }
        for (int i = 0; i < temp.y.size() && !isValidY; i++) {
            if (direction == 'x') {
                isValidY = temp.y[i] + 1 == row || temp.y[i] - 1 == row;
            } else if (direction == 'y'){
                isValidY = temp.y[i] == row;
            } else if(!secondOnSameSpace) {
                isValidY = temp.y[i] == row;
            } else{
                isValidY = temp.y[i] + 1 == row || temp.y[i] - 1 == row;
            }
        }
    } else {
        return false;
    }
    return isValidX && isValidY;
}

void Game::placeShip(const Schiffe * tempShipAdress, int x, int y, Spieler *Player) {
    Player->Playfield.Playground[y][x].setShipHere();
    Player->Playfield.Playground[y][x].setShipAdress(const_cast<Schiffe *>(tempShipAdress));
    Player->Playfield.printOwnField();
}

void Game::play() {
    bool won = false;
    char tempChar = ' ';
    bool hitValid = false;
    int x = 0, y = 0;
    Spieler* Enemy = NULL;
    Spieler* Player = NULL;
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
            cout << "Type the Vertical Coordinate of your shooting guess [A-J]";
            cin >> tempChar;
            cout << "Type the Horizontal Coordinate of your shooting guess [1-10]";
            cin >> tempNum;
            x = tempNum - 1;
            y = tempChar - 65;
            //Ist an der Stelle schonmal geschossen worden?
            hitValid = Enemy->Playfield.Playground[y][x].isHitten();
            if (hitValid){
                cout << "No valid Coos, you shot there already >:(";
            }
            //wenn ja, dann wird der benutzer nochmal aufgefordert Coos einzugeben
        } while (hitValid);
        //Schuss wird ausgeführt
        shoot(x, y, Enemy);
        //Spieler tauschen Feld
        cout << "Press Enter to switch Boards";
        cin.ignore();
        system("cls");

        //TODO Winning Function
    } while (!won);
}

void Game::shoot(int x, int y, Spieler* Player) {
    Player->Playfield.Playground[y][x].setHit();
}

bool Game::findWinner(Spieler *x) {
    bool noShipLeft = true;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (x->Playfield.Playground[i][j].isShipHere()) {
                if (noShipLeft && x->Playfield.Playground[i][j].isHitten()) {
                } else {
                    noShipLeft = false;
                }
            }
        }
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

Game::~Game() {

}
