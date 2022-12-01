#include "game.h"
void Game::handleWay() {
    if (way == "in") //responsible for the position of the hero at the entrance of the next room, or at the exit of the previous one if he goes back
    {
        Boy.pos_X = dungeon[room_id].enterX;
        Boy.pos_Y = dungeon[room_id].enterY;
        Boy.move("", dungeon[room_id]);
    }
    else if (way == "back")
    {
        Boy.pos_X = dungeon[room_id].exitX;
        Boy.pos_Y = dungeon[room_id].exitY;
        Boy.move("", dungeon[room_id]);
    }
    way = "";
}
void Game::createRoomAndSpawnObjects() {
    if (room_id == 0) {
        return;
    }
    if (dungeon[room_id - 1].corridor_type == 2) {
        dungeon[room_id].way_in = "botom";
    }
    else if (dungeon[room_id - 1].corridor_type == 1) {
        dungeon[room_id].way_in = "left";
    }
    else {
        if (dungeon[room_id - 1].way_out == "up")
        {
            dungeon[room_id].way_in = "botom";
        }
        else
        {
            dungeon[room_id].way_in = "left";
        }
    }
    dungeon[room_id].create_room();
    for (int a = 0; a < dungeon[room_id].items.size(); a++)
    {
        if (dungeon[room_id].items[a].picked_up == false)
            dungeon[room_id].items[a].spawn_item(dungeon[room_id], Boy);
    }
    if (dungeon[room_id].Monster_exist)
        monsters[room_id].spawn(dungeon[room_id]);
}
bool Game::isGameExists() {
    return (room_id >= 0 && room_id < dungeon.size());
}
void Game::startGame() {
    cout << "Use WASD for move" << endl << "Use E to pick up items " << endl << "Use F for attack monsters " << endl << "Use Enter for leave room" << endl << "Use I for showing your stats" << endl << "Use H for healing" << endl << "Use Esc for leave the game" << endl; //������� ���������� � ���, ��� ����� ������� ������
}
void Game::endGame() {
    //then the code that will be executed after passing the last room
    cout << "YOU WON :)" << endl;
}
void Game::startKeysCycle() {
    while (room_id != -1) //controlled cycle, reads the pressed keys
    {
        auto exit = handleKeys();
        if (exit) {
            break;
        }
    }
}
bool Game::handleKeys() {
#ifdef __clang__
    auto ch = getchar();
#else
    auto ch = _getch();
#endif
    auto code = static_cast<int>(ch);
    switch (ch) {
    case 27:
        room_id = -1;
        break;
    case 's':
        Boy.move("down", dungeon[room_id]); //responsible for moving down
        break;
    case 'a':
        Boy.move("left", dungeon[room_id]);//for moving left
        break;
    case 'd':
        Boy.move("right", dungeon[room_id]);//for moving right
        break;
    case 'w':
        Boy.move("up", dungeon[room_id]);//for moving up
        break;
    case 102:
        if ((Boy.pos_X == monsters[room_id].Mpos_X + 1 || Boy.pos_X == monsters[room_id].Mpos_X - 1 || (Boy.pos_X == monsters[room_id].Mpos_X) && Boy.pos_Y == monsters[room_id].Mpos_Y + 1 || (Boy.pos_X == monsters[room_id].Mpos_X) && Boy.pos_Y == monsters[room_id].Mpos_Y - 1 || (Boy.pos_X == monsters[room_id].Mpos_X) && Boy.pos_Y == monsters[room_id].Mpos_Y))
        {
            monsters[room_id].take_damage(Boy.damage, dungeon[room_id], Boy);
            Boy.move("", dungeon[room_id]);
            cout << monsters[room_id].health << " monster health " << Boy.health << " Your health" << endl;
        }
        break;

    case 101://responsible for picking up items in the room
        for (int i = 0; i < dungeon[room_id].items.size(); i++)
        {
            if ((Boy.pos_X == dungeon[room_id].items[i].Ipos_X + 1 || Boy.pos_X == dungeon[room_id].items[i].Ipos_X - 1 || Boy.pos_X == dungeon[room_id].items[i].Ipos_X) && (Boy.pos_Y == dungeon[room_id].items[i].Ipos_Y || Boy.pos_Y == dungeon[room_id].items[i].Ipos_Y + 1 || Boy.pos_Y == dungeon[room_id].items[i].Ipos_Y - 1))
            {
                dungeon[room_id].items[i].on_pick_up(dungeon[room_id], Boy);
            }
        }
        break;
    case 105:
        Boy.move("", dungeon[room_id]);
        cout << "Health: " << Boy.health << endl << "Damage: " << Boy.damage << endl << "Food amount: " << Boy.heal_ammount << endl << "Bottles: " << Boy.bottle_ammount << endl;
        break;
    case 104:
        Boy.use_heal();
        break;
    }
    if ((ch == 10 || ch == 13) && Boy.pos_X == dungeon[room_id].enterX && Boy.pos_Y == dungeon[room_id].enterY)//responsible for moving back between rooms
    {
        room_id--;
        way = "back";
        return true;
    }
    if ((ch == 10 || ch == 13) && Boy.pos_X == dungeon[room_id].exitX && Boy.pos_Y == dungeon[room_id].exitY)//responsible for moving back and forth between rooms
    {
        way = "in";
        room_id++;

        return true;
    } //the code below is responsible for dealing damage to the monster

    cout << code << endl;  //outputs the ascii code of the pressed key

    return false;
}
