#include <iostream>
#include <vector>
#include <cstdlib>
#include "game.h"

using namespace std;


int main()
{
    auto game = getGame();

    string way, coredore_side;

    game.startGame();
    //Displays information about controls
    while (game.isGameExists()) //the controlled cycle will be repeated until the room_id becomes -1, or Hero reaches the last room
    {
        game.createRoomAndSpawnObjects();
        game.handleWay();
        game.startKeysCycle();
    }
    game.endGame();
}
