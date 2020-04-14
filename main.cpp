

#include "Game.hpp"

using namespace std;

int main() {

    Game* GetOn = new Game();
    GetOn->run();
    delete(GetOn);
    return 0;
}